# Beginner's Guide to Installing the Carim Mod

Installing the Carim Mod requires editing two specific files on your server. Because
DayZ server configurations use strict formatting, one missing comma or misplaced
bracket will cause the settings to fail. Follow these steps exactly.

## Phase 1: Locating Your Server Files

You need to find two files. Depending on your server host, they are located in different places:

1. `serverDZ.cfg` (Your main server settings file)
2. `cfggameplay.json` (Your gameplay settings file)

**Where to find them:**

* **Nitrado:** Open your Web Interface -> Settings -> Config Files. You will see your `serverDZ.cfg` here. To find `cfggameplay.json`, use the File Browser and navigate to `dayz/mpmissions/dayzOffline.chernarusplus` (or your active map's mission folder).
* **GTX Gaming / Pingperfect / Other Panels:** Use the control panel's File Manager. `serverDZ.cfg` is usually sitting right in the root directory. To find `cfggameplay.json`, open the `mpmissions` folder, then open your active mission folder (like `dayzOffline.chernarusplus`).
* **Local / Dedicated Server:** `serverDZ.cfg` is in your main server folder. `cfggameplay.json` is located in `mpmissions\dayzOffline.chernarusplus\` (or your specific map).

## Phase 2: Forcing the Server to Read the Config

By default, DayZ ignores the `cfggameplay.json` file. You must tell the server to read it.

1. Open your `serverDZ.cfg` file.
2. Scroll to the very bottom and add (or modify) this exact line:
`enableCfgGameplayFile = 1;`
3. Save the file.

## Phase 3: Adding CarimData to `cfggameplay.json` (CRUCIAL STEP)

⚠️ **WARNING: DO NOT OVERWRITE YOUR EXISTING FILE!** Your `cfggameplay.json` already contains vital server settings under sections like `GeneralData` and `PlayerData`. **Do not delete or overwrite them.** You are simply *adding* the `CarimData` section into the existing structure.

Additionally, **you only need to include the values you are changing.** The mod automatically loads the defaults for everything else. You do not need to paste the entire massive block of code from the documentation if you only want to tweak a few things.

**Why do people mess this up?** JSON files are extremely strict. The `CarimData` block must be placed at the **"Root Level"** of the file. It cannot be trapped inside `GeneralData` or any other section. It must be its own independent block.

❌ **THE WRONG WAY (DO NOT DO THIS):**

```json
{
    "version": 122,
    "GeneralData": {
        "disableBaseDamage": false,
        "CarimData": {   <--- WRONG! It is trapped inside GeneralData!
            "CarimAutorunData": {
               "enabled": true
            }
        }
    }
}
```

✅ **THE RIGHT WAY (MINIMAL CONFIG EXAMPLE):**
**DO NOT COPY AND PASTE THIS ENTIRE BLOCK.** This is just a visual example to show you how `CarimData` fits into your *existing* file alongside your other settings.

In this example, we are leaving most Carim settings at their default, but adding an admin ID (using a **BattlEye GUID**) and changing the global chat color. Notice the comma `,` right before `"CarimData"`.

```json
{
    "version": 122,
    "GeneralData": {
        "...": "Leave all your existing GeneralData settings here alone..."
    },
    "PlayerData": {
        "...": "Leave all your existing PlayerData settings here alone..."
    },
    "CarimData": {
        "adminIds": [
            "YourBattlEyeGUIDHere"
        ],
        "CarimChatData": {
            "colorGlobal": -16537100
        }
    }
}
```

## Phase 4: Fixing Map Settings

If you are using the Carim Map module, players may want to be able to open the map without having a physical map item in their inventory.

Still inside your `cfggameplay.json`, locate your existing `"MapData"` and `"UIData"` blocks. Modify the specific lines within them so they look exactly like this:

```json
    "MapData": {
        "ignoreMapOwnership": true,
        "ignoreNavItemsOwnership": true,
        "displayPlayerPosition": true,
        "displayNavInfo": true
    },
    "UIData": {
        "use3DMap": false
    }
```

## Phase 5: The Sanity Check (Don't skip this!)

Before you restart your server, you need to make sure you didn't accidentally delete a bracket or miss a comma.

1. Copy all of the text inside your `cfggameplay.json`.
2. Go to **[jsonlint.com](https://jsonlint.com/)** and paste your text into the box.
3. Click **"Validate JSON"**.
4. If it glows green and says "Valid JSON", you are good to go! Save the file and restart your server. If it gives you an error, look at the line number it tells you—you are likely missing a comma `,` right before the `CarimData` block or a closing bracket `}`.
