@echo off
:start
::Server name (Change to whatever you want to call your server)
set serverName=731 DayZ
::Server files location
set serverLocation="D:\Steam\steamapps\common\DayZServer"
::Server Port
set serverPort=2302
::Server config
set serverConfig=serverDZ.cfg
::Logical CPU cores to use (Equal or less than available)
set serverCPU=2
::Sets title for terminal (DONT edit)
title %serverName% batch
::DayZServer location (DONT edit)
cd "%serverLocation%"
echo (%time%) %serverName% started.
::Launch parameters (edit end: -config=|-port=|-profiles=|-doLogs|-adminLog|-netLog|-freezeCheck|-filePatching|-BEpath=|-cpuCount=)@DayZ-Editor;@TerjeStartScreen;@DayZ-Expansion-Missions;@DayZ-Expansion;@CF;@Community-Online-Tools;@VPPAdminTools;@Paragon Gear and Armor;@Paragon Storage;@Paragon Arsenal;@Paragon Optics;@BulletStacksPlusPlus Paragon;@DayZ-Expansion-Bundle;@DayZ-Expansion-Vehicles;@DayZ-Expansion-Licensed;@DayZ-Expansion-Animations;@DayZ-Expansion-Core;@DayZ-Expansion-AI;@DayZ-Expansion-AI-Friendly-Addons;@DayZ-Expansion-Weapons;@DayZ-Dynamic-AI-Addon;@Dabs Framework;@AI ABDUCTORS;@AI War Zones;@Buca Weapons;@Knock Knock AI;@PvZmoD_CustomisableZombies;@More Expansion Factions;@DayZ-Expansion-Map-Assets;@DayZ-Expansion-Market;@DayZ-Expansion-Quests;@DayZ-Expansion-Missions;@DayZ Editor Loader;@BuilderItems;@Real-World Ammo & Ballistics;@Openable Ammo Cans;@Code Lock;@AI Bandits;@DayZ-Dog;@My Delta Force Weapons;@My Delta Force Medical;@My Delta Force Gear;@My Backpacks;@My Armor Pack 1;
::@DayZ-Expansion-Missions;@DayZ-Expansion;@Paragon Gear and Armor;@Paragon Storage;@Paragon Arsenal;@Paragon Optics;@BulletStacksPlusPlus Paragon;@Paragon Vending Machines;@DayZ-Expansion-Bundle;@DayZ-Expansion-Vehicles;@DayZ-Expansion-Licensed;@DayZ-Expansion-Animations;@DayZ-Expansion-Core;@DayZ-Expansion-AI;@DayZ-Expansion-AI-Friendly-Addons;@DayZ-Expansion-Weapons;@DayZ-Dynamic-AI-Addon;@Dabs Framework;@AI ABDUCTORS;@AI War Zones;@Buca Weapons;@Knock Knock AI;@PvZmoD_CustomisableZombies;@More Expansion Factions;@DayZ-Expansion-Map-Assets;@DayZ-Expansion-Market;@DayZ-Expansion-Quests;@DayZ-Expansion-Missions;@DayZ Editor Loader;@BuilderItems;@Real-World Ammo & Ballistics;@Openable Ammo Cans;@Code Lock;@AI Bandits;@DayZ-Dog;@My Delta Force Weapons;@My Delta Force Medical;@My Delta Force Gear;@My DeadIsland2 Weapons;@My CODM Weapons;@My Backpacks;@My Armor Pack 1;@My DeadIsland2 Weapons;@My CODM Weapons;
start "DayZ Server" /min "DayZServer_x64.exe" -config=%serverConfig% -port=%serverPort% "-profiles=config" "-mod=@Banov;@CF;@Dabs Framework;@Community-Online-Tools;@VPPAdminTools;@DayZ Editor Loader;@AI War Zones;@AI Bandits;@Paragon Gear and Armor;@Paragon Storage;@Paragon Arsenal;@Paragon Optics;@BulletStacksPlusPlus Paragon;@Paragon Vending Machines;@My Delta Force Weapons;@My Delta Force Medical;@My Delta Force Gear;@My DeadIsland2 Weapons;@My CODM Weapons;@My Backpacks;@My Armor Pack 1;@Terje-Compatibility-COT;@Terje-Core;@Terje-Medicine;@Terje-Skills;@Real-World Ammo & Ballistics;@Openable Ammo Cans;@PvZmoD_CustomisableZombies;@PvZmoD_Spawn_System;@PvZmoD_TheDarkHorde;@DayZ-Dynamic-AI-Addon;@DayZ-Expansion-AI-Friendly-Addons;@DayZ-Expansion-AI;@DayZ-Expansion-Core;@DayZ-Expansion-Animations;@DayZ-Expansion-Groups;@DayZ-Expansion-Hardline;@DayZ-Expansion-Licensed;@DayZ-Expansion-Map-Assets;@DayZ-Expansion-Market;@DayZ-Expansion-Missions;@DayZ-Expansion-Navigation;@DayZ-Expansion-Personal-Storage;@DayZ-Expansion-Quests;@DayZ-Expansion-Spawn-Selection;@DayZ-Expansion-Vehicles;@DayZ-Expansion-Weapons;@Knock Knock AI;@Knock Knock Zombies;@Dynamic AI Missions for DayZ Expansion AI;@Tarkov-Expansion-AI;@Svyaznoy_Project_Core;" -cpuCount=%serverCPU% -dologs -adminlog -netlog -freezecheck
::Time in seconds before kill server process (14400 = 4 hours)
timeout 14390
taskkill /im DayZServer_x64.exe /F
::Time in seconds to wait before..
timeout 10
::Go back to the top and repeat the whole cycle again
goto start
