namespace Moho {

// Fully known

enum EEconResource {
	ECON_ENERGY = 0,
	ECON_MASS = 1,
};
enum class ENetProtocol {
	NETPROTO_None = 0,
	NETPROTO_TCP = 1,
	NETPROTO_UDP = 2,
};
enum class EUIState {
	UIS_none = 0,
	UIS_splash = 1,
	UIS_frontend = 2,
	UIS_game = 3,
	UIS_lobby = 4,
};
enum class EAiTargetType {
	AITARGET_None = 0,
	AITARGET_Entity = 1,
	AITARGET_Ground = 2,
};
enum class EJobType {
	JOB_None = 0,
	JOB_Build = 1,
	JOB_Repair = 2,
	JOB_Reclaim = 3,
};
enum class EFireState {
	FIRESTATE_ReturnFire = 0,
	FIRESTATE_HoldFire = 1,
	FIRESTATE_HoldGround = 2,
	FIRESTATE_Mix = -1,
};
enum class EUnitState {
	UNITSTATE_Immobile = 1,
	UNITSTATE_Moving = 2,
	UNITSTATE_Attacking = 3,
	UNITSTATE_Guarding = 4,
	UNITSTATE_Building = 5,
	UNITSTATE_Upgrading = 6,
	UNITSTATE_WaitingForTransport = 7,
	UNITSTATE_TransportLoading = 8,
	UNITSTATE_TransportUnloading = 9,
	UNITSTATE_MovingDown = 10,
	UNITSTATE_MovingUp = 11,
	UNITSTATE_Patrolling = 12,
	UNITSTATE_Busy = 13,
	UNITSTATE_Attached = 14,
	UNITSTATE_BeingReclaimed = 15,
	UNITSTATE_Repairing = 16,
	UNITSTATE_Diving = 17,
	UNITSTATE_Surfacing = 18,
	UNITSTATE_Teleporting = 19,
	UNITSTATE_Ferrying = 20,
	UNITSTATE_WaitForFerry = 21,
	UNITSTATE_AssistMoving = 22,
	UNITSTATE_PathFinding = 23,
	UNITSTATE_ProblemGettingToGoal = 24,
	UNITSTATE_NeedToTerminateTask = 25,
	UNITSTATE_Capturing = 26,
	UNITSTATE_BeingCaptured = 27,
	UNITSTATE_Reclaiming = 28,
	UNITSTATE_AssistingCommander = 29,
	UNITSTATE_Refueling = 30,
	UNITSTATE_GuardBusy = 31,
	UNITSTATE_ForceSpeedThrough = 32,
	UNITSTATE_UnSelectable = 33,
	UNITSTATE_DoNotTarget = 34,
	UNITSTATE_LandingOnPlatform = 35,
	UNITSTATE_CannotFindPlaceToLand = 36,
	UNITSTATE_BeingUpgraded = 37,
	UNITSTATE_Enhancing = 38,
	UNITSTATE_BeingBuilt = 39,
	UNITSTATE_NoReclaim = 40,
	UNITSTATE_NoCost = 41,
	UNITSTATE_BlockCommandQueue = 42,
	UNITSTATE_MakingAttackRun = 43,
	UNITSTATE_HoldingPattern = 44,
	UNITSTATE_SiloBuildingAmmo = 45,
};
enum class ESTITargetType {
	STITARGET_None = 0,
	STITARGET_Entity = 1,
	STITARGET_Position = 2,
};
enum class EUnitCommandType {
	UNITCOMMAND_None = 0,
	UNITCOMMAND_Stop = 1,
	UNITCOMMAND_Move = 2,
	UNITCOMMAND_Dive = 3,
	UNITCOMMAND_FormMove = 4,
	UNITCOMMAND_BuildSiloTactical = 5,
	UNITCOMMAND_BuildSiloNuke = 6,
	UNITCOMMAND_BuildFactory = 7,
	UNITCOMMAND_BuildMobile = 8,
	UNITCOMMAND_BuildAssist = 9,
	UNITCOMMAND_Attack = 10,
	UNITCOMMAND_FormAttack = 11,
	UNITCOMMAND_Nuke = 12,
	UNITCOMMAND_Tactical = 13,
	UNITCOMMAND_Teleport = 14,
	UNITCOMMAND_Guard = 15,
	UNITCOMMAND_Patrol = 16,
	UNITCOMMAND_Ferry = 17,
	UNITCOMMAND_FormPatrol = 18,
	UNITCOMMAND_Reclaim = 19,
	UNITCOMMAND_Repair = 20,
	UNITCOMMAND_Capture = 21,
	UNITCOMMAND_TransportLoadUnits = 22,
	UNITCOMMAND_TransportReverseLoadUnits = 23,
	UNITCOMMAND_TransportUnloadUnits = 24,
	UNITCOMMAND_TransportUnloadSpecificUnits = 25,
	UNITCOMMAND_DetachFromTransport = 26,
	UNITCOMMAND_Upgrade = 27,
	UNITCOMMAND_Script = 28,
	UNITCOMMAND_AssistCommander = 29,
	UNITCOMMAND_KillSelf = 30,
	UNITCOMMAND_DestroySelf = 31,
	UNITCOMMAND_Sacrifice = 32,
	UNITCOMMAND_Pause = 33,
	UNITCOMMAND_OverCharge = 34,
	UNITCOMMAND_AggressiveMove = 35,
	UNITCOMMAND_FormAggressiveMove = 36,
	UNITCOMMAND_AssistMove = 37,
	UNITCOMMAND_SpecialAction = 38,
	UNITCOMMAND_Dock = 39,
};
enum class EResourceType {
	RESTYPE_None = 0,
	RESTYPE_Mass = 1,
	RESTYPE_Hydrocarbon = 2,
	RESTYPE_Max = 3,
};
enum class ERuleBPUnitWeaponBallisticArc {
	RULEUBA_None = 0,
	RULEUBA_LowArc = 1,
	RULEUBA_HighArc = 2,
};
enum class ERuleBPUnitBuildRestriction {
	RULEUBR_None = 0,
	RULEUBR_Bridge = 1,
	RULEUBR_OnMassDeposit = 2,
	RULEUBR_OnHydrocarbonDeposit = 3,
};
enum ERuleBPUnitToggleCaps {
	RULEUTC_ShieldToggle = 0x1,
	RULEUTC_WeaponToggle = 0x2,
	RULEUTC_JammingToggle = 0x4,
	RULEUTC_IntelToggle = 0x8,
	RULEUTC_ProductionToggle = 0x10,
	RULEUTC_StealthToggle = 0x20,
	RULEUTC_GenericToggle = 0x40,
	RULEUTC_SpecialToggle = 0x80,
	RULEUTC_CloakToggle = 0x100,
};
enum class ERuleBPUnitMovementType {
	RULEUMT_None = 0,
	RULEUMT_Land = 1,
	RULEUMT_Air = 2,
	RULEUMT_Water = 3,
	RULEUMT_Biped = 4,
	RULEUMT_SurfacingSub = 5,
	RULEUMT_Amphibious = 6,
	RULEUMT_Hover = 7,
	RULEUMT_AmphibiousFloating = 8,
	RULEUMT_Spec = 9,
};
enum ERuleBPUnitCommandCaps {
	RULEUCC_Move = 0x1,
	RULEUCC_Stop = 0x2,
	RULEUCC_Attack = 0x4,
	RULEUCC_Guard = 0x8,
	RULEUCC_Patrol = 0x10,
	RULEUCC_RetaliateToggle = 0x20,
	RULEUCC_Repair = 0x40,
	RULEUCC_Capture = 0x80,
	RULEUCC_Transport = 0x100,
	RULEUCC_CallTransport = 0x200,
	RULEUCC_Nuke = 0x400,
	RULEUCC_Tactical = 0x800,
	RULEUCC_Teleport = 0x1000,
	RULEUCC_Ferry = 0x2000,
	RULEUCC_SiloBuildTactical = 0x4000,
	RULEUCC_SiloBuildNuke = 0x8000,
	RULEUCC_Sacrifice = 0x10000,
	RULEUCC_Pause = 0x20000,
	RULEUCC_Overcharge = 0x40000,
	RULEUCC_Dive = 0x80000,
	RULEUCC_Reclaim = 0x100000,
	RULEUCC_SpecialAction = 0x200000,
	RULEUCC_Dock = 0x400000,
	RULEUCC_Script = 0x800000,
	RULEUCC_Invalid = 0x1000000,
};
enum class EAlliance {
	ALLIANCE_Neutral = 0,
	ALLIANCE_Ally = 1,
	ALLIANCE_Enemy = 2,
};
enum EVisibilityMode {
	VIZMODE_Never = 0x1,
	VIZMODE_Always = 0x2,
	VIZMODE_Intel = 0x4,
};
enum class EIntel {
	INTEL_None = 0,
	INTEL_Vision = 1,
	INTEL_WaterVision = 2,
	INTEL_Radar = 3,
	INTEL_Sonar = 4,
	INTEL_Omni = 5,
	INTEL_RadarStealthField = 6,
	INTEL_SonarStealthField = 7,
	INTEL_CloakField = 8,
	INTEL_Jammer = 9,
	INTEL_Spoof = 10,
	INTEL_Cloak = 11,
	INTEL_RadarStealth = 12,
	INTEL_SonarStealth = 13,
};
enum class EImpactType {
	IMPACT_Invalid = 0,
	IMPACT_Terrain = 1,
	IMPACT_Water = 2,
	IMPACT_Air = 3,
	IMPACT_Underwater = 4,
	IMPACT_Projectile = 5,
	IMPACT_ProjectileUnderwater = 6,
	IMPACT_Prop = 7,
	IMPACT_Shield = 8,
	IMPACT_Unit = 9,
	IMPACT_UnitAir = 10,
	IMPACT_UnitUnderwater = 11,
};
enum class ECollisionShape {
	COLSHAPE_None = 0,
	COLSHAPE_Box = 1,
	COLSHAPE_Sphere = 2,
};
enum class EMauiKeyCode {
	MKEY_BACK = 8,
	MKEY_TAB = 9,
	MKEY_RETURN = 0xD,
	MKEY_ESCAPE = 0x1B,
	MKEY_SPACE = 0x20,
	MKEY_DELETE = 0x7F,
	MKEY_START = 0x12C,
	MKEY_LBUTTON = 0x12D,
	MKEY_RBUTTON = 0x12E,
	MKEY_CANCEL = 0x12F,
	MKEY_MBUTTON = 0x130,
	MKEY_CLEAR = 0x131,
	MKEY_SHIFT = 0x132,
	MKEY_ALT = 0x133,
	MKEY_CONTROL = 0x134,
	MKEY_MENU = 0x135,
	MKEY_PAUSE = 0x136,
	MKEY_CAPITAL = 0x137,
	MKEY_PRIOR = 0x138,
	MKEY_NEXT = 0x139,
	MKEY_END = 0x13A,
	MKEY_HOME = 0x13B,
	MKEY_LEFT = 0x13C,
	MKEY_UP = 0x13D,
	MKEY_RIGHT = 0x13E,
	MKEY_DOWN = 0x13F,
	MKEY_SELECT = 0x140,
	MKEY_PRINT = 0x141,
	MKEY_EXECUTE = 0x142,
	MKEY_SNAPSHOT = 0x143,
	MKEY_INSERT = 0x144,
	MKEY_HELP = 0x145,
	MKEY_NUMPAD0 = 0x146,
	MKEY_NUMPAD1 = 0x147,
	MKEY_NUMPAD2 = 0x148,
	MKEY_NUMPAD3 = 0x149,
	MKEY_NUMPAD4 = 0x14A,
	MKEY_NUMPAD5 = 0x14B,
	MKEY_NUMPAD6 = 0x14C,
	MKEY_NUMPAD7 = 0x14D,
	MKEY_NUMPAD8 = 0x14E,
	MKEY_NUMPAD9 = 0x14F,
	MKEY_MULTIPLY = 0x150,
	MKEY_ADD = 0x151,
	MKEY_SEPARATOR = 0x152,
	MKEY_SUBTRACT = 0x153,
	MKEY_DECIMAL = 0x154,
	MKEY_DIVIDE = 0x155,
	MKEY_F1 = 0x156,
	MKEY_F2 = 0x157,
	MKEY_F3 = 0x158,
	MKEY_F4 = 0x159,
	MKEY_F5 = 0x15A,
	MKEY_F6 = 0x15B,
	MKEY_F7 = 0x15C,
	MKEY_F8 = 0x15D,
	MKEY_F9 = 0x15E,
	MKEY_F10 = 0x15F,
	MKEY_F11 = 0x160,
	MKEY_F12 = 0x161,
	MKEY_F13 = 0x162,
	MKEY_F14 = 0x163,
	MKEY_F15 = 0x164,
	MKEY_F16 = 0x165,
	MKEY_F17 = 0x166,
	MKEY_F18 = 0x167,
	MKEY_F19 = 0x168,
	MKEY_F20 = 0x169,
	MKEY_F21 = 0x16A,
	MKEY_F22 = 0x16B,
	MKEY_F23 = 0x16C,
	MKEY_F24 = 0x16D,
	MKEY_NUMLOCK = 0x16E,
	MKEY_SCROLL = 0x16F,
	MKEY_PAGEUP = 0x170,
	MKEY_PAGEDOWN = 0x171,
	MKEY_NUMPAD_SPACE = 0x172,
	MKEY_NUMPAD_TAB = 0x173,
	MKEY_NUMPAD_ENTER = 0x174,
	MKEY_NUMPAD_F1 = 0x175,
	MKEY_NUMPAD_F2 = 0x176,
	MKEY_NUMPAD_F3 = 0x177,
	MKEY_NUMPAD_F4 = 0x178,
	MKEY_NUMPAD_HOME = 0x179,
	MKEY_NUMPAD_LEFT = 0x17A,
	MKEY_NUMPAD_UP = 0x17B,
	MKEY_NUMPAD_RIGHT = 0x17C,
	MKEY_NUMPAD_DOWN = 0x17D,
	MKEY_NUMPAD_PRIOR = 0x17E,
	MKEY_NUMPAD_PAGEUP = 0x17F,
	MKEY_NUMPAD_NEXT = 0x180,
	MKEY_NUMPAD_PAGEDOWN = 0x181,
	MKEY_NUMPAD_END = 0x182,
	MKEY_NUMPAD_BEGIN = 0x183,
	MKEY_NUMPAD_INSERT = 0x184,
	MKEY_NUMPAD_DELETE = 0x185,
	MKEY_NUMPAD_EQUAL = 0x186,
	MKEY_NUMPAD_MULTIPLY = 0x187,
	MKEY_NUMPAD_ADD = 0x188,
	MKEY_NUMPAD_SEPARATOR = 0x189,
	MKEY_NUMPAD_SUBTRACT = 0x18A,
	MKEY_NUMPAD_DECIMAL = 0x18B,
	MKEY_NUMPAD_DIVIDE = 0x18C,
};
enum class ECamTimeSource {
	TIMESOURCE_System = 0,
	TIMESOURCE_Game = 1,
};
enum class ESpecialFileType {
	SFT_SaveGame = 0,
	SFT_Replay = 1,
	SFT_CampaignSave = 3,
};
namespace CDamage {
	enum class EMethod {
		SINGLE_TARGET = 0,
		AREA_EFFECT = 1,
		RING_EFFECT = 2,
	};
};
enum ELayer {
	LAYER_None = 0x0,
	LAYER_Land = 0x1,
	LAYER_Seabed = 0x2,
	LAYER_Sub = 0x4,
	LAYER_Water = 0x8,
	LAYER_Air = 0x10,
	LAYER_Orbit = 0x20,
	LAYER_All = 0x7F,
};
enum class EScrollType {
	SCROLLTYPE_None = 0,
	SCROLLTYPE_PingPong = 1,
	SCROLLTYPE_Manual = 2,
	SCROLLTYPE_MotionDerived = 3,
};
enum class EMauiScrollAxis {
	MSA_Vert = 0,
	MSA_Horz = 1,
};
enum class EMauiEventType {
	MET_MouseMotion = 1,
	MET_MouseEnter = 2,
	MET_MouseHover = 3,
	MET_MouseExit = 4,
	MET_ButtonPress = 5,
	MET_ButtonDClick = 6,
	MET_ButtonRelease = 7,
	MET_WheelRotation = 8,
	MET_KeyUp = 9,
	MET_KeyDown = 10,
	MET_Char = 11,
};
enum class EUIActionType {
	EUIAT_None = 0,
	EUIAT_Command = 1,
	EUIAT_Build = 2,
	EUIAT_BuildAnchored = 3,
	EUIAT_Select = 4,
	EUIAT_EditGraphDrag = 5,
	EUIAT_Cancel = 7,
};
enum class EGenericIconType {
	GIT_Land = 0,
	GIT_LandHL = 1,
	GIT_Naval = 2,
	GIT_NavalHL = 3,
	GIT_Air = 4,
	GIT_AirHL = 5,
	GIT_Structure = 6,
	GIT_StructureHL = 7,
};
namespace CWldTerrainDecal {
	enum class TYPE {
		TYPE_UNDEFINED = 0,
		TYPE_ALBEDO = 1,
		TYPE_NORMALS = 2,
		TYPE_WATER_MASK = 3,
		TYPE_WATER_ALBEDO = 4,
		TYPE_WATER_NORMALS = 5,
		TYPE_GLOW = 6,
		TYPE_NORMALS_ALPHA = 7,
		TYPE_GLOW_MASK = 8,
		TYPE_ALBEDOXP = 9,
		TYPE_FORCE_DWORD = 0x7FFFFFFF,
	};
};
enum class EPulseMode {
	STAT_PULSE_NONE = 0,
	STAT_PULSE_TICK = 1,
	STAT_PULSE_FRAME = -1,
};
enum class EStatType {
	STAT_TYPE_NONE = 0,
	STAT_TYPE_FLOAT = 1,
	STAT_TYPE_INT = 2,
	STAT_TYPE_STRING = 3,
};
enum class EFootprintFlags {
	FPFLAG_None = 0,
	FPFLAG_IgnoreStructures = 1,
};
enum class ERuleBPUnitWeaponTargetType {
	RULEWTT_Unit = 0,
	RULEWTT_Projectile = 1,
	RULEWTT_Prop = 2,
};
enum EReconFlags {
	RECON_None = 0x0,
	RECON_Radar = 0x1,
	RECON_Sonar = 0x2,
	RECON_RadarSonar = RECON_Radar | RECON_Sonar,
	RECON_Omni = 0x4,
	RECON_AnyPing = RECON_RadarSonar | RECON_Omni,
	RECON_LOSNow = 0x8,
	RECON_AnySense = RECON_AnyPing | RECON_LOSNow,
	RECON_LOSEver = 0x10,
	RECON_Exposed = RECON_LOSEver | RECON_LOSNow | RECON_Omni,
	RECON_KnownFake = 0x20,
	RECON_MaybeDead = 0x40,
};
enum class EFormationdStatus { // [sic]
	FORMATIONSTATUS_FormationUpdated = 0,
	FORMATIONSTATUS_FormationAtGoal = 1,
};
enum class ECompareType {
	COMPARE_Closest = 0,
	COMPARE_Furthest = 1,
	COMPARE_HighestValue = 2,
	COMPARE_LeastDefended = 4,
};
enum class EAiNavigatorEvent {
	AINAVEVENT_Failed = 0,
	AINAVEVENT_Aborted = 1,
	AINAVEVENT_Succeeded = 2,
};
enum class EAiNavigatorStatus {
	AINAVSTATUS_Idle = 0,
	AINAVSTATUS_Thinking = 1,
	AINAVSTATUS_Steering = 2,
};
enum class EAiAttackerEvent {
	AIATTACKEVENT_AcquiredDesiredTarget = 1,
	AIATTACKEVENT_OutOfRange = 2,
	AIATTACKEVENT_Success = 4,
};
enum class EAiTransportEvent {
	AITRANSPORTEVENT_LoadedFailed = 0,
	AITRANSPORTEVENT_Load = 0,
	AITRANSPORTEVENT_Unload = 1,
};
enum class ECollisionBeamEvent {
	COLLISIONBEAMEVENT_HitTarget = 0,
	COLLISIONBEAMEVENT_MissTarget = 1,
	COLLISIONBEAMEVENT_Irrelavent = 2,
};
enum class EThreatType {
	THREATTYPE_Overall = 0,
	THREATTYPE_OverallNotAssigned = 1,
	THREATTYPE_StructuresNotMex = 2,
	THREATTYPE_Structures = 3,
	THREATTYPE_Naval = 4,
	THREATTYPE_Air = 5,
	THREATTYPE_Land = 6,
	THREATTYPE_Experimental = 7,
	THREATTYPE_Commander = 8,
	THREATTYPE_Artillery = 9,
	THREATTYPE_AntiAir = 10,
	THREATTYPE_AntiSurface = 11,
	THREATTYPE_AntiSub = 12,
	THREATTYPE_Economy = 13,
	THREATTYPE_Unknown = 14,
};
enum class ETriggerOperator {
	TRIGGER_GreaterThan = 0,
	TRIGGER_GreaterThanOrEqual = 1,
	TRIGGER_LessThan = 2,
	TRIGGER_LessThanOrEqual = 3,
};
enum class ESquadClass {
	SQUADCLASS_Unassigned = 0,
	SQUADCLASS_Attack = 1,
	SQUADCLASS_Artillery = 2,
	SQUADCLASS_Guard = 3,
	SQUADCLASS_Support = 4,
	SQUADCLASS_Scout = 5,
};
enum class ETrailParam {
	TRAIL_POSITION = 0,
	TRAIL_POSITION_X = 0,
	TRAIL_POSITION_Y = 1,
	TRAIL_POSITION_Z = 2,
	TRAIL_LIFETIME = 3,
	TRAIL_LENGTH = 4,
	TRAIL_SCALE = 5,
	TRAIL_LASTPARAM = 6,
};
enum class EBeamParam {
	BEAM_POSITION = 0,
	BEAM_POSITION_X = 0,
	BEAM_POSITION_Y = 1,
	BEAM_POSITION_Z = 2,
	BEAM_ENDPOSITION = 3,
	BEAM_ENDPOSITION_X = 3,
	BEAM_ENDPOSITION_Y = 4,
	BEAM_ENDPOSITION_Z = 5,
	BEAM_LENGTH = 6,
	BEAM_LIFETIME = 7,
	BEAM_STARTCOLOR = 8,
	BEAM_STARTCOLOR_R = 8,
	BEAM_STARTCOLOR_G = 9,
	BEAM_STARTCOLOR_B = 10,
	BEAM_STARTCOLOR_A = 11,
	BEAM_ENDCOLOR = 12,
	BEAM_ENDCOLOR_R = 12,
	BEAM_ENDCOLOR_G = 13,
	BEAM_ENDCOLOR_B = 14,
	BEAM_ENDCOLOR_A = 15,
	BEAM_THICKNESS = 16,
	BEAM_USHIFT = 17,
	BEAM_VSHIFT = 18,
	BEAM_REPEATRATE = 19,
	BEAM_LODCUTOFF = 20,
	BEAM_LASTPARAM = 21,
};
enum class EEmitterCurve {
	EMITTER_XDIR_CURVE = 0,
	EMITTER_YDIR_CURVE = 1,
	EMITTER_ZDIR_CURVE = 2,
	EMITTER_EMITRATE_CURVE = 3,
	EMITTER_LIFETIME_CURVE = 4,
	EMITTER_VELOCITY_CURVE = 5,
	EMITTER_X_ACCEL_CURVE = 6,
	EMITTER_Y_ACCEL_CURVE = 7,
	EMITTER_Z_ACCEL_CURVE = 8,
	EMITTER_RESISTANCE_CURVE = 9,
	EMITTER_SIZE_CURVE = 10,
	EMITTER_X_POSITION_CURVE = 11,
	EMITTER_Y_POSITION_CURVE = 12,
	EMITTER_Z_POSITION_CURVE = 13,
	EMITTER_BEGINSIZE_CURVE = 14,
	EMITTER_ENDSIZE_CURVE = 15,
	EMITTER_ROTATION_CURVE = 16,
	EMITTER_ROTATION_RATE_CURVE = 17,
	EMITTER_FRAMERATE_CURVE = 18,
	EMITTER_TEXTURESELECTION_CURVE = 19,
	EMITTER_RAMPSELECTION_CURVE = 20,
	EMITTER_LAST_CURVE = 21,
};
enum class EEmitterParam {
	EFFECT_POSITION = 0,
	EFFECT_POSITION_X = 0,
	EFFECT_POSITION_Y = 1,
	EFFECT_POSITION_Z = 2,
	EFFECT_TICKCOUNT = 3,
	EFFECT_LIFETIME = 4,
	EFFECT_REPEATTIME = 5,
	EFFECT_TICKINCREMENT = 6,
	EFFECT_BLENDMODE = 7,
	EFFECT_FRAMECOUNT = 8,
	EFFECT_USE_LOCAL_VELOCITY = 9,
	EFFECT_USE_LOCAL_ACCELERATION = 10,
	EFFECT_USE_GRAVITY = 11,
	EFFECT_ALIGN_ROTATION = 12,
	EFFECT_INTERPOLATE_EMISSION = 13,
	EFFECT_TEXTURE_STRIPCOUNT = 14,
	EFFECT_ALIGN_TO_BONE = 15,
	EFFECT_SORTORDER = 16,
	EFFECT_FLAT = 17,
	EFFECT_SCALE = 18,
	EFFECT_LODCUTOFF = 19,
	EFFECT_EMITIFVISIBLE = 20,
	EFFECT_CATCHUPEMIT = 21,
	EFFECT_CREATEIFVISIBLE = 22,
	EFFECT_SNAPTOWATERLINE = 23,
	EFFECT_ONLYEMITONWATER = 24,
	EFFECT_PARTICLERESISTANCE = 25,
	EFFECT_LASTPARAM = 26,
};


// Class names and serialized member names known; prefix guessed.

enum class EUnitMotionState {
	UMS_None = 0,
	UMS_Attached = 1,
	UMS_Ballistic = 2,
	UMS_Crashed = 3,
};
enum class EUnitMotionTurnEvent {
	UMTE_Straight = 0,
	UMTE_Turn = 1,
	UMTE_SharpTurn = 2,
};
enum class EUnitMotionVertEvent {
	UMVE_Bottom = 0,
	UMVE_Top = 1,
	UMVE_Up = 2,
	UMVE_Down = 3,
	UMVE_Hover = 4,
};
enum class EUnitMotionHorzEvent {
	UMHE_Stopped = 0,
	UMHE_Stopping = 1,
	UMHE_TopSpeed = 2,
};
enum class UnitWeaponRangeCategory {
	UWRC_Undefined = 0,
	UWRC_DirectFire = 1,
	UWRC_IndirectFire = 2,
	UWRC_AntiAir = 3,
	UWRC_AntiNavy = 4,
	UWRC_Countermeasure = 5,
};


// Member names unknown

enum EUnitMotionCarrierEvent : int;
enum EAirCombatState : int;

enum EOccupancyCaps : char
{
	OC_LAND = 0x1,
	OC_SEABED = 0x2,
	OC_SUB = 0x4,
	OC_WATER = 0x8,
	OC_AIR = 0x10,
	OC_ORBIT = 0x20,
};



// Class names unknown

enum class EPlatoonThreatType {
	PTT_Air = 0,
	PTT_Surface = 1,
	PTT_Sub = 2,
	PTT_Economy = 3,
};
enum class ESiloType {
	SILOTYPE_Tactical = 0x0,
	SILOTYPE_Nuke = 0x1,
};
enum EEntityType {
	ENTITYTYPE_Entity = 0x800,
	ENTITYTYPE_Projectile = 0x400,
	ENTITYTYPE_Unit = 0x100,
	ENTITYTYPE_Prop = 0x200,
};
enum class EDepositType {
	DEPOTYPE_None = 0,
	DEPOTYPE_Mass = 1,
	DEPOTYPE_Hydrocarbon = 2,
};
enum class ESolutionStatus {
	TRS_Available = 0,
	TRS_InsideMinRange = 1,
	TRS_NoSolution = 2,
	TRS_OutsideMaxRange = 3,
};
enum class ECameraAccType {
	CAMACCTYPE_Linear = 0,
	CAMACCTYPE_FastInSlowOut = 1,
	CAMACCTYPE_SlowInOut = 2,
};
enum class ECamTargetType {
	CAMTARTYPE_Location = 0,
	CAMTARTYPE_Box = 1,
	CAMTARTYPE_Entity = 2,
	CAMTARTYPE_NoseCam = 3,
	CAMTARTYPE_Hermite = 4,
};
enum class ENetCompressionMethod {
	NETCOMP_None = 0,
	NETCOMP_Deflate = 1,
};
enum EEventModifier {
	EVMOD_Shift = 0x1,
	EVMOD_Ctrl = 0x2,
	EVMOD_Alt = 0x4,
	EVMOD_Left = 0x10,
	EVMOD_Middle = 0x20,
	EVMOD_Right = 0x40,
};
enum class EMouseButton {
	MB_Right = 0,
	MB_Left = 1,
	MB_Middle = 2,
};
enum ECommandMode {
	COMMOD_None = 0x0,
	COMMOD_Order = 0x1,
	COMMOD_Build = 0x2,
	COMMOD_BuildAnchored = 0x3,
	COMMOD_Ping = 0x6,
};

};


namespace gpg {

enum class EOwnership {
	RESERVED = 0,
	UNOWNED = 1,
	OWNED = 2,
	SHARED = 3,
};

};
