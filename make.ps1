param([switch]$Setup = $false, [switch]$Build = $false, [switch]$Workbench = $false, [switch]$Diag = $false, [switch]$Server = $false, [switch]$Exp = $false)

$mod = "Carim"
$key = "S:\Drive\DayZKeys\schana.biprivatekey"
$publicKey = "S:\Drive\DayZKeys\schana.bikey"
$dayZExtract = "C:\Users\Nathaniel\AppData\Local\DayZExtract\DayZExtract.exe"
$steamRoot = "S:\SteamLibrary\steamapps\common"
$expClientDir = "$steamRoot\DayZ Exp"
$expServerDir = "$steamRoot\DayZ Server Exp"
$expToolsDir = "$steamRoot\DayZ Experimental Tools"
$clientDir = "$steamRoot\DayZ"
$serverDir = "$steamRoot\DayZServer"
$toolsDir = "$steamRoot\DayZ Tools"
$addonBuilder = "$toolsDir\Bin\AddonBuilder\AddonBuilder.exe"
$workshopMods = "$clientDir\!Workshop"
$projectDrive = "P:"
$projectDriveSource = "S:\DayZDev"

$root = $(Convert-Path $(git rev-parse --show-toplevel))
$localMods = "$root\build"
$missions = "$root\missions"
$missionName = "dayzOffline.chernarusplus"

function Setup-Project {
    # Clean previous setups
    if ((Test-Path -Path "$projectDrive\DZ")) {
        Remove-Item "$projectDrive\*" -Recurse -Force
    }
    if ((Test-Path -Path "$missions\$missionName")) {
        Remove-Item "$missions\$missionName" -Recurse -Force
        Remove-Item "$missions\profiles" -Recurse -Force
        Remove-Item "$missions\serverDZ.cfg" -Force
    }

    # Extract game data to project drive
    if ($Exp) {
        Check-Result -FilePath "$dayZExtract" -ArgumentList "$projectDrive", "--experimental", "--unattended", "--parallel 8"
    }
    else {
        Check-Result -FilePath "$dayZExtract" -ArgumentList "$projectDrive", "--unattended", "--parallel 16"
    }

    # Create the junction
    cmd /c mklink /J "$projectDrive\$mod" "$root\$mod"
    
    $workingServerDir = $serverDir
    $workingClientDir = $clientDir
    if ($Exp) {
        $workingServerDir = $expServerDir
        $workingClientDir = $expClientDir
    }

    # Ensure the keys are present
    if (!(Test-Path -Path "$workingClientDir\keys")) {
        Copy-Item "$workingServerDir\keys" -Destination "$workingClientDir\keys" -Recurse
        Copy-Item "$publicKey" -Destination "$workingClientDir\keys"
        Copy-Item "$publicKey" -Destination "$workingServerDir\keys"
    }

    # Setup the mission used for testing
    Copy-Item "$workingServerDir\mpmissions\$missionName" -Destination "$missions\$missionName" -Recurse
    Copy-Item "$workingServerDir\serverDZ.cfg" -Destination "$missions\"

    (Get-Content "$missions\serverDZ.cfg").Replace($missionName, "$missions\$missionName") | Set-Content "$missions\serverDZ.cfg"
    (Get-Content "$missions\serverDZ.cfg").Replace("maxPlayers = 60;", "enableCfgGameplayFile=1;`nmaxPlayers = 60;") | Set-Content "$missions\serverDZ.cfg"

    $cfggameplay = Get-Content "$missions\$missionName\cfggameplay.json" -raw | ConvertFrom-Json
    # map config
    $cfggameplay.MapData.ignoreMapOwnership = $true
    $cfggameplay.MapData.ignoreNavItemsOwnership = $true
    $cfggameplay.MapData.displayPlayerPosition = $true
    $cfggameplay.MapData.displayNavInfo = $true
    # unlimited stamina
    $cfggameplay.PlayerData.StaminaData.sprintStaminaModifierErc = 0.0
    $cfggameplay.PlayerData.StaminaData.sprintStaminaModifierCro = 0.0
    $cfggameplay.PlayerData.StaminaData.staminaWeightLimitThreshold = 60000.0
    $cfggameplay.PlayerData.StaminaData.staminaMax = 9999.0
    $cfggameplay.PlayerData.StaminaData.staminaKgToStaminaPercentPenalty = 0.0
    $cfggameplay.PlayerData.StaminaData.staminaMinCap = 9999.0
    $cfggameplay.PlayerData.StaminaData.sprintSwimmingStaminaModifier = 0.0
    $cfggameplay.PlayerData.StaminaData.sprintLadderStaminaModifier = 0.0
    $cfggameplay.PlayerData.StaminaData.meleeStaminaModifier = 0.0
    $cfggameplay.PlayerData.StaminaData.obstacleTraversalStaminaModifier = 0.0
    $cfggameplay.PlayerData.StaminaData.holdBreathStaminaModifier = 0.0
    # write
    $cfggameplay | ConvertTo-Json -Depth 32 -Compress | Set-Content "$missions\$missionName\cfggameplay.json"

    (Get-Content "$missions\$missionName\db\globals.xml").Replace('<var name="TimeLogin" type="0" value="15"/>', '<var name="TimeLogin" type="0" value="1"/>') | Set-Content "$missions\$missionName\db\globals.xml"
}

function Start-Workbench {
    $workingDir = $toolsDir
    if ($Exp) {
        $workingDir = $expToolsDir
    }
    Start-Process -FilePath workbenchApp.exe -WorkingDirectory "$workingDir\Bin\Workbench" -ArgumentList "-mod=$projectDrive\$mod\$mod;$projectDrive\$mod\${mod}Deprecated;"
}

function Build-Project {
    $outputs = Get-ChildItem "$localMods" | Where-Object { $_.PSISContainer }

    foreach ($output in $outputs) {
        $inputRoot = "$projectDrive\$mod\$output".Replace('@', '')
        $outputRoot = "$localMods\$output"

        if ((Test-Path -Path "$outputRoot\addons")) {
            Remove-Item "$outputRoot\addons\*" -Recurse -Force
        } else {
            New-Item -Path "$outputRoot\addons" -ItemType Directory
        }

        if ((Test-Path -Path "$outputRoot\keys")) {
            Remove-Item "$outputRoot\keys\*" -Recurse -Force
        } else {
            New-Item -Path "$outputRoot\keys" -ItemType Directory
        }

        Copy-Item -Path "$publicKey" -Destination "$outputRoot\keys\"

        $builderArgs = @(
            "$inputRoot",
            "$outputRoot\addons",
            "-clear",
            "-sign=$key",
            "-include=$localMods\include.txt",
            "-project=$inputRoot",
            "-prefix=$mod\$output".Replace('@', '')
        )

        Check-Result -FilePath $addonBuilder -ArgumentList $builderArgs

        Write-Output "Built with args: $($builderArgs -join ' ')"
    }
}

function Diag-Project {
    $mods = "$localMods\@$mod;$localMods\@${mod}MapStyle"
    # $mods = "$workshopMods\@$mod;$workshopMods\@${mod}MapStyle"

    $workingDir = $clientDir
    if ($Exp) {
        $workingDir = $expClientDir
    }
    
    Start-Process -FilePath "$workingDir\DayZDiag_x64.exe" -WorkingDirectory "$workingDir" -ArgumentList "-mod=$mods -profiles=$missions\profiles\server -doLogs -server -config=$missions\serverDZ.cfg -limitFPS=1000"
    Start-Process -FilePath "$workingDir\DayZDiag_x64.exe" -WorkingDirectory "$workingDir" -ArgumentList "-mod=$mods -profiles=$missions\profiles\client -doLogs -name=cnofafva -connect=127.0.0.1 -port=2302"
}

function Run-Server {
    $mods = "$localMods\@$mod;$localMods\@${mod}MapStyle"

    $workingDir = $serverDir
    if ($Exp) {
        $workingDir = $expServerDir
    }
    Start-Process -FilePath "$workingDir\DayZServer_x64.exe" -WorkingDirectory "$workingDir" -ArgumentList "-mod=$mods -profiles=$missions\profiles\server -doLogs -config=$missions\serverDZ.cfg -limitFPS=1000"
}

function Check-Result {
    $process = (Start-Process -Wait -PassThru -NoNewWindow @args)
    if ($process.ExitCode) {
        throw "Failed"
    }
}

# Setup the P drive if it's not already
if (!(Test-Path -Path "$projectDrive")) {
    subst "$projectDrive" "$projectDriveSource"
}

if ($Setup) {
    Setup-Project
}
if ($Build) {
    Build-Project
}
if ($Workbench) {
    Start-Workbench
}
if ($Diag) {
    Diag-Project
}
if ($Server) {
    Run-Server
}
