# FA Binary Patches Repository

This are some binary patches for Supreme Commander Forged Alliance. 

To apply them build or get the patcher itself from here

https://github.com/FAETHER/FA_Patcher

This are just the patch files for this game. I decided to separate them from patcher source code. 

# Change List
## Fixes
- Range ring performance improvement (don't render each ring twice)
    - RangeRings
- Camera performance improvements
    - LogParticleCap
    - LogSegBuffers
    - LowResolutionGCam
    - LowResolutionGCam2
- Fix replays desyncing when a player leaves the game
    - EndGame
    - Gpg_Net_Entry
    - Kill_maploader_except
    - SessionEndGame
    - Update_Pipeline_Stream
    - decode
    - instance
    - recvfrom
    - sendto
    - sendto
    - sim_dispatch
    - user_input
    - xact_3dapply
    - SetPaused
    - SimCallback
- Prevent blueprint editor being used without cheat mode
    - FixOpenBPEditor
    - ObserverFix
- Stop the engine calling lua every time a plane turns
    - OnMotionTurnEvent1
    - OnMotionTurnEvent2
    - OnMotionTurnEvent3
- Optimised some AI actions
    - aiinitattack
    - aiinitattack_jmp
- Fix a crash when units arrive at waypoints
    - WayPointArrive

## Additions
- Allow players to double-click to select Walls
    - Walls
- Free maximum sim rate
    - DelClampMaxSimRate1
    - DelClampMaxSimRate2
    - DelClampMaxSimRate3
    - DelClampMaxSimRate4
- Adds an amphibious mode toggle to the Salem
    - luaSimGetStat
- Make `LOWSELECTPRIO` apply to units under construction
    - selectionPriority
- Allow the getting of Mass or Energy spots around a location 
    - UserGetDepositsAroundPoint
- Allow devs to write console commands to the log
    - ConsoleLog
- Added an "ultra" graphics preset
    - UnlockUltraPreset
- Allow armies to be shared by multiple players
    - SimSetFocusArmy
- Allow upgrades to be queued on units under construction
    - BuildUnit
    - SelectUnit
    - SimArmyCreate (I think....)
