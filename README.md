# FA Binary Patches Repository

This are some binary patches for Supreme Commander Forged Alliance. 

To apply them build or get the patcher itself from here

https://github.com/FAETHER/FA_Patcher

This are just the patch files for this game. I decided to separate them from patcher source code. 

# Change List

- Allow players to double-click to select Walls
    - hook_Walls    
- Range ring performance improvement (don't render each ring twice)
    - hook_RangeRings
- Free maximum sim rate
    - hook_DelClampMaxSimRate1
    - hook_DelClampMaxSimRate2
    - hook_DelClampMaxSimRate3
    - hook_DelClampMaxSimRate4
- Camera performance improvements
    - hook_LogParticleCap
    - hook_LogSegBuffers
    - hook_LowResolutionGCam
    - hook_LowResolutionGCam2
- Fix replays desyncing when a player leaves the game
    - hook_EndGame
    - hook_Gpg_Net_Entry
    - hook_Kill_maploader_except
    - hook_SessionEndGame
    - hook_Update_Pipeline_Stream
    - hook_decode
    - hook_instance
    - hook_recvfrom
    - hook_sendto
    - hook_sendto
    - hook_sim_dispatch
    - hook_user_input
    - hook_xact_3dapply
- Adds an amphibious mode toggle to the Salem
    - hook_luaSimGetStat
- Make LOWSELECTPRIO apply to unbuilt units
    - hook_selectionPriority
- Prevent blueprint editor being used without cheat mode
    - hook_FixOpenBPEditor
- something... ?
    - hook_UserGetDepositsAroundPoint
- Allow devs to write console commands to the log
    - hook_ConsoleLog
- Added an "ultra" graphics preset
    - hook_UnlockUltraPreset
- Stop the engine calling lua every time a plane turns
    - hook_OnMotionTurnEvent1
    - hook_OnMotionTurnEvent2
    - hook_OnMotionTurnEvent3
    
// TODO: 
Need to know what the following do:
hook_BuildUnit.cpp
hook_ObserverFix.cpp
hook_SelectUnit.cpp
hook_SetPaused.cpp
hook_SimArmyCreate.cpp
hook_SimCallback.cpp
hook_SimSetFocusArmy.cpp
hook_WayPointArrive.cpp
hook_aiinitattack.cpp
hook_aiinitattack_jmp.cpp
    