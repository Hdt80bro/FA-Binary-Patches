#pragma once

#include "LuaAPI.h"
#include "enums.h"
#include "boost.h"
#include "wm3.h"



// hoist all forward declarations
struct CTask;
struct Entity;
struct ReconBlip;
struct Prop;
struct Projectile;
struct CWldSession;
struct RBlueprint;
struct Sim;
struct Unit;
struct STIMap;
struct GeomLine3;
struct CGeomHitResult;
struct CArmyImpl;
struct RRuleGameRulesImpl;



struct CScrLuaBinder {
	void Run(LuaState*) asm("0x04CD3A0");
};

typedef void (__cdecl *fn_call_t)(void);
struct CScrLuaInitForm {
	void* vtable;          // call for register lua function. 0x00E45E90 is std func
	char *FuncName;        // lua name function
	char *ClassName;       // lua class name. 0x00E00D90 - <global> if none
	char *FuncDesc;        // for log
	CScrLuaInitForm *Next; // reg func of chain
	fn_call_t FuncPtr;     // code address
	void *ClassPtr;        // C++ class type address. NULL if class none
};
VALIDATE_SIZE(CScrLuaInitForm, 0x1C)

struct CScrLuaInitFormSet {
    const char *Name;
    CScrLuaInitForm *Forms;
    bool Registered;
	CScrLuaInitFormSet* Next;

	void registerFunction(const char* methodName, const char* className, const char* help, fn_call_t fn) {

	}
};
VALIDATE_SIZE(CScrLuaInitFormSet, 0x10)

struct CScrLuaMetatableFactory {
	void* vtable;
	int index;
};

static fn_call_t* static_init asm("0xC0FA60");

void oninit(fn_call_t fn) {
	

}


CScrLuaInitFormSet coreForms asm("0xF5967C");
CScrLuaInitFormSet userForms asm("0xF5968C");
CScrLuaInitFormSet simForms asm("0xF5A120");
CScrLuaInitFormSet unsafeForms asm("0xF596C4");






// it was easier to rewrite this function than to make an assembly call
// 0x50AD80 const char *__usercall Moho::COORDS_LayerToString@<eax>(Moho::ELayer layer@<eax>)
const char *COORDS_LayerToString(Moho::ELayer layer) {
	switch (layer) {
		case Moho::LAYER_None:   return "None";
		case Moho::LAYER_Land:   return "Land";
		case Moho::LAYER_Seabed: return "Seabed";
		case Moho::LAYER_Sub:    return "Sub";
		case Moho::LAYER_Water:  return "Water";
		case Moho::LAYER_Air:    return "Air";
		case Moho::LAYER_Orbit:  return "Orbit";
		default: return "";
	}
}



// Presumes that it is the first base class of an object with a vtable.
// This means that the object can be retreived by subtracting the address by
// one. For objects without a virtual table, one of the fields slides up and
// requires a faux base class to position it where the vtable would have been.
template<class T>
struct intrusive_linked_list
{
	intrusive_linked_list<T> *list_next;
	intrusive_linked_list<T> *list_prev;

	// note that this can only be called on sliced base object pointers, not
	// the most derived object!
	T* list_item() const {
		return reinterpret_cast<T*>(this - 1);
	}
};



struct moho_set
{       // 0x20 bytes
	int baseI;
	int unk1;
	uint32_t *begin, *end, *capacity_end;
	void *unk2;
	uint32_t value; // Memory for 'Short Set Optimization'
	void *unk3;

	void set(uint32_t item, bool set) {
		auto *itemPtr = &begin[item >> 5 - baseI];
		if (itemPtr >= end) end = itemPtr + 1;
		item = 1 << (item & 0x1F);
		if (set)
			*itemPtr |= item; else
			*itemPtr &= ~item;
	}
	bool operator[](int item) {
		auto *itemPtr = &begin[item >> 5 - baseI];
		if (itemPtr >= end) return false;
		return *itemPtr & (1 << (item & 0x1F));
	}
};
VALIDATE_SIZE(moho_set, 0x20)


//namespace gpg {

template<class T, int C = 0>
struct fastvector {
	fastvector<T> *self;
	T* start;
	T* finish;
	T* capacity;
	T inline_capacity[C];
};
VALIDATE_SIZE(fastvector<int>, 0x10)

template<class T>
using fastvector16 = fastvector<T, 16>;
VALIDATE_SIZE(fastvector16<int>, 0x50)

//} // namespace gpg


// GPGCore


struct struct_VecQuat
{
	Vector3f pos;
	Quaternionf orient;
};

struct VTransform
{
	Quaternionf orient;
	Vector3f pos;
};


// for whatever reason, collision primitives seem to be backwards
struct struct_QuatB
{
	float w;
	float z;
	float y;
	float x;
};
struct struct_VecB
{
	float z;
	float y;
	float x;
};
struct struct_VecQuatB
{
	struct_QuatB quat;
	struct_VecB vec;
};

struct _Vector4f
{
	float d[4];
};

struct VMatrix4
{
	_Vector4f d[4];
};

struct Rect2i
{
	int x0;
	int y0;
	int x1;
	int y1;
};

struct CGeomHitResult
{
	float distance;
	float v1;
};
struct SPointVector
{
  Vector3f point;
  Vector3f vector;
};

struct GeomLine3
{
	Vector3f pos;
	Vector3f dir;
	float closest;
	float farthest;
};

template<class T>
struct SMinMax
{
	using type = typename T;
	T min;
	T max;
};





struct RObject : VirtualClass
{
	using vtable_t = struct vtable_robject : vtable_ {
		RType* (__thiscall *GetClass)(RObject*);
		RRef* (__thiscall *GetDerivedObjectRef)(RObject*, RRef*);
		void (__thiscall *Destroy)(RObject*, EDestroyType);
	};
	vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(vtable); }
};

template <int T, int TInfo>
struct ObjectType {
	const static int Type = T;
	const static int Info = TInfo;
};

struct CTaskStage
{
	DWORD v1;
	DWORD v2;
	DWORD v3;
	DWORD v4;
	DWORD v5;
};


struct CTaskThread
{
	DWORD previousThread;
	DWORD *gap4;
	DWORD gap8;
	CTaskStage *curThread;
	CTask *task;
	DWORD gap14;
	BYTE byte18;
};


struct CTask : VirtualClass
{
	int v1;
	int v2;
	CTaskThread *taskThread;
	CTask *subtask;
	int v5;
};
VALIDATE_SIZE(CTask, 0x18)


struct CScriptObject : RObject, intrusive_linked_list<CScriptObject>
{//0x004C6F8A, 0x34 bytes
	using vtable_t = struct vtable_cscriptobject : vtable_robject {
		string* (__thiscall *GetErrorDescription)(CScriptObject*, string*);
	};
	vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(vtable); }

	LuaObject cobj;
	LuaObject luaobj;

	void __thiscall Callback(const char* callback) asm("0x581AA0");
};
VALIDATE_SIZE(CScriptObject, 0x34)

struct WeakObject
{	// 0x8 bytes?
	void *vtable;
	void *Unk1;
};

struct gpg_mutex {
	CRITICAL_SECTION* section;
	bool iscritical;
};

struct shared_mutex : gpg_mutex {
  	int ctr;
};


struct EntityCategory
{
  DWORD v0;
  DWORD v1;
  DWORD ordinalStart;
  vector<unk_t> vec;
  DWORD v6;
  DWORD v7;
  DWORD v8;
  DWORD v9;
};


struct Stream : VirtualClass
{	// 0x1C bytes
	using vtable_t = struct vtable_stream { 
		void (__thiscall *dtr)(Stream*, EDestroyType);
		void *VirtTell;
		void *VirtSeek;
		size_t (__thiscall *VirtRead)(Stream*, void *, unsigned int);
		void *VirtReadNonBlocking;
		void *VirtUnGetByte;
		bool (__thiscall *VirtEmpty)(Stream*);
		char *(__thiscall *VirtWrite)(Stream*, char *data, size_t size);
		void (__thiscall *VirtFlush)(Stream*);
		void *VirtClose;
	};
    vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(vtable); }

	char *start;
	char *readHead;
	char *end;
	char *writeHead;
	char *writeStart;
	char *dataEnd;
};

struct struct_object_handler {
	HANDLE semaphoreObjCtr;
	HANDLE semaphoreObjSize;
	HANDLE mutex;
	DWORD size;
	DWORD ctr;
	DWORD object;
};

struct struct_stream_buffer {
	void *v0;
	void *v1;
	int data[1024];
};



struct PipeStream : Stream
{	// 0x48 bytes
	gpg_mutex lock;
	DWORD v11;
	struct_object_handler semaphore;
	struct_stream_buffer *buffer;
	struct_stream_buffer **pBuffer;
};

struct FileStream : Stream
{//0x00956DB4, 0x34 bytes
	DWORD v0;
	DWORD accessKind;
	int *buffer;
	DWORD v3;
	DWORD v4;
	DWORD v5;
};

struct StatItem : VirtualClass // : class TDatTreeItem<class StatItem>
{	// 0xA0 bytes
	// at 0x24
	int value; // int/float
	// at 0x74
	string name;
	// at 0x90
	int valueType;
	int unk2;
	// at 0x98
	gpg_mutex lock;
};

struct EngineStats : VirtualClass// : class Stats<class StatItem>
{	// 0x50 bytes
	StatItem *stat;
	gpg_mutex lock;
	string str1; // Written "stats.log"
	string str2;
	int unk2;
	BOOL unk3;
};

struct Broadcaster : VirtualClass {
  	Broadcaster *v1;
};


struct RCamCamera : VirtualClass, Broadcaster
{
};
VALIDATE_SIZE(RCamCamera, 0xC)


struct Camera // : RCamCamera
{//0x007A7972, 0x858 bytes
};
struct SCamShakeParams
{
	float v1;
	float v2;
	float v3;
	float v4;
	float v5;
	float v6;
	float minTime;
};

namespace gpg {
namespace gal {
using Matrix = VMatrix4;
}
}

struct GeomCamera3 {
	VTransform tranform;
	gpg::gal::Matrix v7;
	gpg::gal::Matrix v23;
	gpg::gal::Matrix invViewport;
	gpg::gal::Matrix v55;
	gpg::gal::Matrix v71;
	gpg::gal::Matrix v87;
	DWORD v103;
	VMatrix4 v104;
	DWORD v120;
	DWORD v121;
	DWORD v122;
	DWORD v123;
	DWORD v124;
	DWORD v125;
	DWORD v126;
	DWORD v127;
	DWORD v128;
	DWORD v129;
	DWORD v130;
	DWORD v131;
	VMatrix4 v132;
	DWORD v148;
	DWORD v149;
	DWORD v150;
	DWORD v151;
	DWORD v152;
	DWORD v153;
	DWORD v154;
	DWORD v155;
	DWORD v156;
	DWORD v157;
	DWORD v158;
	DWORD v159;
	float lodScale;
	VMatrix4 viewport;
};

struct CTaskEvent : VirtualClass
{
	int v1;
	int v2;
	int v3;
};


struct CScriptEvent : CTaskEvent, CScriptObject
{
};

struct SystemTimeSource : VirtualClass {};
struct GameTimeSource : VirtualClass {};



struct CameraImpl : RCamCamera, CScriptEvent
{
	string name;
	STIMap* stiMap;
	GeomCamera3 cam;
	DWORD v186;
	float v187;
	bool isOrtho;
	bool isRotated;
	bool revertRotation;
	bool bytesd;
	float farFOV;
	float farPitch;
	float v191;
	float heading;
	float v193;
	float targetZoom;
	float nearZoom;
	float zoom;
	Vector3f offset;
	Vector2f pivot;
	float headingRate;
	float zoomRate;
	Moho::ECamTargetType targetType;
	Vector3f targetLocation;
	AxisAlignedBox3f targetBox;
	DWORD list1;
	DWORD targetEntities;
	DWORD v216;
	DWORD v217;
	float v218;
	DWORD v219;
	Moho::ECamTimeSource timeSource;
	SystemTimeSource *systemTimeSource;
	GameTimeSource *gameTimeSource;
	float lastFrameTime;
	bool enableEaseInOut;
	bool v224b;
	bool v224c;
	bool v224d;
	float v225;
	Vector3f timedMoveOffset;
	float timedMoveZoom;
	float v230;
	float v231;
	float time;
	float timedMovePitch;
	float v234;
	Vector3f v235;
	Vector3f v238;
	float v241;
	float v242;
	float v243;
	float v244;
	float v245;
	float v246;
	SCamShakeParams camShakeParams;
	float totalTime;
	float v255;
	BYTE canShake;
	BYTE v256b;
	BYTE v256c;
	BYTE v256d;
	Moho::ECameraAccType accType;
	float v258;
	float v259;
	DWORD v260;
	DWORD soundEntitiesInFrustrum;
	DWORD v262;
	DWORD v263;
	DWORD v264;
	DWORD v265;
	DWORD v266;
	DWORD v267;
	DWORD v268;
	DWORD v269;
	DWORD v270;
	DWORD v271;
	DWORD v272;
	DWORD v273;
	DWORD v274;
	DWORD v275;
	DWORD v276;
	DWORD v277;
	DWORD v278;
	DWORD v279;
	DWORD v280;
	DWORD v281;
	DWORD v282;
	DWORD v283;
	DWORD v284;
	DWORD v285;
	DWORD v286;
	DWORD v287;
	DWORD v288;
	DWORD v289;
	DWORD v290;
	DWORD v291;
	DWORD v292;
	DWORD v293;
	DWORD v294;
	DWORD v295;
	DWORD v296;
	DWORD v297;
	DWORD v298;
	DWORD v299;
	DWORD v300;
	DWORD v301;
	DWORD v302;
	DWORD v303;
	DWORD v304;
	DWORD v305;
	DWORD v306;
	DWORD v307;
	DWORD v308;
	DWORD v309;
	DWORD v310;
	DWORD v311;
	DWORD v312;
	DWORD v313;
	DWORD v314;
	DWORD v315;
	DWORD v316;
	DWORD v317;
	DWORD v318;
	DWORD v319;
	DWORD v320;
	DWORD v321;
	DWORD v322;
	DWORD v323;
	DWORD v324;
	DWORD v325;
	DWORD v326;
	DWORD v327;
	DWORD v328;
	DWORD v329;
	DWORD v330;
	DWORD v331;
	DWORD v332;
	DWORD v333;
	DWORD v334;
	DWORD v335;
	DWORD v336;
	DWORD v337;
	DWORD v338;
	DWORD v339;
	DWORD v340;
	DWORD v341;
	DWORD v342;
	DWORD v343;
	DWORD v344;
	DWORD allUnitsInFrustrum;
	DWORD v346;
	DWORD v347;
	DWORD v348;
	DWORD v349;
	DWORD v350;
	DWORD v351;
	DWORD v352;
	DWORD v353;
	DWORD v354;
	DWORD v355;
	DWORD v356;
	DWORD v357;
	DWORD v358;
	DWORD v359;
	DWORD v360;
	DWORD v361;
	DWORD v362;
	DWORD v363;
	DWORD v364;
	DWORD v365;
	DWORD v366;
	DWORD v367;
	DWORD v368;
	DWORD v369;
	DWORD v370;
	DWORD v371;
	DWORD v372;
	DWORD v373;
	DWORD v374;
	DWORD v375;
	DWORD v376;
	DWORD v377;
	DWORD v378;
	DWORD v379;
	DWORD v380;
	DWORD v381;
	DWORD v382;
	DWORD v383;
	DWORD v384;
	DWORD v385;
	DWORD v386;
	DWORD v387;
	DWORD v388;
	DWORD v389;
	DWORD v390;
	DWORD v391;
	DWORD v392;
	DWORD v393;
	DWORD v394;
	DWORD v395;
	DWORD v396;
	DWORD v397;
	DWORD v398;
	DWORD v399;
	DWORD v400;
	DWORD v401;
	DWORD v402;
	DWORD v403;
	DWORD v404;
	DWORD v405;
	DWORD v406;
	DWORD v407;
	DWORD v408;
	DWORD v409;
	DWORD v410;
	DWORD v411;
	DWORD v412;
	DWORD v413;
	DWORD v414;
	DWORD v415;
	DWORD v416;
	DWORD v417;
	DWORD v418;
	DWORD v419;
	DWORD v420;
	DWORD v421;
	DWORD v422;
	DWORD v423;
	DWORD v424;
	DWORD v425;
	DWORD v426;
	DWORD v427;
	DWORD v428;
	DWORD armyUnitsInFrustum;
	DWORD v430;
	DWORD v431;
	DWORD v432;
	DWORD v433;
	DWORD v434;
	DWORD v435;
	DWORD v436;
	DWORD v437;
	DWORD v438;
	DWORD v439;
	DWORD v440;
	DWORD v441;
	DWORD v442;
	DWORD v443;
	DWORD v444;
	DWORD v445;
	DWORD v446;
	DWORD v447;
	DWORD v448;
	DWORD v449;
	DWORD v450;
	DWORD v451;
	DWORD v452;
	DWORD v453;
	DWORD v454;
	DWORD v455;
	DWORD v456;
	DWORD v457;
	DWORD v458;
	DWORD v459;
	DWORD v460;
	DWORD v461;
	DWORD v462;
	DWORD v463;
	DWORD v464;
	DWORD v465;
	DWORD v466;
	DWORD v467;
	DWORD v468;
	DWORD v469;
	DWORD v470;
	DWORD v471;
	DWORD v472;
	DWORD v473;
	DWORD v474;
	DWORD v475;
	DWORD v476;
	DWORD v477;
	DWORD v478;
	DWORD v479;
	DWORD v480;
	DWORD v481;
	DWORD v482;
	DWORD v483;
	DWORD v484;
	DWORD v485;
	DWORD v486;
	DWORD v487;
	DWORD v488;
	DWORD v489;
	DWORD v490;
	DWORD v491;
	DWORD v492;
	DWORD v493;
	DWORD v494;
	DWORD v495;
	DWORD v496;
	DWORD v497;
	DWORD v498;
	DWORD v499;
	DWORD v500;
	DWORD v501;
	DWORD v502;
	DWORD v503;
	DWORD v504;
	DWORD v505;
	DWORD v506;
	DWORD v507;
	DWORD v508;
	DWORD v509;
	DWORD v510;
	DWORD v511;
	DWORD v512;
	float maxZoomMult;
	DWORD v514;
};

struct CMauiControl : CScriptObject
{//0x004C6F8A, 0x11C bytes
	using Type = ObjectType<0x10C7700, 0xF83314>;
};


struct CUIWorldView : CMauiControl
{//0x004C6F8A, 0x2A8 bytes
	using Type = ObjectType<0x10C77E4, 0xF8A71C>;
	// at 0x120
	Camera *camera;
	// at 0x208
	CWldSession *session;
	void *unk1; // If shift pressed
};


struct RRuleGameRules
{//0x00529158, 0xD0 bytes
	void *vtable;
	// at 0x2C
	//list L1;
	// at 0x48
	//list L2;
	// at 0xB8
	list<RBlueprint*> Blueprints;
	//list L3;
	// at 0xC4
	//void *Blueprints;
	//void *Start, *End;
};

struct LaunchInfoNew
{//0x005423CC, 0xA4 bytes
	void *vtable;
	RRuleGameRules *rules;
	void *STIMap;
	// at 0xC
	string lua_gameMods;
	// at 0x28
	string str2;
	// at 0x60
	int unk1;
	int unk2;
	int unk3; // = -1
	// at 0x6C
	string interfaceLang;
	bool cheatsEnabled; // copied to CWldSession + 0x4D4
	char pad1[3];
	int unk4;
};

struct REffectBlueprint : RObject
{
  DWORD gap1;
  string BlueprintId;
  BYTE HighFidelity;
  BYTE MedFidelity;
  BYTE LowFidelity;
};

struct RBeamBlueprint : REffectBlueprint
{//0x0050EEFD, 0x84 bytes

  float Length;
  float Lifetime;
  float Thickness;
  float UShift;
  float VShift;
  string TextureName;
  Vector4f StartColor;
  Vector4f EndColor;
  float LODCutoff;
  float RepeatRate;
  int Blendmode;
};

struct RBlueprint : RObject
{	// ~0x60 bytes
	// at 0x4
	RRuleGameRules *owner;
	string name;
	string desc;
	// at 0x40
	string source; // example: /units/uel0001/uel0001_unit.bp
	uint32_t BlueprintOrdinal;
};

struct RMeshBlueprint : RBlueprint
{//0x0050DD83, 0x80 bytes
	// at 0x70
  	struct RMeshBlueprintLOD {
		string MeshName;
		string AlbedoName;
		string SpecularName;
		string LookupName;
		string SecondaryName;
		string ShaderName;
		float LODCutoff;
		BYTE Scrolling;
		BYTE Occlude;
		BYTE Silhouette;
	} LOD;
	float IconFadeInZoom;
	float SortOrder;
	float UniformScale;
	BOOL StraddleWater;
};

struct SFootprint {
	char SizeX;
	char SizeZ;
	char OccupancyCaps;
	char Flags;
	float MaxSlope;
	float MinWaterDepth;
	float MaxWaterDepth;
};

struct REntityBlueprint : RBlueprint
{
	vector<string> Categories;
	string ScriptModule;
	string ScriptClass;
	Moho::ECollisionShape CollisionShape;
	float SizeX;
	float SizeY;
	float SizeZ;
	float AverageDensity;
	float InertiaTensorX;
	float InertiaTensorY;
	float InertiaTensorZ;
	float CollisionOffsetX;
	float CollisionOffsetY;
	float CollisionOffsetZ;
	int DesiredShooterCap;
	SFootprint Footprint, AltFootprint;
	bool LifeBarRender;
	float LifeBarOffset;
	float LifeBarSize;
	float LifeBarHeight;
	float SelectionSizeX;
	float SelectionSizeY;
	float SelectionSizeZ;
	float SelectionCenterOffsetX;
	float SelectionCenterOffsetY;
	float SelectionCenterOffsetZ;
	float SelectionYOffset;
	float SelectionMeshScaleX;
	float SelectionMeshScaleY;
	float SelectionMeshScaleZ;
	float SelectionMeshUseTopAmount;
	float SelectionThickness;
	float UseOOBTestZoom;
	string StrategicIconName;
	BYTE StrategicIconSortPriority;
	weak_ptr<void*> StrategicIconRest;
	weak_ptr<void*> StrategicIconSelected;
  	weak_ptr<void*> StrategicIconOver;
	weak_ptr<void*> StrategicIconSelectedOver;
};


struct RPropBlueprint : REntityBlueprint
{//0x0050DD83, 0x1AC bytes
	struct RPropBlueprintDisplay {
		string MeshBlueprint;
		float UniformScale;
	} Display;
  	struct RPropBlueprintDefense {
		float MaxHealth;
		float Health;
	} Defense;
	struct RPropBlueprintEconomy {
		float ReclaimMassMax;
		float ReclaimEnergyMax;
	} Economy;
};

struct RProjectileBlueprint : REntityBlueprint
{//0x0050DD83, 0x268 bytes
	string DevStatus;
	struct RProjectileBlueprintDisplay {
		string MeshBlueprint;
		float UniformScale;
		float MeshScaleRange;
		float MeshScaleVelocity;
		float MeshScaleVelocityRange;
		bool CameraFollowsProjectile;
		float CameraFollowTimeout;
		float StrategicIconSize;
	} Display;
	struct RProjectileBlueprintEconomy {
		float BuildCostEnergy;
		float BuildCostMass;
		float BuildTime;
	} Economy;
	struct RProjectileBlueprintPhysics {
		bool CollideSurface;
		bool CollisionEntity;
		bool TrackTarget;
		bool VelocityAlign;
		bool StayUpright;
		bool LeadTarget;
		bool StayUnderwater;
		bool UseGravity;
		float DetonateAboveHeight;
		float DetonateBelowHeight;
		float TurnRate;
		float TurnRateRange;
		float Lifetime;
		float LifeTimeRange;
		float InitialSpeed;
		float InitialSpeedRange;
		float MaxSpeed;
		float MaxSpeedRange;
		float Acceleration;
		float AccelerationRange;
		float PositionX;
		float PositionY;
		float PositionZ;
		float PositionXRange;
		float PositionYRange;
		float PositionZRange;
		float DirectionX;
		float DirectionY;
		float DirectionZ;
		float DirectionXRange;
		float DirectionYRange;
		float DirectionZRange;
		float RotationalVelocity;
		float RotationalVelocityRange;
		float MaxZigZag;
		float ZigZagFrequency;
		bool DestroyOnWater;
		int MinBounceCount;
		int MaxBounceCount;
		float BounceVelDamp;
		bool RealisticOrdinance;
		bool StraightDownOrdinance;
	} Physics;
};
VALIDATE_SIZE(RProjectileBlueprint, 0x268)

struct RUnitBlueprintWeapon
{	// 0x184 bytes
	DWORD v1;
	DWORD v2;
	string Label;
	string DisplayName;
	Moho::UnitWeaponRangeCategory RangeCategory;
	bool DummyWeapon;
	bool PrefersPrimaryWeaponTarget;
	bool StopOnPrimaryWeaponBusy;
	bool SlavedToBody;
	float SlavedToBodyArcRange;
	bool AutoInitiateAttackCommand;
	float TargetCheckInterval;
	bool AlwaysRecheckTarget;
	float MinRadius;
	float MaxRadius;
	float MaximumBeamLength;
	float EffectiveRadius;
	float MaxHeightDiff;
	float TrackingRadius;
	float HeadingArcCenter;
	float HeadingArcRange;
	float FiringTolerance;
	float FiringRandomness;
	float RequiresEnergy;
	float RequiresMass;
	float MuzzleVelocity;
	float MuzzleVelocityRandom;
	float MuzzleVelocityReduceDistance;
	bool LeadTarget;
	float ProjectileLifetime;
	float ProjectileLifetimeUsesMultiplier;
	float Damage;
	float DamageRadius;
	string DamageType;
	float RateOfFire;
	string ProjectileId;
	Moho::ERuleBPUnitWeaponBallisticArc BallisticArc;
	string TargetRestrictOnlyAllow;
	string TargetRestrictOnlyDisallow;
	bool ManualFire;
	bool NukeWeapon;
	bool OverChargeWeapon;
	bool NeedPrep;
	bool CountedProjectile;
	int MaxProjectileStorage;
	bool IgnoresAlly;
	Moho::ERuleBPUnitWeaponTargetType TargetType;
	int AttackGroundTries;
	bool AimsStraightOnDisable;
	bool Turreted;
	bool YawOnlyOnTarget;
	bool AboveWaterFireOnly;
	bool BelowWaterFireOnly;
	bool AboveWaterTargetsOnly;
	bool BelowWaterTargetsonly;
	bool ReTargetOnMiss;
	bool NeedToComputeBombDrop;
	float BombDropThreshold;
	bool UseFiringSolutionInsteadOfAimBone;
	bool IgnoreIfDisabled;
	bool CannotAttackGround;
	string UIMinRangeVisualId;
	string UIMaxRangeVisualId;
};

struct RUnitBlueprint : REntityBlueprint
{//0x0050DD83, 0x568 bytes
	// at 0x17C
	struct RUnitBlueprintGeneral {
		Moho::ERuleBPUnitCommandCaps CommandCaps;
		Moho::ERuleBPUnitToggleCaps ToggleCaps;
		string UpgradesTo;
		string UpgradesFrom;
		string UpgradesFromBase;
		string SeedUnit;
		int QuickSelectPriority;
		float CapCost;
		int SelectionPriority;
	} General;

	// at 0x200
	struct RUnitBlueprintDisplay {
		string DisplayName;
		string MeshBlueprint;
		string PlaceholderMeshName;
		string IconName;
		float UniformScale;
		BYTE SpawnRandomRotation;
		BYTE HideLifebars;
	} Display;

	// at 0x278
	struct RUnitBlueprintPhysics {
		BOOL FlattenSkirt;
		float SkirtOffsetX;
		float SKirtOffsetZ;
		float SkirtSizeX;
		float SkirtSizeZ;
		float MaxGroundVariation;
		Moho::ERuleBPUnitMovementType MotionType;
		Moho::ERuleBPUnitMovementType AltMotionType;
		BYTE StandUpright;
		BYTE SinkLower;
		BYTE RotateBodyWhileMoving;
		float DiveSurfaceSpeed;
		float MaxSpeed;
		float MaxSpeedReverse;
		float MaxAcceleration;
		float MaxBrake;
		float MaxSteerForce;
		float BankingSlope;
		float RollStability;
		float RollDamping;
		float WobbleFactor;
		float WobbleSpeed;
		float TurnRadius;
		float TurnRate;
		float TurnFacingRate;
		bool RotateOnSpot;
		float RotateOnSpotThreshold;
		float Elevation;
		float AttackElevation;
		float CatchUpAcc;
		float BackUpDistance;
		float LayerChangeOffsetHeight;
		float LayerTransitionDuration;
		Moho::ELayer BuildOnLayerCaps;
		Moho::ERuleBPUnitBuildRestriction BuildRestriction;
		SFootprint *footprint;
		SFootprint *altFootprint;
		float FuelUseTime;
		float FuelRechargeRate;
		float GroundCollisionOffset;
		fastvector<unk_t> OccupRects;
		fastvector<unk_t> RaisedPlatforms;
	} Physics;

	// at 0x330
	struct RUnitBlueprintIntel {
		unsigned int VisionRadius;
		unsigned int WaterVisionRadius;
		unsigned int RadarRadius;
		unsigned int SonarRadius;
		unsigned int OmniRadius;
		bool RadarStealth;
		bool SonarStealth;
		bool Cloak;
		bool ShowIntelOnSelect;
		unsigned int RadarStealthFieldRadius;
		unsigned int SonarStealthFieldRadius;
		unsigned int CloakFieldRadius;
		SMinMax<unsigned int> JamRadius;
		BYTE JammerBlips;
		SMinMax<unsigned int> SpoofRadius;
	} Intel;

	// at 0x368
	struct RUnitBlueprintAir {
		bool CanFly;
		bool Winged;
		bool FlyInWater;
		float AutoLandTime;
		float MaxAirSpeed;
		float MinAirSpeed;
		float TurnSpeed;
		float CombatTurnSpeed;
		float StartTurnDistance;
		float TightTurnMultiplier;
		float SustainedTurnThreshold;
		float LiftFactor;
		float BankFactor;
		bool BankForward;
		float EngageDistance;
		float BreakOffTriggger;
		float BreakOffDistance;
		bool BreakOffIfNearNewTarget;
		float KMove;
		float KMoveDamping;
		float KLift;
		float KLiftDamping;
		float KTurn;
		float KTurnDamping;
		float KRoll;
		float KRollDamping;
		float CirclingTurnMult;
		float CirclingRadiusChangeMinRatio;
		float CirclingRadiusChangeMaxRatio;
		float CirclingRadiusVsAirMult;
		float CirclingElevationChangeRatio;
		float CirclingFlightChangeFrequency;
		bool CirclingDirChange;
		bool HoverOverAttack;
		float RandomBreakOffDistanceMult;
		float RandomMinChangeCombatStateTime;
		float RandomMaxChangeCombatStateTime;
		float TransportHoverHeight;
		float PredictAheadForBombDrop;
	} Air;

	// at 0x3F8
	struct RUnitBlueprintTransport {
		// at 0x400
		int TransportClass;
		int ClassGenericUpTo;
		int Class2AttachSize;
		int Class3AttachSize;
		int Class4AttachSize;
		int ClassSAttachSize;
		bool AirClass;
		int StorageSlots;
		int DockingSlots;
		float RepairsRate;
	} Transport;

	// at 0x420
	struct RUnitBlueprintDefense {
		float MaxHealth;
		float Health;
		float RegenRate;
		float AirThreatLevel;
		float SurfaceThreatLevel;
		float SubThreatLevel;
		float EconomyThreatLevel;
		string ArmorType;
		struct RUnitBlueprintDefenseShield {
			float ShieldSize;
			float RegenAssistMult;
		} Shield;
	} Defense;

	// at 0x460
	struct RUnitBlueprintAI {
		float GuardScanRadius;
		float GuardReturnRadius;
		float StagingPlatformScanRadius;
		bool ShowAssistRangeOnSelect;
		string GuardFormationName;
		bool NeedUnpack;
		bool InitialAutoMode;
		string BeaconName;
		fastvector<string> TargetBones;
		float RefuelingMultiplier;
		float RefuelingRepairAmount;
		float RepairConsumeEnergy;
		float RepairConsumeMass;
		bool AutoSurfaceToAttack;
		float AttackAngle;
	} AI;

	// at 0x4D8
	fastvector<RUnitBlueprintWeapon> Weapons;
  	DWORD gap2;

	// at 0x4E8
	struct RUnitBlueprintEconomy {
		// at 0x564
		float BuildCostEnergy;
		float BuildCostMass;
		float BuildRate;
		float BuildTime;
		float StorageEnergy;
		float StorageMass;
		bool NaturalProducer;
		vector<string> BuidableCategories;
		int gap28;
		vector<string> RebuildBonusIds;
		int gap38;
		DWORD gap;
		RRuleGameRulesImpl *rules;
		DWORD gap44;
		DWORD gap48;
		DWORD gap4C;
		vector<unk_t> vec1;
		DWORD vec1Arr[3];
		float InitialRallyX;
		float InitialRallyZ;
		bool NeedToFaceTargetToBuild;
		float SacrificeMassMult;
		float SacrificeEnergyMult;
		float MaxBuildDistance;
	} Economy;
};
struct struct_Frame
{
	DWORD v0;
	DWORD v1;
	DWORD v2;
	DWORD v3;
	DWORD v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
	LuaObject obj;
	DWORD v13;
	DWORD v14;
	DWORD v16;
};

struct CUIManager : VirtualClass // : IUIManager
{//0x0084C9CB, 0x78 bytes
	// at 0x30
	DWORD v1;
	struct_Frame **framesStart;
	struct_Frame **framesEnd;
	DWORD v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
	DWORD v8;
	DWORD v9;
	DWORD v10;
	DWORD v11;
	LuaState *state;
	DWORD v13;
	DWORD v14;
	DWORD v15;
	DWORD v16;
	DWORD v17;
	DWORD v18;
	DWORD v19;
	DWORD v20;
	DWORD v21;
	DWORD v22;
	DWORD v23;
	DWORD v24;
	DWORD v25;
	float v26;
	float v27;
	float v28;
	DWORD v29;
};

struct __declspec(align(4)) InfluenceMapEntry
{
	float overallInfluence;
	float influenceStructuresNotMex;
	float influenceStructures;
	float navalInfluence;
	float airInfluence;
	float landInfluence;
	float experimentalInfluence;
	float commanderInfluence;
	float artilleryInfluence;
	float antiAirInfluence;
	float antiSurfaceInfluence;
	float antiSubInfluence;
	float economyInfluence;
	float unknownInfluence;
};


struct InfluenceMap
{
	DWORD v0;
	DWORD v1;
	DWORD v2;
	fastvector<InfluenceMapEntry> entries;
	InfluenceMapEntry threat;
	InfluenceMapEntry decay;
};


struct InfluenceGrid
{
	CArmyImpl *army;
	DWORD total;
	DWORD width;
	DWORD height;
	DWORD gridSize;
	DWORD v5;
	DWORD vec;
	DWORD v7;
	fastvector<InfluenceMap> mapEntries;
};


struct CAiReconDBImpl : VirtualClass // : IAiReconDB
{//0x005BFFB8, 0xB0 bytes
	DWORD v0;
	DWORD blipDB;
	DWORD v2;
	DWORD blips;
	DWORD v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
	ReconBlip **blipEventsStart;
	ReconBlip **blipEventsEnd;
	DWORD v10;
	CArmyImpl *army;
	STIMap *mapdata;
	Sim *sim;
	InfluenceGrid *igrid;
	weak_ptr<CIntelGrid> m_visionGrid;
	weak_ptr<CIntelGrid> m_waterGrid;
	weak_ptr<CIntelGrid> m_radarGrid;
	weak_ptr<CIntelGrid> m_sonarGrid;
	weak_ptr<CIntelGrid> m_omniGrid;
	weak_ptr<CIntelGrid> m_rsiGrid;
	weak_ptr<CIntelGrid> m_sciGrid;
	weak_ptr<CIntelGrid> m_vciGrid;
	DWORD v31;
	DWORD v32;
	DWORD v33;
	DWORD v34;
	unsigned int *vec1Start;
	unsigned int *vec1End;
	DWORD v37;
	DWORD v38;
	DWORD v39;
	DWORD v40;
	BYTE fogOfWar;
	BYTE v40b;
	BYTE v40c;
	BYTE v40d;
	DWORD v42;
};

struct IClientManager
{
	void* vtable;
};

struct IClient : VirtualClass
{
	using vtable_t = struct vtable_iclient : vtable_ {
		void *dtr;
		bool (__thiscall *field_4)(IClient*);
		void *field_8;
		void *field_C;
		DWORD *(__thiscall *field_10)(IClient*);
		DWORD *(__thiscall *field_14)(IClient*, DWORD*);
		void *field_18;
		void (__thiscall *Dtr)(IClient*, int);
		void *field_20;
		void *field_24;
		void *field_28;
		void *field_2C;
		void *field_30;
		void *field_34;
		void (__thiscall *Open)(CClientBase*, shared_mutex**);
		void *Debug;
	};
    vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(vtable); }

  	string mNickname;
  	DWORD mIndex;
  	DWORD launchInfo;
};

struct RWldMapPreviewChunk
{
  DWORD v0;
  DWORD v1;
  DWORD v2;
  DWORD v3;
  string v4;
};

struct Cartographic : VirtualClass
{
  BYTE byte4;
  DWORD dword8;
  DWORD dwordC;
  DWORD dword10;
  DWORD dword14;
  DWORD dword18;
  DWORD dword1C;
  DWORD dword20;
  DWORD dword24;
  DWORD dword28;
  DWORD dword2C;
  DWORD dword30;
  BYTE byte34;
  DWORD dword38;
  DWORD dword3C;
  DWORD dword40;
  DWORD dword44;
  DWORD dword48;
  DWORD dword4C;
  DWORD dword50;
  DWORD dword54;
  BYTE gap58[4];
  DWORD dword5C;
  DWORD dword60;
  DWORD dword64;
  DWORD dword68;
  DWORD dword6C;
  DWORD dword70;
  DWORD dword74;
  DWORD dword78;
  DWORD dword7C;
  DWORD dword80;
  DWORD dword84;
  DWORD dword88;
  DWORD dword8C;
  DWORD dword90;
  DWORD dword94;
  DWORD dword98;
  DWORD dword9C;
  DWORD dwordA0;
};

struct SkyDome : VirtualClass
{
  BYTE gap4[4];
  DWORD dword8;
  DWORD dwordC;
  DWORD dword10;
  DWORD dword14;
  BYTE gap18[20];
  DWORD dword2C;
  float dword30;
  float dword34;
  DWORD dword38;
  DWORD dword3C;
  float dword40;
  float dword44;
  float dword48;
  float dword4C;
  float dword50;
  float dword54;
  float dword58;
  string horizon;
  DWORD dword78;
  BYTE gap7C[4];
  BYTE byte80;
  BYTE gap81[15];
  DWORD dword90;
  DWORD dword94;
  BYTE gap98[4];
  BYTE byte9C;
  BYTE gap9D[15];
  DWORD dwordAC;
  DWORD dwordB0;
  BYTE gapB4[4];
  DWORD dwordB8;
  DWORD dwordBC;
  BYTE gapC0[4];
  BYTE byteC4;
  BYTE gapC5[15];
  DWORD dwordD4;
  DWORD dwordD8;
  BYTE gapDC[4];
  BYTE byteE0;
  BYTE gapE1[15];
  DWORD dwordF0;
  DWORD dwordF4;
  BYTE gapF8[4];
  BYTE byteFC;
  BYTE gapFD[15];
  DWORD dword10C;
  DWORD dword110;
  DWORD dword114;
  DWORD dword118;
  DWORD dword11C;
  DWORD dword120;
  string clouds;
  char char140;
  BYTE gap141[79];
  DWORD dword190;
  DWORD dword194;
  DWORD dword198;
  DWORD dword19C;
  DWORD dword1A0;
  DWORD dword1A4;
  DWORD dword1A8;
  DWORD dword1AC;
  DWORD dword1B0;
  DWORD dword1B4;
  DWORD dword1B8;
  DWORD dword1BC;
  DWORD dword1C0;
  DWORD dword1C4;
  BYTE byte1C8;
  DWORD dword1CC;
  DWORD dword1D0;
  DWORD dword1D4;
  DWORD dword1D8;
  DWORD dword1DC;
  DWORD dword1E0;
  DWORD dword1E4;
  DWORD dword1E8;
  DWORD dword1EC;
  DWORD dword1F0;
  DWORD dword1F4;
  DWORD dword1F8;
  DWORD dword1FC;
  DWORD dword200;
  DWORD dword204;
  DWORD dword208;
  DWORD dword20C;
  DWORD dword210;
  DWORD dword214;
  DWORD dword218;
  DWORD dword21C;
  DWORD dword220;
};

struct CWaterShaderProperties
{
  DWORD dword0;
  DWORD dword4;
  float dword8;
  float dwordC;
  float dword10;
  float dword14;
  float dword18;
  float dword1C;
  float dword20;
  float dword24;
  float dword28;
  float dword2C;
  float dword30;
  float dword34;
  float dword38;
  float dword3C;
  float dword40;
  float dword44;
  float dword48;
  float dword4C;
  float dword50;
  float dword54;
  float dword58;
  float dword5C;
  float dword60;
  Vector3f wm3__vector3f64;
  Vector3f wm3__vector3f70;
  float dword7C;
  float dword80;
  string waves[4];
  string waterCubemap;
  string waterRamp;
  char char12C;
  BYTE gap12D[31];
  DWORD dword14C;
  DWORD dword150;
  DWORD dword154;
  DWORD dword158;
};
struct MemBuffer
{
  shared_ptr<char> data;
  void *begin;
  void *end;
};


struct TextureContext : VirtualClass
{
  DWORD source;
  string location;
  MemBuffer res1;
  DWORD type;
  DWORD usage;
  DWORD format;
  DWORD mipmapLevels;
  DWORD v17;
  DWORD width;
  DWORD height;
  DWORD v20;
};


struct CD3DDynamicTextureSheet
{
  DWORD vtable;
  DWORD dword4;
  DWORD dword8;
  DWORD dwordC;
  DWORD dword10;
  DWORD dword14;
  TextureContext context;
  BYTE byte6C;
};

struct CStratumMaterial
{
  string path;
  float v1;
  float v2;
  DWORD v3;
  float v4;
  DWORD v5;
  DWORD v6;
  float v7;
};


struct CStrata
{
  BYTE byte0;
  BYTE byte1;
  string shaderName;
  DWORD v1;
  DWORD v2;
  weak_ptr<CD3DDynamicTextureSheet> stratumMask0;
  weak_ptr<CD3DDynamicTextureSheet> stratumMask1;
  CStratumMaterial std__string38;
  CStratumMaterial std__string70;
  CStratumMaterial std__stringA8;
  CStratumMaterial std__stringE0;
  CStratumMaterial std__string118;
  CStratumMaterial str;
  CStratumMaterial str4;
  CStratumMaterial str3;
  CStratumMaterial str2;
  CStratumMaterial std__string230;
  CStratumMaterial std__string268;
  CStratumMaterial std__string2A0;
  CStratumMaterial std__string2D8;
  CStratumMaterial std__string310;
  CStratumMaterial std__string348;
  CStratumMaterial str6;
  CStratumMaterial str5;
  CStratumMaterial str7;
  CStratumMaterial str8;
  CStratumMaterial str9;
};
struct struct_session_subres3
{
  DWORD v0;
  Rect2i v1;
  DWORD v5;
  DWORD v6;
  DWORD v7;
  DWORD v8;
  DWORD v9;
  DWORD v10;
  DWORD v11;
  DWORD v12;
  DWORD v13;
  DWORD v14;
  DWORD v15;
  DWORD v16;
  struct_session_subres3 **subres2_start;
  struct_session_subres3 **subres2_end;
  DWORD v19;
  DWORD v20;
  int **subres1_start;
  DWORD subres1_end;
  DWORD v23;
};

struct struct_session_res3
{
  DWORD v0;
  struct_session_subres3 **data;
  struct_session_subres3 **data_end;
  DWORD v3;
  DWORD v4;
  DWORD v5;
  DWORD v6;
  DWORD v7;
  DWORD v8;
  DWORD v9;
  DWORD v10;
  DWORD v11;
  DWORD v12;
  DWORD v13;
  DWORD v14;
  DWORD v15;
  DWORD v16;
  DWORD v17;
  DWORD v18;
  DWORD v19;
  DWORD v20;
  DWORD v21;
  DWORD v22;
  DWORD v23;
  DWORD v24;
  DWORD v25;
  DWORD v26;
  DWORD v27;
  int width1;
  int width2;
  DWORD v30;
  DWORD v31;
  DWORD size;
};


struct WaveSystem
{
  DWORD vtable;
  DWORD v1;
  struct_session_res3 v2;
  DWORD v35;
  DWORD v36;
  DWORD v37;
  DWORD v38;
  DWORD v39;
  DWORD v40;
  DWORD v41;
  DWORD v42;
  DWORD v43;
  DWORD v44;
  DWORD v45;
};

struct __declspec(align(4)) CDecalManager : VirtualClass
{
  DWORD v1;
  DWORD numDecals;
  DWORD v3;
  DWORD v4;
  DWORD v5;
  DWORD v6;
  DWORD v7;
  DWORD v8;
  DWORD v9;
  DWORD v10;
  DWORD v11;
  DWORD v12;
  DWORD v13;
  DWORD v14;
  DWORD v15;
  DWORD v16;
  DWORD v17;
  DWORD v18;
  DWORD v19;
  DWORD v20;
  struct_session_res3 v21;
  DWORD v54;
  DWORD v55;
  DWORD v56;
  CWldTerrainRes *wldTerrain;
  int v58[10];
  bool v68;
};

struct CWldTerrainRes : VirtualClass
{
  STIMap *map;
  bool gap8a;
  bool editMode;
  bool gap8c;
  bool gap8d;
  Cartographic cartographic;
  SkyDome skyDome;
  BYTE gap2D4[4];
  float lightingMultiplier;
  Vector3f sunDirection;
  Vector3f sunAmbience;
  Vector3f sunColor;
  Vector3f shadowFillColor;
  Vector4f specularColor;
  float bloom;
  float fogInfo[5];
  DWORD topographicSamples;
  DWORD *hypsometricColor;
  DWORD dword33C;
  DWORD dword340;
  DWORD dword344;
  DWORD dword348;
  float imagerElevationOffset;
  CWaterShaderProperties waterShaderProperties;
  CStrata strata;
  weak_ptr<unk_t> normalMap;
  DWORD normalMapEnd;
  DWORD dword950;
  DWORD normalMapWidth;
  int normalMapHeight;
  string backgroundFile;
  weak_ptr<CD3DDynamicTextureSheet> textureSheet;
  string str1;
  DWORD dword99C;
  DWORD dword9A0;
  BYTE envLookup[4];
  DWORD dword9A8;
  DWORD dword9AC;
  BYTE gap9B0[4];
  DWORD dword9B4;
  DWORD dword9B8;
  DWORD dword9BC;
  weak_ptr<CD3DDynamicTextureSheet> waterMap;
  unsigned __int8 *waterFoam;
  unsigned __int8 *waterFlatness;
  unsigned __int8 *waterDepthBias;
  BitArray2D *debugDirtyTerrain;
  BYTE gap9D8[4];
  DWORD vec1;
  DWORD vec1End;
  DWORD gap9E4;
  WaveSystem waveSystem;
  BYTE gapAA0[400];
  CDecalManager *decalManager;
  DWORD dwordC34;
};



struct CWldMap
{
	RWldMapPreviewChunk *mapPreviewChunk;
	CWldTerrainRes *terrainRes;
	DWORD props;
};

struct SSTICommandSource
{       // 0x24 bytes
	int index;
	string name;
	int protocol; // -1 SinglePlayer, 3 MultiPlayer
};

struct Deposit
{	// 0x14 bytes
	int X1,Z1,X2,Z2; // Rect
	int Type; // 1 - Mass, 2 - Energy
};
VALIDATE_SIZE(Deposit, 0x14);

struct CSimResources // : ISimResources // : IResources
{//0x007444EF, 0x1C bytes
	void *vtable;
	// at 0x8 in vtable
	// ecx:CreateResourceDeposit(type, x, y, z, size)
	// at 0x28 in vtable
	// ecx:FindResourceDeposit(PtrPosXZ, PtrResultXZ, Radius, Type):Bool

	gpg_mutex lock;
	uint8_t pad[0x4];
	// at 0x10
	list<Deposit> deposits;
};
VALIDATE_SIZE(CSimResources, 0x1C)

struct LaunchInfoBase : VirtualClass
{
  DWORD gamerules;
	STIMap *map;
  string gameMods;
  string scenarioInfo;
  DWORD armyLaunchInfo;
  int *vec2_start;
  int *vec2_end;
  DWORD vec2_end2;
  vector<SSTICommandSource> commandSources;
  string language;
  BYTE cheatsEnabled;
  BYTE v34;
  BYTE v35;
  BYTE v36;
};

struct LaunchInfoNew : LaunchInfoBase
{
  DWORD props;
  DWORD strVec;
  DWORD armyStart;
  DWORD armyEnd;
  DWORD v39;
  DWORD initSeed;
};


struct LaunchInfoLoad : LaunchInfoBase
{
  DWORD props;
  DWORD strVec;
  DWORD armyStart;
  DWORD armyEnd;
  DWORD v39;
};



struct SWldSessionInfo
{	// 0x30 bytes

  string mapname;
  weak_ptr<LaunchInfoBase> launch_info;
  bool isBeingRecorded;
  bool isReplay;
  bool isMultiplayer;
  CClientManagerImpl *clientManager;
  unsigned int sourceId;
};

struct CAiPersonality : CScriptObject
{
	DWORD v0;
	string personalityName;
	string charPersonality;
	SMinMax<float> armySize;
	SMinMax<float> platoonSize;
	SMinMax<float> attackFrequency;
	SMinMax<float> repeatAttackFrequency;
	SMinMax<float> counterForces;
	SMinMax<float> intelGathering;
	SMinMax<float> coordinatedAttacks;
	SMinMax<float> expansionDriven;
	SMinMax<float> techAdvancement;
	SMinMax<float> upgradesDriven;
	SMinMax<float> defenseDriven;
	SMinMax<float> economyDriven;
	SMinMax<float> factoryTycoon;
	SMinMax<float> intelBuildingTycoon;
	SMinMax<float> superWeaponTendency;
	vector<string> favouriteStructures;
	SMinMax<float> airUnitsEmphasis;
	SMinMax<float> tankUnitsEmphasis;
	SMinMax<float> botUnitsEmphasis;
	SMinMax<float> seaUnitsEmphasis;
	SMinMax<float> specialtyForcesEmphasis;
	SMinMax<float> supportUnitsEmphasis;
	SMinMax<float> directDamageEmphasis;
	SMinMax<float> inDirectDamageEmphasis;
	vector<string> favouriteUnits;
	SMinMax<float> survivalEmphasis;
	SMinMax<float> teamSupport;
	SMinMax<float> formationUse;
	SMinMax<float> targetSpread;
	SMinMax<float> quittingTendency;
	SMinMax<float> chatFrequency;
	float difficulty;
};
VALIDATE_SIZE(CAiPersonality, 0x17C)


struct CAiBrain : CScriptObject
{
	CArmyImpl* army;
	CArmyImpl* currentEnemy;
	CAiPersonality* personality;
	string currentPlan;
  	vector<SPointVector> attackVectors;
	DWORD v13;
	DWORD v14;
	vector<unk_t> vec2;
	fastvector<int> vec3;
	DWORD v23;
	DWORD v24;
	DWORD v25;
	DWORD v26;
	DWORD v27;
  	Sim *sim;
  	Sim *sim;
  	CTaskStage* aiThread2;
  	CTaskStage* lAttackerThreads;
	DWORD v32;
};
VALIDATE_SIZE(CAiBrain, 0xB8)

struct struct_ThreatTable
{
	CArmyImpl *army;
	DWORD v1;
	DWORD width;
	DWORD height;
	DWORD size;
	DWORD v5;
	DWORD vec;
	DWORD v7;
	DWORD v8;
	DWORD arr;
	DWORD v10;
	DWORD v11;
};

template<class T>
struct struct_Resources
{
	T ENERGY;
	T MASS;
};

struct struct_Economy
{
	struct_Resources<float> mStored;
	struct_Resources<float> mIncome;
	struct_Resources<float> mReclaimed;
	struct_Resources<float> mLastUseRequested;
	struct_Resources<float> mLastUseActual;
	struct_Resources<double> mMaxStorage;
};
VALIDATE_SIZE(struct_Economy, 0x38)

struct struct_EconomyData
{
	Sim *sim;
	DWORD index;
  	struct_Resources<float> resources;
	DWORD v4;
	DWORD v5;
	struct_Economy economy;
  	struct struct_ExtraStorage {
		struct_EconomyData *economy;
		struct_Resources<float> amt;
	} *extraStorage;
	bool isResourceSharing;
	DWORD v24;
};
VALIDATE_SIZE(struct_EconomyData, 0x60)

struct CIntelGrid
{
	STIMap *mapdata;
	BYTE *grid;
	int width;
	int height;
	int v4;
	int v5;
	int v6;
	int v7;
	int gridSize;
};
VALIDATE_SIZE(CIntelGrid, 0x24)

struct struct_ReconGrid
{
	DWORD armyIndex;
	string armyName;
	string playerName;
	bool isCivilian;
	BYTE v16b;
	BYTE v16c;
	BYTE v16d;
	weak_ptr<CIntelGrid> exploredReconGrid;
	weak_ptr<CIntelGrid> fogReconGrid;
	weak_ptr<CIntelGrid> waterReconGrid;
	weak_ptr<CIntelGrid> radarReconGrid;
	weak_ptr<CIntelGrid> sonarReconGrid;
	weak_ptr<CIntelGrid> omniReconGrid;
	weak_ptr<CIntelGrid> rciReconGrid;
	weak_ptr<CIntelGrid> sciReconGrid;
};

struct __unaligned __declspec(align(4)) struct_ArmyData
{
	struct_Economy data;
	DWORD v47;
	DWORD v48;
	moho_set neutrals;
	moho_set allies;
	moho_set enemies;
	bool isAlly;
	BYTE v73b;
	BYTE v73c;
	BYTE v73d;
	DWORD v74;
	moho_set mValidCommandSources;
	DWORD playerColor;
	DWORD armyColor;
	string mArmyType;
	DWORD faction;
	DWORD v93;
	DWORD v94;
	DWORD v95;
	DWORD v96;
	DWORD v97;
	DWORD v98;
	bool showScore;
	BYTE v99b;
	BYTE v99c;
	BYTE v99d;
	DWORD v100;
	DWORD v101;
	DWORD v102;
	DWORD v103;
	DWORD v104;
	DWORD v105;
	DWORD v106;
	DWORD v107;
	DWORD v108;
	DWORD v109;
	DWORD v110;
	bool isOutOfGame;
	BYTE v11b;
	BYTE v11c;
	BYTE v11d;
	float armystartX;
	float armystartZ;
	int norushtimer;
	float norushradius;
	float norushoffsetx;
	float norushoffsety;
	float hasHandicap;
	float handicap;
};
// ignore if this throws an error, using `struct_Economy` as a field makes the class align up to 0x160
VALIDATE_SIZE(struct_ArmyData, 0x15C)

struct BaseArmy : struct_ReconGrid, struct_ArmyData
{
};
// the same
VALIDATE_SIZE(BaseArmy, 0x1DC);

struct SimArmy : BaseArmy
{
};


struct CArmyStats
{
	void *vtable;
	int v1;
	int v2;
	int v3;
	CAiBrain *brain;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v10;
};
VALIDATE_SIZE(CArmyStats, 0x2C)

struct SOCellPos
{
  __int16 x;
  __int16 z;
};


struct CAiPathFinder
{
  void *vtable;
  DWORD v1;
  DWORD v2;
  DWORD v3;
  DWORD v4;
  bool v5a;
  bool v5b;
  bool v5c;
  bool v5d;
  Unit* unit;
  SFootprint* footprint;
  SFootprint* altFootprint;
  Moho::ERuleBPUnitMovementType motionType;
  Sim* unitSim;
  CAiPathFinder* armyPathfinder;
  struct_poi *poi1;
  SOCellPos currentPos;
  DWORD v14;
  DWORD v15;
  DWORD v16;
  DWORD v17;
  DWORD v18;
  DWORD v19;
  DWORD v20;
  DWORD v21;
  DWORD v22;
  DWORD v23;
  DWORD v24;
  bool v25a;
  bool v25b;
  bool v25c;
  bool v25d;
  DWORD v26;
  DWORD vec;
  DWORD v28;
  bool useWholeMap;
  bool isInMap;
  bool v29c;
  bool v29d;
  DWORD size;
};




struct IArmy : VirtualClass {
	using vtable_t = struct vtable_carmyimpl : vtable_ {
  void* dtr;
  Sim* (__thiscall *GetSim)(CArmyImpl*);
  BOOL (__thiscall *IsHuman)(CArmyImpl*);
  const char *(__thiscall *ArmyType)(CArmyImpl*);
  void (__thiscall *SetArmyPlans)(CArmyImpl*, string*);
  void *field_14;
  InfluenceGrid *(__thiscall *GetIGrid)(CArmyImpl*);
  CAiBrain *(__thiscall *GetArmyBrain)(CArmyImpl*);
	CAiReconDBImpl *(__thiscall *GetReconDB)(CArmyImpl*);
  struct_EconomyData *(__thiscall *GetEconomy)(CArmyImpl*);
  int (__thiscall *GenerateArmyStart)(CArmyImpl*);
  void (__thiscall *SetArmyStart)(CArmyImpl*, Vector2f *);
  Vector2f *(__thiscall *GetArmyStartPos)(CArmyImpl*, Vector2f*);
  void (__thiscall *SetAlliance)(CArmyImpl*, BaseArmy *, Moho::EAlliance);
  int (__thiscall *field_38)(CArmyImpl*, DWORD *);
  void *OnTick;
  void *field_40;
  void *field_44;
  int (__thiscall *GetArmyStats)(CArmyImpl*);
  double (__thiscall *GetArmyUnitCostTotal)(CArmyImpl*);
  CAiPathFinder *(__thiscall *GetPathFinder)(CArmyImpl*);
  void *field_54;
  void *field_58;
  void *field_5C;
  void *GetPlatoonsList;
  CPlatoon *(__thiscall *MakePlatoon)(CArmyImpl*, const char *, const char *);
  CPlatoon *(__thiscall *GetPlatoon)(CArmyImpl*, const char *);
  int (__thiscall *field_6C)(CArmyImpl*, int, int *);
  void (__thiscall *DisbandPlatoonUniquelyNamed)(CArmyImpl*, const char *);
  void (__thiscall *DisbandPlatoon)(CArmyImpl*, CPlatoon *);
  void (__thiscall *field_78)(CArmyImpl*, int *, const char *);
  void *field_7C;
  void (__thiscall *field_80)(CArmyImpl*, moho_set*);
  int (__thiscall *GetNumPlatoonsTemplateNamed)(CArmyImpl*, const char *);
  int (__thiscall *GetNumPlatoonsWithAI)(CArmyImpl*, const char *);
  void *field_8C;
  void *field_90;
  void *field_94;
  void *field_98;
  void (__thiscall *GetUnits)(CArmyImpl*, int *, CScriptObject *);
  void *field_A0;
  double (__thiscall *GetUnitCap)(CArmyImpl*);
  void (__thiscall *SetUnitCap)(CArmyImpl*, int);
  unsigned __int8 (__thiscall *IgnoreUnitCap)(CArmyImpl*);
  void (__thiscall *SetUseUnitCap)(CArmyImpl*, int);
  void (__thiscall *SetIgnorePlayableRect)(CArmyImpl*, BOOL);
  int (__thiscall *UseWholeMap)(CArmyImpl*);
  void (__thiscall *AddBuildRestriction)(CArmyImpl*, EntityCategory *);
  void (__thiscall *RemoveBuildRestriction)(CArmyImpl*, EntityCategory *);
  void *SetNoRushTimer;
  void *SetNoRushRadius;
  void *SetNoRushOffset;
  void *GetPathcapLand;
  void *GetPathcapSea;
	};
	vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(vtable); }

	DWORD v0;
};

struct CArmyImpl : IArmy, SimArmy
{
	DWORD v120;
	Sim *sim;
	CAiBrain *brain;
	CAiReconDBImpl *reconDB;
	struct_EconomyData *economy;
	string v125;
	CArmyStats *armyStats;
	struct_ThreatTable *v133;
	DWORD v134;
	DWORD v135;
	DWORD v136;
  	CPlatoon **platoonsStart;
  	CPlatoon **platoonsEnd;
  	DWORD platoonsCapacity;
	DWORD v140;
	DWORD v141;
	DWORD v142;
	DWORD v143;
	DWORD v144;
	DWORD v145;
	DWORD v146;
	DWORD v147;
	DWORD v148;
	DWORD v149;
	DWORD v150;
	DWORD v151;
	DWORD v152;
	DWORD v153;
	DWORD v154;
	float unitcap;
	DWORD ignoreUnitCap;
	DWORD pathcap_land;
	DWORD pathcap_sea;
	DWORD pathcap_both;
	DWORD v160;
};
VALIDATE_SIZE(CArmyImpl, 0x288);

struct UserArmy : BaseArmy
{	// 0x210 bytes
	// at 0x1DC
	uint8_t unk12[8];
	// at 0x1E4
	CWldSession *session;
	uint8_t unk13[0x28];
};
VALIDATE_SIZE(UserArmy, 0x210);

struct Entities
{	// 0x50 bytes
};

struct EntityChain // [[Entities+4]+4]
{
	void *next;
	//void *?;
	//void *?;
	int ID;
	void *entity;
};

// subobject of the point of interest structure 
struct struct_subpoi
{
	DWORD width;
	DWORD height;
	DWORD lastIndex;
	DWORD height2;
	int *arr1;
	int *arr2;
	int *arr3;
	DWORD v8;
	DWORD v9;
	DWORD v10;
	void **start;
	void **end;
	DWORD v13;
};

struct EntityAttributes
{
	DWORD v0;
	DWORD v1;
	DWORD v2;
	DWORD v3;
	DWORD v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
};


struct SSTIEntityVariableData
{
	DWORD scmResource;
	DWORD dword4;
	DWORD mesh;
	Vector3f scale;
	float health;
	float maxHealth;
	bool isBeingBuilt;
	bool isDead;
	bool requestRefreshUI;
	Quaternionf transform;
	Vector3f pos;
	VTransform lastTransform;
	float dword5C;
	float fractionComplete;
	DWORD dword64;
	DWORD dword68;
	DWORD dword6C;
	DWORD dword70;
	DWORD dword74;
	DWORD v7;
	DWORD v8;
	QWORD qword80;
	QWORD qword88;
	DWORD ambientSound;
	DWORD rumbleSound;
	BYTE byte98;
	DWORD dword9C;
	Moho::ELayer layer;
	BYTE byteA4;
	DWORD dwordA8;
	DWORD dwordAC;
	EntityAttributes intel;
};

struct CColPrimitive
{
	void *vtable;
	struct_VecQuatB v0;
};



struct Entity : CScriptObject, CTask
{
	using vtable_t = struct vtable_entity : vtable_cscriptobject {
		Unit *(__thiscall *IsUnit)(Entity *);
		Prop *(__thiscall *IsProp)(Entity *);
		Projectile *(__thiscall *IsProjectile)(Entity *);
		ReconBlip *(__thiscall *IsBlip)(Entity *);
		void *(__thiscall *IsCollisionBeam)(Entity *);
		void *(__thiscall *IsShield)(Entity *);
		int (__thiscall *GetBoneCount)(Entity *);
		int (__thiscall *IsBeingBuilt)(Entity *);
		int (__thiscall *Sync)(Entity *);
		int (__thiscall *SetMesh)(Entity *);
		int (__thiscall *GetUnitformScale)(Entity *);
		Vector3f *(__thiscall *GetVelocity)(Entity *, Vector3f *);
		int (__thiscall *IsMobile)(Entity *);
		void (__thiscall *Warp)(Entity *, VTransform *);
		void (__thiscall *GetBoneWorldTransform)(VTransform *);
		void (__thiscall *GetBoneLocalTransform)(VTransform *);
		int (__thiscall *MotionTick)(Entity *);
		void (__thiscall *SetMotor)(Entity *);
		void (__thiscall *GetAttachedEntities)(Entity *);
		void (__thiscall *AttachTo)(Entity *);
		void (__thiscall *DetachFrom)(Entity *, bool);
		void (__thiscall *AttachedEntityDestroyed)(Entity *);
		void (__thiscall *AttachedEntityKilled)(Entity *);
		void (__thiscall *ParentEntityDestroyed)(Entity *);
		void (__thiscall *ParentEntityKilled)(Entity *);
		void (__thiscall *Materialize)(Entity *, float);
		void (__thiscall *AdjustHealth)(Entity *,float);
		void (__thiscall *Kill)(Entity *, void*, float);
		void (__thiscall *OnDestroy)(Entity *);
		void (__thiscall *UpdateCollision)(Entity *);
		void (__thiscall *CreateInterface)(Entity *);
		void (__thiscall *DestroyInterface)(Entity *);
		void (__thiscall *SyncInterface)(Entity *);
		void (__thiscall *UpdateVisibility)(Entity *);
	};
	vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(CScriptObject::vtable); }

	WORD word4C;
	WORD word4E;
	WORD word50;
	WORD word52;
	struct_subpoi *subpoi;
	BYTE byte58;
	DWORD dword5C;
	DWORD dword60;
	DWORD dword64;
	DWORD entityId;
	REntityBlueprint *blueprint;
	DWORD tickCreated;
	DWORD gap74;
	SSTIEntityVariableData sstiData;
	Sim *sim;
	CArmyImpl *army;
	Quaternionf lastOri;
	Vector3f nextPos;
	DWORD dword16C;
	float lastImpactSomething;
	DWORD v0;
	CColPrimitive *collisionShape;
	DWORD v1;
	DWORD dword180;
	DWORD dword184;
	DWORD dword188;
	int *parent;
	DWORD dword190;
	float dword194;
	float dword198;
	struct_QuatB parentOrientation;
	Vector3f parentOffset;
	BYTE v3a;
	bool destroyQueued;
	bool destroyed;
	BYTE v3d;
	string str0;
	DWORD intelManager;
	DWORD vizToFocusPlayer;
	DWORD vizToAllies;
	DWORD vizToEnemies;
	DWORD visToNeutrals;
	bool interfaceCreated;
	BYTE v7b;
	BYTE v7c;
	BYTE v7d;
	DWORD scroller;
	DWORD worldImpulse;
	DWORD v4;
	string uniqueName;
	DWORD shooters;
	DWORD dword21C;
	DWORD shootersStart;
	DWORD shootersEnd;
	DWORD dword228;
	DWORD dword22C;
	DWORD gap230;
	DWORD gap234;
	DWORD gap238;
	DWORD gap23C;
	DWORD gap240;
	DWORD gap244;
	DWORD gap248;
	DWORD gap24C;
	DWORD gap250;
	DWORD dword26C;
	LuaObject obj1;

	// again, easier to rewrite than to make the assembly call
	// 0x67AFF0 void __usercall Moho::Entity::SetCurrentLayer(Moho::Entity *this@<esi>, Moho::ELayer newLayer@<edx>)
	void SetCurrentLayer(Moho::ELayer newLayer) {
		Moho::ELayer oldLayer = this->sstiData.layer;
		this->sstiData.layer = newLayer;
		if (newLayer != oldLayer) {
			const char *oldName;
			if ((unsigned int)oldLayer > Moho::LAYER_Orbit) {
				oldName = "";
			} else {
				oldName = COORDS_LayerToString(oldLayer);
			}
			const char *newName;
			if ((unsigned int)newLayer > Moho::LAYER_Orbit) {
				newName = "";
			} else {
				newName = COORDS_LayerToString(newLayer);
			}
			this->Callback("OnLayerChange", &newName, &oldName);
		}
	}

	using CScriptObject::Callback; // unshadow `Callback`

	// 0x67F450 void __thiscall Moho::Entity::Callback(Moho::Entity *this, const char *callback, const char **arg1, const char **arg2)
	void __thiscall Callback(const char *callback, const char **arg1, const char **arg2) asm("0x67F450");
};
VALIDATE_SIZE(Entity, 0x270)

struct CAiTarget_Faux
{
	Moho::EAiTargetType targetType;
};
struct CAiTarget : CAiTarget_Faux, intrusive_linked_list<CAiTarget>
{
	Vector3f position;
	DWORD targetPoint;
	BYTE targetIsMobile;
};

struct Projectile : Entity
{//0x004C702B, 0x380 bytes
	using Type = ObjectType<0x10C7578, 0xF77914>;
	DWORD v140;
	DWORD v141;
	DWORD launcher_p1;
	DWORD v143;
	Vector3f velocity;
	Vector3f v147;
	Vector3f scaleVelocity;
	float impactInterp;
	bool collideSurface;
	bool doCollision;
	bool trackTarget;
	bool velocityAlign;
	bool stayUpright;
	bool v155b;
	bool stayUnderwater;
	bool destroyOnWater;
	float turnRateDeg;
	float maxSpeed;
	float acceleration;
	Vector3f ballisticAcc;
	DWORD v162;
	DWORD v163;
	string v164;
	DWORD targetPosData;
	intrusive_linked_list<CAiTarget>* trackingTargets;
	DWORD v173;
	DWORD v174;
	DWORD v175;
	DWORD v176;
	DWORD v177;
	DWORD v178;
	Vector3f v179;
	DWORD v182;
	Vector3f impactPosition;
	intrusive_linked_list<CScriptObject>* impactEntities;
	DWORD lifetimeEnd;
	bool belowWater;
	BYTE v189b;
	BYTE v189c;
	BYTE v189d;
	DWORD bounceLimit;
	DWORD groundTick;
	bool directAwayFromGround;
	BYTE v192b;
	BYTE v192c;
	BYTE v192d;
	Vector3f groundir;
	float BounceVelDamp;
	DWORD v197;
	Vector3f v198;
	Moho::EImpactType impactType;
	RProjectileBlueprint *blueprint;
	float v203;
	float v204;
	float detonateAboveHeight;
	float detonateBelowHeight;
	char v207;

	void __thiscall CheckWorldCollision(Segment3f *movement);
};
VALIDATE_SIZE(Projectile, 0x380)

struct Prop : Entity
{//0x004C702B, 0x288 bytes
	// at 0x6C
	RPropBlueprint *Blueprint;
	DWORD v2;
	bool v3a;
	bool v3b;
	bool v3c;
	bool v3d;
	DWORD priority;
	DWORD boundedTick;
};
struct __declspec(align(4)) CTask
{
  void *vtable;
  DWORD v1;
  DWORD v2;
  CTaskThread *taskThread;
  CTask *subtask;
  bool v5;
};

struct CCommandTask
{	//0x34 bytes
	void* vtable;
	void* unk0; // self+4;
	// at 0x10
	CCommandTask *prevTask; // ?
	// at 0x1C
	Unit *owner;
	Sim *sim;
	// at 0x28
	//CCommandTask *prevTask; -0x2C
};

struct CUnitMobileBuildTask : CCommandTask
{	//0xE8 bytes
	// at 0xC
	Unit *owner;
	Sim *sim;
	Unit *target0; // -4
	CCommandTask *next; // ?
	// at 0x2C
	string name;
	float FractionComplete;
	// at 0x50
	CUnitCommand *unitCommand;
	RUnitBlueprint *build;
	float unk0, unk1, unk2, unk3;
	// at 0x84
	Unit *target1; // -4
};

struct CUnitRepairTask : CCommandTask
{	//0x9C bytes
	// at 0xC
	Unit *owner;
	Sim *sim;
	// at 0x2C
	string name;
	// at 0x50
	CUnitCommand *unitCommand;
	Unit *target; // -4
};

struct CUnitCommand : CScriptEvent
{	// 0x178 bytes
 DWORD v0;
  DWORD v1;
  DWORD v2;
  DWORD index;
  DWORD cmd;
  DWORD v5;
  DWORD v6;
  DWORD v7;
  DWORD v8;
  DWORD v9;
  DWORD v10;
  RUnitBlueprint *blueprint;
  DWORD v12;
  DWORD v13;
  DWORD v14;
  DWORD v15;
  DWORD v16;
  DWORD v17;
  DWORD v18;
  DWORD v19;
  DWORD v20;
  DWORD v21;
  DWORD v22;
  DWORD v23;
  DWORD v24;
  Moho::EUnitCommandType unitCommandType;
  DWORD v26;
  DWORD targetId;
  Vector3f targetPosition;
  DWORD v31;
  DWORD v32;
  DWORD v33;
  DWORD v34;
  DWORD v35;
  DWORD v36;
  DWORD v37;
  DWORD v38;
  DWORD v39;
  DWORD v40;
  DWORD v41;
  DWORD v42;
  DWORD v43;
  DWORD v44;
  DWORD v45;
  DWORD v46;
  std::map<uint, Entity> unitSet;
  DWORD v51;
  DWORD v52;
  DWORD v53;
  DWORD v54;
  DWORD v55;
  DWORD v56;
  DWORD v57;
  DWORD v58;
  DWORD v59;
  DWORD v60;
  DWORD v61;
  DWORD v62;
  DWORD v63;
  DWORD v64;
  DWORD v65;
  DWORD v66;
  bool v67a;
  bool v67b;
  bool v67c;
  bool v67d;
  DWORD v68;
  DWORD v69;
  DWORD v70;
  DWORD v71;
  DWORD v72;
  DWORD v73;
  DWORD v74;
  DWORD v75;
  DWORD v76;
  DWORD v77;
  DWORD v78;
  DWORD v79;
  DWORD v80;
};

struct SCommand
{	// 0x8 bytes
	void *CUnitCommand; // +0x4
	void *nil;
};

struct CommandQueue
{	// 0x28 bytes
	void *unk1;
	void *unk2;
	Unit *Owner;
	vector<SCommand> Commands;
	void *unk3;
	void *unk4;
	bool unk5;
};

struct UnitWeapon_base {
	DWORD vtable;
	DWORD v1;
	DWORD v2;
	DWORD v3;
};

struct CFireWeaponTask : CTask
{
  int v1;
  Unit *unit;
  UnitWeapon *weapon;
  int fireClock;
};


struct CDamageType {
	RUnitBlueprintWeapon *blueprint;
	float firingTolerance;
	float rateOfFire;
	float minRadius;
	float maxRadius;
	float minRadiusSq;
	float maxRadiusSq;
	float maxHeightDiff;
	string type;
	float damageRadius;
	float damage;
	DWORD v38;
	DWORD v39;
};


struct UnitWeapon : UnitWeapon_base, CScriptEvent
{//0x006D3114, 0x188 bytes
	Sim *sim;
	RUnitBlueprintWeapon *weaponBlueprint;
	RProjectileBlueprint *projectileBlueprint;
	CAiAttackerImpl *attacker;
	CDamageType damageType;
	Unit *unit;
	DWORD weaponIndex;
	DWORD v42;
	bool enabled;
	BYTE v43b;
	BYTE v43c;
	BYTE v43d;
	string label;
	CAiTarget target;
	CFireWeaponTask *fireWeaponTask;
	bool v60;
	DWORD v61;
	RRuleGameRulesImpl *rules1;
	DWORD v63;
	DWORD v64;
	DWORD v65;
	DWORD restrictProhibit;
	DWORD v67;
	DWORD v68;
	DWORD v69;
	DWORD v70;
	DWORD v71;
	RRuleGameRulesImpl *rules2;
	DWORD v73;
	DWORD v74;
	DWORD v75;
	fastvector<unk_t> restrictOnlyAllow;
	DWORD v80;
	DWORD v81;
	DWORD fireTargetLayerCaps;
	float firingRandomness;
	DWORD targetPriorities;
	DWORD targetPriorityStart;
	DWORD targetPriorityEnd;
	DWORD v87;
	DWORD v88;
	DWORD v89;
	DWORD v90;
	DWORD v91;
	DWORD v92;
	DWORD v93;
	Vector3f v94;
	DWORD shotsAtTarget;
};

struct IAiAttacker : VirtualClass {
	using vtable_t = struct vtable_attacker : vtable_ {
		void (__thiscall *dtr)(CAiAttackerImpl*, int);
		void* field_4;
		Unit* (__thiscall *GetUnit)(CAiAttackerImpl*);
		int (__thiscall *AttackerWeaponsBusy)(CAiAttackerImpl*);
		int (__thiscall *field_10)(CAiAttackerImpl*);
		void (__thiscall *field_14)(CAiAttackerImpl*, int);
		int (__thiscall *GetWeaponCount)(DWORD*);
		UnitWeapon* (__thiscall *GetWeapon)(CAiAttackerImpl*, int);
		void (__thiscall *SetDesiredTarget)(CAiAttackerImpl*, CAiTarget*);
		CAiTarget* (__thiscall *GetDesiredTarget)(CAiAttackerImpl*);
		void *field_28;
		int (__thiscall *CanAttackTarget)(CAiAttackerImpl*, CAiTarget*);
		bool (__thiscall *CanAttackTarget)(CAiAttackerImpl*, Entity*);
		void *FindBestEnemy;
		UnitWeapon* (__thiscall *GetTargetWeapon)(CAiAttackerImpl*, CAiTarget*);
		UnitWeapon* (__thiscall *GetPrimaryWeapon)(CAiAttackerImpl*);
		double (__thiscall *GetMaxWeaponRange)(CAiAttackerImpl*);
		int (__thiscall *VectorIsWithinWeaponAttackRange)(CAiAttackerImpl*, UnitWeapon*, Vector3f*);
		int (__thiscall *VectorIsWithinAttackRange)(CAiAttackerImpl*, Vector3f*);
		int (__thiscall *TargetIsWithinWeaponAttackRange)(CAiAttackerImpl*, UnitWeapon*, CAiTarget*);
		int (__thiscall *TargetIsWithinAttackRange)(CAiAttackerImpl*, CAiTarget*);
		int (__thiscall *IsTooClose)(CAiAttackerImpl*, CAiTarget*);
		int (__thiscall *IsTargetExempt)(CAiAttackerImpl*, Entity*);
		CAiTarget *(__thiscall *HasSlavedTarget)(CAiAttackerImpl*, int*);
		void (__thiscall *ResetReportingState)(CAiAttackerImpl*);
		void (__thiscall *field_64)(CAiAttackerImpl*, UnitWeapon*, Projectile*);
		void* field_68;
		void (__thiscall *ForceEngage)(CAiAttackerImpl*, Entity*);
		LuaStackObject *(__thiscall *PushStack)(CAiAttackerImpl*, LuaState*);
	};
	vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(vtable); }
	DWORD v0;
	DWORD v1;
};

struct CAiAttackerImpl : IAiAttacker, CScriptObject
{//0x005D6ABF, 0xA4 bytes
	Unit *unit;
  DWORD v16;
  DWORD v17;
  DWORD v18;
  DWORD v19;
  DWORD v20;
	vector<UnitWeapon*> Weapons;
  fastvector<unk_t> v25;
  DWORD v24;
  DWORD v29;
  DWORD v30;
  CAiTarget desiredTarget;
  DWORD reportingState;
};

struct UserUnitWeapon
{	// 0x98 bytes
	// at 0x54
	float MinRadius;
	float MaxRadius;
};

struct UnitIntel
{	// 0x20 bytes, AND 7FFFFFFF
	int VisionRadius;
	int WaterVisionRadius;
	int RadarRadius;
	int SonarRadius;
	int OmniRadius;
	int RadarStealthFieldRadius;
	int SonarStealthFieldRadius;
	int CloakFieldRadius;
};

struct IUnit_chain {
  IUnit_chain** iunitchain;
};

struct UnitAttributes
{
  RUnitBlueprint *blueprint;
  DWORD v1;
  EntityCategory restrictionCategory;
  float elevation;
  float speedMult;
  float accMult;
  float turnMult;
  float breakOffTriggerMult;
  float breakOffDistMult;
  float consumptionPerSecondEnergy;
  float consumptionPerSecondMass;
  float productionPerSecondEnergy;
  float productionPerSecondMass;
  float buildRate;
  float regenRate;
  Moho::ERuleBPUnitCommandCaps commandCaps;
  Moho::ERuleBPUnitToggleCaps toggleCaps;
  BYTE reclaimable;
  BYTE capturable;
  BYTE gap20A[6];
};


struct IUnit : VirtualClass, IUnit_chain
{
	using vtable_t = struct vtable_iunit : vtable_ {
		void (__thiscall *IsUnit1)(Unit*);
		Unit* (__thiscall *IsUnit2)(Unit*);
		void (__thiscall *IsUserUnit1)(Unit*);
		void (__thiscall *IsUserUnit2)(Unit*);
		DWORD (__thiscall *GetEntityId)(Unit*);
		Vector3f* (__thiscall *GetPosition)(Unit*);
		VTransform* (__thiscall *GetTransform)(Unit*);
		RUnitBlueprint* (__thiscall *GetBlueprint)(IUnit *);
		LuaObject* (__thiscall *GetLuaObject)(Unit*, LuaObject*);
		int (__thiscall *CalcTransportLoadFactor)(Unit*);
		bool (__thiscall *IsDead)(IUnit*);
		bool (__thiscall *DestroyQueued)(IUnit*);
		bool (__thiscall *IsMobile)(IUnit*);
		bool (__thiscall *IsBeingBuilt)(Unit*);
		int (__thiscall *IsNavigatorIdle)(Unit*);
		unsigned __int8 (__thiscall *IsUnitState)(Unit*, Moho::EUnitState);
		UnitAttributes* (__thiscall *GetAttributes1)(IUnit*);
		UnitIntel* (__thiscall *GetAttributes2)(Unit*);
		StatItem* (__thiscall *GetStatDefaultStr)(Unit*, const char*, string*);
		StatItem* (__thiscall *GetStatDefaultNum)(Unit*, const char*, float*);
		StatItem* (__thiscall *GetStatDefaultInt)(Unit*, const char*, int*);
		StatItem* (__thiscall *GetStat)(Unit*, const char*);
		void (__thiscall *SetAutoMode)(Unit*, BOOL);
		void (__thiscall *SetAutoSurfaceMode)(Unit*);
		void (__thiscall *IsAutoMode)(Unit*);
		int (__thiscall *IsAutoSurfaceMode)(Unit*);
		void (__thiscall *SetCustomName)(Unit*, string);
		string *(__thiscall *GetCustomName)(Unit*, string*);
	};
	vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(vtable); }
};


struct Unit : WeakObject
{//0x006A5422, 0x6A8 bytes
	//WeakObject WeakObject;
	// at 0x8
	//Entity Entity; to 0x278
	// at 0x50
	void* self1;
	// at 0x70
	uint32_t UnitID;
	RUnitBlueprint *Blueprint;
	uint32_t CreationIndex; // ?
	void *unk1;
	void *unk2;
	void *RScmResource;
	void *RMeshBlueprint;
	Vector3f Scale; // at 0x8C
	float CurHealth;
	float MaxHealth;
	bool unk3;
	bool unk4;
	bool unk5;
	char pad1;
	Vector4f Rot1; // at 0xA4
	Vector3f Pos1;
	Vector4f Rot2;
	Vector4f Pos2;
	float FractionComplete; // at 0xE0
	void *unk6;
	char unk7[0x18];
	void *unk10;
	void *unk12;
	void *unk13;
	void *unk14;
	void *unk15;
	void *unk16;
	bool VisibleAndControl; // at 0x118
	char pad2[3];
	void *unk18;
	void *unk19;
	bool unk20;
	char pad3[3];
	void *unk21;
	UnitIntel UnitIntel; // at 0x130
	Sim *sim; // at 0x150
	SimArmy *owner;
	Vector4f Rot3;
	Vector3f Pos3;
	// at 0x17C
	int TickCount1; // Readonly
	void* CColPrimitiveBase;
	// at 0x248
	Vector3f Pos4;
	Vector3f Pos5;
	// at 0x294
	float FuelRatio;
	float ShieldRatio; // Readonly
	// at 0x2A0
	bool Paused;
	// at 0x2AC
	float WorkProgress;
	// at 0x2CC
	string customUnitName;
	// at 0x380
	UserUnitWeapon* Weapons;
	list<unk_t> unk22; // Weapons?
	void *unk23; // Weapons?
	// at 0x4B0
	void *MotionEngine; // +0xC FuelUseTime
	void *CommandQueue;
	int Enum; //0..4
	// at 0x534
	void *workValues; // +0x8
	bool Flag;
	// at 0x53C
	float WorkRate;
	// at 0x544
	void* IAiAttacker;
	void* IAiCommandDispatch;
	// at 0x558
	void* IAiSiloBuild;
	void* IAiTransport;
	// at 0x59C
	Vector3f Pos6;
	// at 0x668
	int tickCount2; // Readonly
	// at 0x68E
	bool updWeaponRadius;
};

struct UserEntity : WeakObject
{	// 0x148 bytes
	// at 0x44
	int entityID;
	RPropBlueprint *blueprint;
	// at 0x58
	RMeshBlueprint *mesh;
	// at 0x68
	float curHealth;
	float maxHealth;
	// at 0x70
	bool isBeingBuilt;
	Vector4f rot1;
	Vector3f pos1;
	// at 0x90
	Vector4f rot2;
	Vector4f pos2;
	// at 0xB0
	float fractionComplete;
	// at 0xD0
	//float x1,y1,x2,y2;
	// at 0x100
	UnitIntel unitIntel;
	UserArmy *owner; // at 0x120
	Vector4f rot3;
	Vector4f pos3;
};

struct UserUnit : UserEntity
{//0x008B8601, 0x3E8 bytes
	using Type = ObjectType<0x10C77AC, 0xF881E0>;
	// at 0x44
	uint32_t UnitID;
	RUnitBlueprint *blueprint;
	// at 0x1B0
	bool Paused;
	// at 0x1BC
	float WorkProgress;
	// at 0x1DC
	string customUnitName;
	// at 0x290
	UserUnitWeapon *weapons;
};

struct CPlatoon : public CScriptObject
{
	using Type = ObjectType<0x10C6FCC, 0xF6A1FC>;
};

struct CMauiBitmap : public CMauiControl
{
	using Type = ObjectType<0x10C7704, 0xF832F4>;
};

struct ReconBlip : Entity
{	// 0x4D0 bytes
	Entity entity;
	// at 0x270
	void *originUnit; // -0x4
	// at 0x28C
	void *StatItem;
	void *StatItem2;
	// at 0x320
	void *CAniPose;
	// at 0x328
	void *CAniPose2;
	// at 0x330, size 0x30?
	list<unk_t> unk1;
	void *unk2;
	// at 0x360, size 0x30?
	list<unk_t> unk3;
	void *unk4;
	// at 0x390, size 0x30?
	list<unk_t> unk5; // Weapons?
	void *unk6; // Weapons?
	// at 0x450, size 0x30?
	list<unk_t> unk7;
	void *unk8;
	// at 0x4C4
	void *armyesData[]; //size 0x34
};


struct MD5Digest
{
	int v0;
	int v1;
	int v2;
	int v3;
};

struct MD5Context
{
	MD5Digest dynamicHashes;
	MD5Digest trashHashes[5];
};

struct CMersenneTwister
{
	unsigned int state[624];
	int k;
	DWORD gap1;
	DWORD gap2;
};
VALIDATE_SIZE(CMersenneTwister, 0x9CC)

struct BitArray2D
{
	int* ptr;
	int size;
	int width;
	int height;
};
VALIDATE_SIZE(BitArray2D, 0x10)

// unknown, but a point of interest that frequently pops up
struct struct_poi
{
	Sim *sim;
	struct_subpoi sub;
	BitArray2D arr1;
	BitArray2D arr2;
	BitArray2D arr3;
};
VALIDATE_SIZE(struct_poi, 0x68)


struct IEffect : CScriptObject
{
	DWORD v1;
	DWORD v2;
	DWORD v3;
	DWORD v4;
};


struct CEffectImpl : IEffect
{
	DWORD v0;
	DWORD v1;
	DWORD v2;
	DWORD v3;
	DWORD v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
	DWORD v8;
	DWORD v9;
	DWORD v10;
	DWORD v11;
	DWORD v12;
	DWORD v13;
	DWORD v14;
	DWORD v15;
	DWORD v16;
	DWORD v17;
	DWORD v18;
	DWORD v19;
	DWORD v20;
	DWORD v21;
	DWORD v22;
	DWORD v23;
	DWORD v24;
	DWORD v25;
	DWORD v26;
	DWORD v27;
	DWORD v28;
	DWORD v29;
	DWORD v30;
	DWORD v31;
	DWORD v32;
	DWORD v33;
	DWORD v34;
	DWORD v35;
	DWORD v36;
	DWORD v37;
	DWORD v38;
	DWORD v39;
	DWORD v40;
	DWORD v41;
	DWORD v42;
	DWORD v43;
	DWORD v44;
	DWORD v45;
	DWORD v46;
	DWORD v47;
	DWORD v48;
	DWORD v49;
	DWORD v50;
	DWORD v51;
	DWORD v52;
	DWORD v53;
	DWORD v54;
	DWORD v55;
	DWORD v56;
	DWORD v57;
	DWORD v58;
	float v59;
	DWORD v60;
	DWORD v61;
	DWORD v62;
	DWORD v63;
	DWORD v64;
	DWORD v65;
	DWORD v66;
	VMatrix4 matrix;
};


struct CEfxEmitter : CEffectImpl
{
	DWORD gap[346];
};
VALIDATE_SIZE(CEfxEmitter, 0x6F8)


struct CEffectManagerImpl : VirtualClass
{
	using vtable_t = struct vtable_ceffectmanagerimpl : vtable_ {
		void *dtr;
		Sim *(__thiscall *GetSim)(CEffectManagerImpl *);
		int (__thiscall *CreateEmitter)(CEffectManagerImpl *, char, int, int, const char *, int);
		CEfxEmitter *(__thiscall *CreateAttachedEmitter)(CEffectManagerImpl *, Entity *arg0, int arg4, const char *a4, int a3);
		CEfxEmitter *(__thiscall *CreateEmitterAtBone)(CEffectManagerImpl *, Entity *arg0, int arg4, const char *a4, int a3);
		CEfxEmitter *(__thiscall *CreateEmitterAtEntity)(CEffectManagerImpl *, Entity *arg0, const char *arg4, int a3);
		CEfxEmitter *(__thiscall *CreateEmitterOnEntity)(CEffectManagerImpl *, Vector3f *arg0, const char *arg4, int);
		void *CreateBeam1;
		void *CreateBeam2;
		void *CreateBeamEntityToEntity1;
		void *CreateBeamEntityToEntity2;
		int (__thiscall *CreateTrail)(CEffectManagerImpl *, Entity *, LuaState *, const char *, LuaObject *);
		int *(__thiscall *CreateLightParticle)(CEffectManagerImpl *, int a2, int a3, int a4, string *a5, string *a6, int a7, int a8, int a9);
		void *Tick;
		void *DestroyEffect;
		void *PurgeDestroyedEffects;
	};
	vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(vtable); }

	Sim *sim;
	int v2;
	int v3;
	int v4;
	int v5;
};
VALIDATE_SIZE(CEffectManagerImpl, 0x18)

struct ISoundManager
{
};


struct CSimSoundManager : ISoundManager
{
	void *vtable;
	DWORD gap[455];
};
VALIDATE_SIZE(CSimSoundManager, 0x720)

struct CDebugCanvas
{
	DWORD v0;
	DWORD v1;
	DWORD v2;
	DWORD v3;
	DWORD v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
	DWORD v8;
	DWORD v9;
	DWORD v10;
	DWORD v11;
	DWORD v12;
	DWORD v13;
	DWORD v14;
	DWORD v15;
};


struct OccupationData
{
	DWORD v1;
	DWORD v2;
	DWORD v3;
	DWORD v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
	DWORD v8;
	DWORD v9;
	DWORD v10;
};

struct SubclusterData
{
	DWORD v1;
	DWORD v2;
	DWORD v3;
	DWORD v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
	DWORD v8;
	DWORD v9;
	DWORD v10;
};


template<class T>
struct ClusterInternalCache 
{
	DWORD vtable;
	T vec;
};


struct ClusterCache
{
	ClusterInternalCache<OccupationData> occupationData;
	ClusterInternalCache<SubclusterData> subclusterData;
};

struct Cluster
{
	void *data;
};

struct struct_12
{
	Cluster **vec;
	DWORD width;
	DWORD height;
};


struct ClusterMap
{
	DWORD numlevels;
	DWORD width;
	DWORD height;
	DWORD v3;
	weak_ptr<ClusterCache> v4;
	struct_12 v6[4];
	BitArray2D v18[4];
	DWORD v34;
	DWORD v35;
	Rect2i v36;
};


struct struct_PathTable
{
	DWORD width;
	DWORD height;
	DWORD v3;
	char **v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
	ClusterMap **clusterMap;
	DWORD v9;
	DWORD v10;
	weak_ptr<ClusterCache> clusterCache;
};

struct struct_PathTables
{
	struct_PathTable* tbl;
};

struct CAiFormationDBImpl
{
	void *vtable;
	Sim *sim;
	int v2;
	int v3;
	int end;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v10;
	int v11;
	int v12;
	int v13;
	int v14;
	int v15;
};
VALIDATE_SIZE(CAiFormationDBImpl, 0x40)

struct EntityDB
{
	void *vtable;
	DWORD v2;
	DWORD v3;
	DWORD v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
	DWORD v8;
	DWORD v9;
	DWORD v10;
	DWORD v11;
	DWORD v12;
	DWORD v13;
	DWORD v14;
	DWORD v15;
	DWORD v16;
	DWORD v17;
	DWORD v18;
	DWORD v19;
	DWORD v20;
};
VALIDATE_SIZE(EntityDB, 0x50)


// unknown sub resource 2 in Sim sub resource 1
struct struct_sim_subres2
{
	vector<unk_t> v1;
	vector<unk_t> v2;
};

// unknown sub resource 1 in Sim sub resource
struct struct_sim_subres1
{
	struct_sim_subres2 data[100];
	DWORD v1;
	DWORD index;
};

// unknown sub resource in Sim resource 1 and 2
struct struct_sim_subres
{
	DWORD v24;
	DWORD v25;
	DWORD v26;
	DWORD v27;
	DWORD *v28;
	DWORD *v29;
	DWORD *v30;
	DWORD *v31;
	DWORD v32;
	DWORD v33;
	struct_sim_subres1 subres2;
};

// unknown resource 2 in Sim
struct struct_sim_res2
{
	void *sim;
	DWORD v0;
	DWORD vec;
	DWORD v2;
	struct_sim_subres subres;
	DWORD v4;
	DWORD v3;
	DWORD v5;
	DWORD v6;
};
VALIDATE_SIZE(struct_sim_res2, 0xCD0)


// unknown resource 1 in Sim
struct struct_sim_res1
{
	Sim *sim;
	DWORD v23;
	struct_sim_subres subres1;
	DWORD v836;
	DWORD index;
	DWORD v838;
	vector<unk_t> *vec22;
	DWORD v840;
	DWORD v841;
	DWORD *v842;
	DWORD v843;
	DWORD v844;
	DWORD v845;
	DWORD *v846;
	DWORD v847;
	DWORD v848;
	DWORD v849;
};



struct Sim : VirtualClass // : ICommandSink
{	// 0xAF8 bytes
	using vtable_t = struct vtable_sim : vtable_ {
		void (__thiscall *SetCommandSource)(Sim *);
		void (__thiscall *CommandSourceTerminated)(Sim *);
		void (__thiscall *VerifyChecksum)(Sim *);
		void (__thiscall *RequestPause)(Sim *);
		void (__thiscall *Resume)(Sim *);
		void (__thiscall *SingleStep)(Sim *);
		void (__thiscall *CreateUnit)(Sim *);
		void (__thiscall *CreateProp)(Sim *);
		void (__thiscall *DestroyEntity)(Sim *);
		void (__thiscall *WarpEntity)(Sim *);
		void (__thiscall *ProcessInfoPair)(Sim *);
		void (__thiscall *IssueCommand)(Sim *);
		void (__thiscall *IssueFactoryCommand)(Sim *);
		void (__thiscall *IncreaseCommandCount)(Sim *);
		void (__thiscall *DecreaseCommandCount)(Sim *);
		void (__thiscall *SetCommandTarget)(Sim *);
		void (__thiscall *SetCommandType)(Sim *);
		void (__thiscall *SetCommandCells)(Sim *);
		void (__thiscall *RemoveCommandFromUnitQueue)(Sim *);
		void (__thiscall *ExecuteLuaInSim)(Sim *);
		void (__thiscall *LuaSimCallback)(Sim *);
		void (__thiscall *ExecuteDebugCommand)(Sim *);
		void (__thiscall *AdvanceBeat)(Sim *);
		void (__thiscall *EndGame)(Sim *);
	};
	vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(vtable); }

	string str0;
	FILE *log;
	string str1;
	DWORD *gap40;
	linked_list<string> *linkedlist1;
	DWORD *gap48;
	DWORD *gap4C;
	MD5Context hashContext;
	MD5Digest simHashes[128];
	DWORD v4;
	DWORD v5;
	DWORD v6;
	DWORD v7;
	CEffectManagerImpl *effectManager;
	CSimSoundManager *soundManager;
	RRuleGameRules *rules;
	STIMap *mapData;
	weak_ptr<CSimResources> simResources;
	LuaState *luaState;
	bool gameEnded;
	bool gameOverMaybe;
	int pausedBy;
	bool singleStep;
	BYTE byte8E5;
	bool cheatsEnabled;
	BYTE byte8E7;
	DWORD *gap8E8;
	DWORD *gap8EC;
	DWORD *gap8F0;
	DWORD *gap8F4;
	DWORD cur_beat;
	BYTE byte8FC;
	DWORD cur_tick;
	CMersenneTwister *mersenneTwister;
	struct_poi *poi1;
	vector<CArmyImpl*> armies;
	DWORD *gap91C;
	list<SSTICommandSource> commandSources;
	unsigned int currentCommandSource;
	DWORD dword930;
	DWORD *gap934;
	DWORD *gap938;
	DWORD *gap93C;
	BYTE gap940[4];
	CTaskThread *taskThread;
	DWORD *gap948;
	DWORD *gap94C;
	DWORD *gap950;
	DWORD *gap954;
	DWORD dword958;
	DWORD *gap95C;
	DWORD *gap960;
	DWORD *gap964;
	BYTE gap968;
	weak_ptr<CDebugCanvas> debugCanvas;
	DWORD dword974;
	volatile signed __int32 *pvolatile_signed___int32978;
	struct_PathTables *pathTables;
	CAiFormationDBImpl *formationDB;
	EntityDB *entityDB;
	struct_sim_res2 *resource2;
	DWORD *gap98C;
	DWORD *gap990;
	DWORD *gap994;
	DWORD *gap998;
	struct_sim_res1 *resource1;
	DWORD *gap9A0;
	DWORD dword9A4;
	BYTE gap9A8[4];
	DWORD dword9AC;
	DWORD dword9B0;
	DWORD *gap9B4;
	DWORD *gap9B8;
	DWORD *gap9BC;
	DWORD *gap9C0;
	DWORD *gap9C4;
	DWORD *gap9C8;
	DWORD *gap9CC;
	DWORD *gap9D0;
	DWORD *gap9D4;
	DWORD *gap9D8;
	DWORD *gap9DC;
	DWORD *gap9E0;
	DWORD *gap9E4;
	DWORD *gap9E8;
	DWORD *gap9EC;
	DWORD *gap9F0;
	DWORD *gap9F4;
	DWORD *gap9F8;
	DWORD *gap9FC;
	DWORD *gapA00;
	DWORD *gapA04;
	DWORD *gapA08;
	DWORD *gapA0C;
	DWORD *gapA10;
	DWORD *gapA14;
	DWORD *gapA18;
	DWORD *gapA1C;
	DWORD *gapA20;
	DWORD *gapA24;
	BYTE gapA28[4];
	DWORD dwordA2C;
	DWORD dwordA30;
	DWORD dwordA34;
	Vector3f *gravity;
	DWORD *gapA3C;
	DWORD *gapA40;
	DWORD *gapA44;
	BYTE gapA48[4];
	DWORD dwordA4C;
	DWORD dwordA50;
	DWORD dwordA54;
	DWORD dwordA58;
	DWORD dwordA5C;
	DWORD dwordA60;
	bool requestXMLArmyStatsSubmit;
	int syncArmy;
	BYTE gapA6C;
	DWORD *gapA70;
	DWORD *gapA74;
	DWORD *gapA78;
	DWORD *gapA7C;
	DWORD *gapA80;
	DWORD *gapA84;
	int focusArmyIndex;
	DWORD *gapA8C;
	DWORD *gapA90;
	DWORD *gapA94;
	DWORD *gapA98;
	BYTE gapA9C[12];
	DWORD dwordAA8;
	DWORD dwordAAC;
	DWORD dwordAB0;
	DWORD dwordAB4;
	DWORD v9;
	DWORD v10;
	DWORD v11;
	DWORD v12;
	BYTE v13;
	BYTE v13a;
	BYTE v13b;
	BYTE v14c;
	DWORD v14;
	DWORD v15;
	DWORD v16;
	DWORD v17;
	DWORD v18;
	DWORD v19;
	DWORD v20;
	DWORD v21;
	DWORD v22;
	DWORD v23;
	DWORD v24;
};
VALIDATE_SIZE(Sim, 0xAF8)

struct CWldSession
{//0x0089318A, 0x508 bytes
	CWldSession *self1;
	CWldSession *self2;
	void *self_weird1; // this + 0x8
	void *self_weird2; // this + 0x8
	// at 0x10
	LuaState *LState; // Set from constructor argument
	void *unk1; // 0x14 bytes
	RRuleGameRules *rules;
	CWldMap *map;
	LaunchInfoNew *launchInfo;
	void *unk2; //class detail::boost::sp_counted_impl_p<struct Moho::LaunchInfoNew>
	string mapName;
	Entities entities;
	uint8_t pad1[0x3A8];
	// at 0x3F0
	list<UserArmy*> armies;
	// at 0x3FC
	void *unk3; // 0xCC0 bytes
	void *unk4; // 0x64 bytes
	uint8_t pad2[0x20];
	// at 0x424
	CSimResources *deposits;
	uint8_t pad3[0x48];
	// at 0x470
	vector<SSTICommandSource> cmdSources;
	// at 0x480
	int ourCmdSource;
	bool isReplay;
	bool isBeingRecorded;
	bool isMultiplayer;
	bool allowObservers;

	int focusArmyIndex; // focused army, -1 = observer

	BOOL isGameOver;
	uint8_t pad4[0x10];
	// at 0x4A0
	struct {
		int unk1;
		void **SelList; //+0x10
		int SelCount;
		int SelCount2;
	} selectedUnits;
	// at 0x4B0
	struct
	{	// size 0x24
		void *unk1;
		float mouseWorldPosX;
		float mouseWorldPosY;
		float mouseWorldPosZ;
		void *unk2;
		void *unk3;
		int IsDragger;
		float mouseScreenPosX;
		float mouseScreenPosY;
	} mouse;
	// at 0x4D4
	bool cheatsEnabled; // Copied from LaunchInfoNew + 0x88
	uint8_t pad5[0x13];
	// at 0x4E8
	bool displayEconomyOverlay;
	bool relationsArmyColors;
	uint8_t pad6[0x1C];
};
VALIDATE_SIZE(CWldSession, 0x508)

struct CSimDriver // : ISTIDriver
{//0x0073B59E, 0x230 bytes
	void *vtable;
	Sim *sim;
	IClientManager *ClientManager;
	uint8_t pad1[4];
	// at 0x10
	void *LaunchInfoNew; // From g_SWldSessionInfo, only when loading game init
	uint8_t pad2[8];
	// at 0x1C
	uint32_t beatCounter1;
	uint32_t beatCounter2; // Copied to address 0x1290710
	uint32_t beatCounter3;
	uint8_t pad3[0x86];
	// at 0xB0
	int focusArmyIndex;
	uint8_t pad4[0x6C];
	// at 0x120
	int focusArmyIndex2; // Copy from 0xB0
	uint8_t _pad5[0x104];
	// at 0x228
	int maxSimRate; // from CalcMaxSimRate
	uint8_t pad6[4];
};
VALIDATE_SIZE(CSimDriver, 0x230);

template<class T>
struct struct_iGrid_data
{
	T *data;
	int width;
	int height;
};

struct struct_iGrid
{
	struct_iGrid_data<__int32> data1;
	struct_iGrid_data<__int16> data2;
};

struct CHeightField : struct_iGrid_data<__int16>
{//0x00579121
	BYTE gap1[4];
	struct_iGrid *subgrid_start;
	struct_iGrid *subgrid_end;
	float a;

	// 0x476F30 Wm3::Vector3f *__userpurge Moho::CHeightField::Intersection@<eax>(Moho::CHeightField *this@<eax>, Wm3::Vector3f *dest@<ebx>, Moho::GeomLine3 *line@<esi>, Moho::CGeomHitResult *result)
	Vector3f* Intersection(GeomLine3 *line, Vector3f *dest, CGeomHitResult *result) {
		Vector3f* out;
		asm(R"(
			push %[pResult]
			call 0x476F30
		)"
			: [tied]"=a"(out)
			: "[tied]"(this), "S"(line), "b"(dest), [pResult]"rm"(result)
			:
		);
		return out;
	}
};
VALIDATE_SIZE(CHeightField, 0x1C)

struct TerrainTypes
{
	LuaObject v1;
	BYTE gap14[5100];
	DWORD v5;
	DWORD v6;
	DWORD v7;
	DWORD v8;
};


struct STIMap
{
	weak_ptr<CHeightField> heightField;
	DWORD playableRectX;
	DWORD playableRectY;
	DWORD playableRectW;
	DWORD playableRectH;
	TerrainTypes terrainTypes;
	struct_iGrid_data<__int8> terrainType;
	DWORD gap1434[64];
	bool hasWater;
	BYTE gap1534b;
	BYTE gap1534c;
	BYTE gap1534d;
	float waterLevel;
	float depthLevel;
	float abyssLevel;
	DWORD v1;
};
VALIDATE_SIZE(STIMap, 0x1548);

struct CPushTask
{
	char data[0x24];
};

typedef CPushTask CPullTask;

struct INetConnector
{
	void* vtable;
};
struct CLobby
{//0x004C702B, 0xC8 bytes
	// at 0x20
	LuaObject unk1;

	int unk2;
	int unk3;
	int unk4;
	int unk5;
	// at 0x44
	CPushTask pushTask;

	// at 0x60
	CPullTask pullTask;

	// at 0x84
	bool hosted_or_joined; // Has CLobby been used to host/join yet?

	// at 0x88
	void* not_host; // 0 if we're host

	// at 0x90
	string our_name;
	// at 0xAC
	int our_UID;

	// at 0xB0
	struct
	{
		INetConnector* first_element;
		INetConnector* last_element; // It will probably always be our CNetXXXConnector
	} peer_list; // Probably singly-linked list
};

struct sub_10392B10_ret
{	// 0x20 bytes

	void* zero1;
	void* zero2;
	void* zero3;
	int unk1;

	// at 0x10
	bool one1;
	bool zero4;
};

struct CLobbyPeer
{	// 0x50 bytes

	CLobbyPeer* next; // Doubly linked list pointers
	CLobbyPeer* prev;

	string playerName;

	// at 0x24
	int ownerID;	// User UID
	int const1;
	short const2;
	char pad1[2];

	// at 0x30
	int const3;	// enum?
	float const4;	// = 0
	int const5;
	int unk1;

	// at 0x40
	sub_10392B10_ret* unk2; // made in sub_10394180
	int zero1;
	int cmdSourceIndex; // == 255 => Unassigned
	int playerNo;

	/*
		const1, const2, const3, const5
		specially define the CLobbyUser

		const3:
		1 - Host for a lobby we joined?
		3 - Peer who connected to us?
		6 - Game Peer of a Launched Game?
	*/
};

struct CClientManagerImpl : IClientManager
{	// 0x184D0 bytes
	// at 0x40C
	gpg_mutex mLock;

	// at 0x420
	list<IClient*> mClients;
	INetConnector* mConnector;

	// at 0x434
	bool mWeAreReady;
	bool mEveryoneIsReady;
	char pad1[2];
	int mDispatchedBeat;
	int mAvailableBeat;
	int mFullyQueuedBeat;
	int mPartiallyQueuedBeat;
	int gameSpeedChangeCounter; // mGameSpeedClock
	int mGameSpeedRequester;    // Always 0
	int gameSpeedRequested;     // mGameSpeed
	bool speedControlEnabled;
	// at 0x458
	uint32_t hEvent; // for KERNEL32.SetEvent
	// at 0x18470
	PipeStream mPipe;
	// at 0x184BC
	bool unk1; // if value is 1 then KERNEL32.SetEvent is bypassed
};

typedef struct mRequest {IClient* mRequester; int mAfterBeat;};

struct CClientBase : IClient
{//0x0053B5E9, 0xD8 bytes
	string mNickname;
	// at 0x20
	int mIndex; // client index
	int mUID;
	IClientManager* clientManager;

	// at 0x30
	moho_set unk1;
	// at 0x50
	int mCommandSource;
	bool mReady;
	char pad1[3];
	PipeStream mPipe;

	// at 0xA0
	int mQueuedBeat;
	int mDispatchedBeat;
	int mAvailableBeatRemote;
	vector<int> mLatestAckReceived;
	int mLatestBeatDispatchedRemote;
	// at 0xC0
	bool mEjectPending;
	bool mEjected;
	char pad2[2];
	vector<mRequest> mEjectRequests;
	int maxSimRate; // from CalcMaxSimRate
};

struct CLocalClient : CClientBase
{//0x0053B5E9, 0xD8 bytes
};	// equal CClientBase

struct CReplayClient : CClientBase
{	// 0x160 bytes
	// before 0xD8 it CClientBase
	// at 0xD8
	FileStream* stream;
	// at 0xE0
	void* ptr1; // self+0xF0
	void* ptr2; // self+0xF0
	void* ptr3; // self+0x130
	void* ptr4; // self+0xF0
	void* unk1;
	// at 0x130
	void* unk2;
	// at 0x138
	uint32_t replayBeat;
	bool unk3;
	void* unk4;
	uint32_t hSemaphore1;
	uint32_t hSemaphore2;
	uint32_t hMutex;
	// at 0x15C
	bool unk5;
	bool unk6;
};

struct CNetUDPConnection {};

struct CNetUDPConnetor // : INetConnector
{	// 0x18090 bytes
	void* vtable;
	void* smth; // Listen socket fd?
	gpg_mutex mMutex;
	// at 0x14
	SOCKET mSocket;
	// at 0x24
	linked_list<CNetUDPConnection*> mConnections;
};
/*Game Types
  Multiplayer - CLobby::LaunchGame
  Replay - VCR_SetupReplaySession
  SinglePlayer - WLD_SetupSessionInfo
  Saved Game - CSavedGame::CreateSinglePlayerSession

  Session State
	0 - None?
	1 - Loading?
	2 - Started?
	3 - SIM Initialized
	4 - SIM Started
	5 - Game Started
	7 - Restart Requested
	8 - Session Halted
*/

struct MapImager
{	// 0x14 bytes
	void* vtable;
};

struct MeshThumbnailRenderer
{	// 0x3C bytes
	void* vtable;
};

struct RangeRenderer
{	// 0x94 bytes
	void* vtable;
};

struct VisionRenderer
{	// 0x78 bytes
	void* vtable;
};

struct BoundaryRenderer
{	// 0x68 bytes
	void* vtable;
};

struct Shadow
{	// 0x318 bytes
	void* vtable;
};

struct Clutter
{	// 0x192C bytes
	void* vtable;
};

struct Silhouette
{	// 0x74? bytes
	void* vtable;
	// at 0xC
	CUIWorldView *worldView;
};

struct WRenViewport // : WD3DViewport
{//0x0097977D, 0x21A8 bytes
	void* vtable;
	// at 0x32C
	MapImager mapImager;
	// at 0x340
	MeshThumbnailRenderer meshThumbnailRenderer;
	// at 0x37C
	RangeRenderer rangeRenderer;
	// at 0x410
	VisionRenderer visionRenderer;
	// at 0x488
	BoundaryRenderer boundaryRenderer;
	// at 0x4F0
	Shadow shadow;
	// at 0x808
	Clutter clutter;
	// at 0x2134
	Silhouette silhouette;
};








struct struct_CollisionEntry
{
	Entity *entity;
	DWORD v1;
	DWORD v2;
	DWORD v3;
	Vector3f pos;
	float dist;
};

struct CColHitResult : CGeomHitResult
{
	int unk1;
	int unk2;
};
