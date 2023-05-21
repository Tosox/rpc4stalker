# rpc4stalker
[![](https://img.shields.io/badge/Language-C%2B%2B-%23f34b7d.svg?style=flat)](https://en.wikipedia.org/wiki/C%2B%2B) 
[![](https://img.shields.io/badge/Game-S.T.A.L.K.E.R.-yellow.svg?style=flat)](https://store.steampowered.com/app/41700/STALKER_Call_of_Pripyat) 
[![](https://img.shields.io/github/languages/code-size/TosoxDev/rpc4stalker?color=blue&label=Code%20size&style=flat)](https://github.com/TosoxDev/rpc4stalker)
[![](https://img.shields.io/tokei/lines/github/TosoxDev/rpc4stalker?color=red&label=Total%20lines&style=flat)](https://github.com/TosoxDev/rpc4stalker)
[![](https://img.shields.io/github/downloads/TosoxDev/rpc4stalker/total?color=green&label=Downloads&style=flat)](https://github.com/TosoxDev/rpc4stalker/releases)

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

## Preview
<img src="readme-res/preview.png" width="650" height="340" /> <img src="readme-res/discord.png" width="225" height="340" />

## FAQ
### Which S.T.A.L.K.E.R. games is the program compatible with?
It is compatible with all games *based* on the [Call of Chernobyl](https://www.moddb.com/mods/call-of-chernobyl) mod. Unfortunately, this does not include the three original games. A list of tested games can be found [here](COMPATABILITY.md).

### How does the program work?
The mod that needs to be installed is the most important part of this program. It saves the data to be displayed in the discord status in a file in `%temp%\rpc4stalker.json`. The dll is only responsible for reading and transmitting the data to discord via their [GameSDK](https://discord.com/developers/docs/game-sdk/sdk-starter-guide).

### Can the mod conflict with other mods?
No, because no files need to be overwritten during the installation.

## Compatability
| Game                                  | Platform  | Data Install Location     |
|---------------------------------------|-----------|---------------------------|
| S.T.A.L.K.E.R. Call of Chernobyl      | Win32     | /bin/                     |
| S.T.A.L.K.E.R. Call of The Zone       | Win32     | /bin/                     |
| S.T.A.L.K.E.R. Call of Misery         | Win32     | /bin/                     |
| S.T.A.L.K.E.R. Road To The North      | Win64     | /bin/                     |
| S.T.A.L.K.E.R. Global War             | Win32     | /bin/                     |
| S.T.A.L.K.E.R. Anomaly                | Win64     | /bin/                     |
| S.T.A.L.K.E.R. Dead Air               | Win32     | /                         |
| S.T.A.L.K.E.R. A.R.E.A.               | Win32     | /bin/                     |

## Credits
- [ThirteenAG](https://github.com/ThirteenAG) for his [ASI-Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader)
- [Discord](https://github.com/discord) for their [GameSDK](https://discord.com/developers/docs/game-sdk/sdk-starter-guide)
- [GNU](https://www.gnu.org) for their conversion library [libiconv](https://www.gnu.org/software/libiconv)
- [nlohmann](https://github.com/nlohmann) for a modern C++ [implementation of JSON](https://github.com/nlohmann/json)

