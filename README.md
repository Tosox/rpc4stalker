# rpc4stalker
[![C++](https://img.shields.io/badge/Language-C%2B%2B-%23f34b7d.svg?style=flat)](https://en.wikipedia.org/wiki/C%2B%2B) 
[![S.T.A.L.K.E.R.](https://img.shields.io/badge/Game-S.T.A.L.K.E.R.-yellow.svg?style=flat)](https://www.moddb.com/mods/call-of-chernobyl) 
[![Windows](https://img.shields.io/badge/Platform-Windows-0078d7.svg?style=flat)](https://en.wikipedia.org/wiki/Microsoft_Windows) 
[![x86](https://img.shields.io/badge/Arch-x86-red.svg?style=flat)](https://en.wikipedia.org/wiki/X86) 

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
- Open the compressed file and install the mod located in the 'data' folder like any other mod for S.T.A.L.K.E.R.
- Open the game and load a save
- Run the program

## Preview
![preview](https://github.com/TosoxDev/rpc4stalker/tree/master/data/preview.png)
![discord](https://github.com/TosoxDev/rpc4stalker/tree/master/data/discord.png)

## FAQ
### Which S.T.A.L.K.E.R. games is the program compatible with?
It is compatible with all games derived from the [Call of Chernobyl](https://www.moddb.com/mods/call-of-chernobyl) mod. Unfortunately, this does not include the three original games. A list of tested games can be found [here](https://github.com/TosoxDev/rpc4stalker/tree/master/data/compatibility.txt).

### How does the program work?
The mod that needs to be installed is the most important part of this program. It saves the data to be displayed in the discord status in a file in '%temp%\rpc4stalker.json'. The executable is only responsible for reading and transmitting the data to discord via their [SDK](https://discord.com/developers/docs/game-sdk/sdk-starter-guide).

### Which languages are supported?
The Latin and Cyrillic script were successfully tested.

### Can the mod conflict with other S.T.A.L.K.E.R. mods?
No, because no files need to be overwritten during the installation.
