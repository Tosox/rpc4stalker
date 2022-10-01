# rpc4stalker
[![C++](https://img.shields.io/badge/Language-C%2B%2B-%23f34b7d.svg?style=flat)](https://en.wikipedia.org/wiki/C%2B%2B) 
[![S.T.A.L.K.E.R.](https://img.shields.io/badge/Game-S.T.A.L.K.E.R.-yellow.svg?style=flat)](https://store.steampowered.com/app/41700/STALKER_Call_of_Pripyat) 
[![Windows](https://img.shields.io/badge/Platform-Windows-0078d7.svg?style=flat)](https://en.wikipedia.org/wiki/Microsoft_Windows) 
[![x86](https://img.shields.io/badge/Arch-x86-green.svg?style=flat)](https://en.wikipedia.org/wiki/X86)
[![Mod DB](https://img.shields.io/badge/ModDB-Download-red.svg?style=flat)](https://www.moddb.com/mods/call-of-chernobyl/addons/rpc4stalker)

> Note: *This mod is only compatible with games based on [Call of Chernobyl](https://www.moddb.com/mods/call-of-chernobyl)*

```
                               $$\   $$\             $$\               $$\ $$\                           
                               $$ |  $$ |            $$ |              $$ |$$ |                          
  $$$$$$\   $$$$$$\   $$$$$$$\ $$ |  $$ | $$$$$$$\ $$$$$$\    $$$$$$\  $$ |$$ |  $$\  $$$$$$\   $$$$$$\  
 $$  __$$\ $$  __$$\ $$  _____|$$$$$$$$ |$$  _____|\_$$  _|   \____$$\ $$ |$$ | $$  |$$  __$$\ $$  __$$\ 
 $$ |  \__|$$ /  $$ |$$ /      \_____$$ |\$$$$$$\    $$ |     $$$$$$$ |$$ |$$$$$$  / $$$$$$$$ |$$ |  \__|
 $$ |      $$ |  $$ |$$ |            $$ | \____$$\   $$ |$$\ $$  __$$ |$$ |$$  _$$<  $$   ____|$$ |      
 $$ |      $$$$$$$  |\$$$$$$$\       $$ |$$$$$$$  |  \$$$$  |\$$$$$$$ |$$ |$$ | \$$\ \$$$$$$$\ $$ |      
 \__|      $$  ____/  \_______|      \__|\_______/    \____/  \_______|\__|\__|  \__| \_______|\__|      
           $$ |                                                                                          
           $$ |                                                                                          
           \__|                                                                                           
```

## Installation
- Download the latest [release](https://github.com/TosoxDev/rpc4stalker/releases)
- Open the compressed file and install the mod located in the `data` folder like any other mod for S.T.A.L.K.E.R.
- Install both VC Redistributables located in the `redist` folder if necessary
- Open the game and load a save
- Run the program

## Compilation
- `C++ 17` is required for compilation
- Make sure that you use `Release | x86` as build configuration

## Preview
<img src="readme-res/preview.png" width="650" height="340" /> <img src="readme-res/discord.png" width="225" height="340" />

## FAQ
### Which S.T.A.L.K.E.R. games is the program compatible with?
It is compatible with all games based on the [Call of Chernobyl](https://www.moddb.com/mods/call-of-chernobyl) mod. Unfortunately, this does not include the three original games. A list of tested games can be found [here](readme-res/compatibility.txt).

### How does the program work?
The mod that needs to be installed is the most important part of this program. It saves the data to be displayed in the discord status in a file in `%temp%\rpc4stalker.json`. The executable is only responsible for reading and transmitting the data to discord via their [GameSDK](https://discord.com/developers/docs/game-sdk/sdk-starter-guide).

### Which languages are supported?
The Latin and Cyrillic script were successfully tested.

### Can the mod conflict with other mods?
No, because no files need to be overwritten during the installation.

## Credits
- [Discord](https://github.com/discord) for their [GameSDK](https://discord.com/developers/docs/game-sdk/sdk-starter-guide)
- [nlohmann](https://github.com/nlohmann) for a modern C++ [implementation of JSON](https://github.com/nlohmann/json)

