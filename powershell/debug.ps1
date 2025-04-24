$steamRoot = "S:\SteamLibrary\steamapps\common"
$clientDir = "$steamRoot\DayZ"
$serverDir = "$steamRoot\DayZServer"
$localMods = "S:\DayZDevOutput"
$workshopMods = "$clientDir\!Workshop"

$mission = "P:\missions\dayzOffline.chernarusplus"

# verify all can load (duplicate inputs.xml errors are expected)
# $mod = "$localMods\@Carim;$localMods\@CarimAutorun;$localMods\@CarimChat;$localMods\@CarimCompass;$localMods\@CarimParty;

# verify all SchanaMods
# $mod = "$localMods\@SchanaModGlobalChat;$localMods\@SchanaModCompass;$localMods\@SchanaModParty;"

# check all functionality in single mod
$mod = "$localMods\@Carim"

# verify all workshop mods
# $mod = "$workshopMods\@SchanaModGlobalChat;$workshopMods\@SchanaModCompass;$workshopMods\@SchanaModParty;$workshopMods\@Carim;$workshopMods\@CarimAutorun;$workshopMods\@CarimChat;$workshopMods\@CarimCompass;$workshopMods\@CarimParty;"

# run prod server
#Start-Process -FilePath "$serverDir\DayZServer_x64.exe" -WorkingDirectory "$serverDir" -ArgumentList "-mod=$mod -profiles=$mission\profilesServer -doLogs -config=$mission\serverDZ.cfg -limitFPS=1000"

# run diag server & client
Start-Process -FilePath "$clientDir\DayZDiag_x64.exe" -WorkingDirectory "$clientDir" -ArgumentList "-mod=$mod -profiles=$mission\profilesServer -doLogs -server -config=$mission\serverDZ.cfg -limitFPS=1000"
Start-Process -FilePath "$clientDir\DayZDiag_x64.exe" -WorkingDirectory "$clientDir" -ArgumentList "-mod=$mod -profiles=$mission\profilesClient -doLogs -name=cnofafva -connect=127.0.0.1 -port=2302"


