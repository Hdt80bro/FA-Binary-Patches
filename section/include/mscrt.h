#pragma once


#include <cstdint>

#define GPtr(addr, type) \
    (*(type*)addr)

#define GDecl(name, addr, type) \
    extern type name asm(#addr);

#define CDecl(name, addr, type) \
    constexpr type name asm(#addr)

#define WDecl(addr, type) \
    ((type)*(uintptr_t*)addr)

#define VALIDATE_SIZE(struc, size) \
    static_assert(sizeof(struc) == size, "Invalid structure size of " #struc);


using BYTE = char;
using WORD = short;
using DWORD = int;
using QWORD = long long;
VALIDATE_SIZE(BYTE, 1)
VALIDATE_SIZE(WORD, 2)
VALIDATE_SIZE(DWORD, 4)
VALIDATE_SIZE(QWORD, 8)

using BOOL = int;
using unk_t = int;
using SOCKET = int;
using HANDLE = void*;
using LONG = int;
using ULONG_PTR = unsigned int;



struct LIST_ENTRY {
    LIST_ENTRY *Flink;
    LIST_ENTRY *Blink;
};


struct _RTL_CRITICAL_SECTION_DEBUG {
    WORD Type;
    WORD CreatorBackTraceIndex;
    struct _RTL_CRITICAL_SECTION *CriticalSection;
    LIST_ENTRY ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Flags;
    WORD CreatorBackTraceIndexHigh;
    WORD SpareWORD;
};


struct _RTL_CRITICAL_SECTION {
    _RTL_CRITICAL_SECTION_DEBUG* DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;
};
using CRITICAL_SECTION = _RTL_CRITICAL_SECTION;


enum class EDestroyType {
	DT_Destructor = 0,
	DT_Delete = 1,
	DT_ArrayDestructor = 2,
	DT_ArrayDelete = 3,
};


/**
 * To have complete control over virtual calls (as the virtual tables are
 * defined by the engine), all virtual classes will have this form.
 *
 * Any virtual call like
 *    obj->Func();
 * will be called like
 *    obj->Virt()->Func(obj);
 */
struct VirtualClass {
    // copy this bit to the top of your class
    using vtable_t = struct vtable_ {
        //void (__thiscall *dtr)(VirtualClass*, EDestroyType);
    };
    vtable_t* Virt() const { return reinterpret_cast<vtable_t*>(vtable); }

    vtable_* vtable;
};



struct typeInfo
{	// 0x8+ bytes
	void *vtable;
	int zero;
	char name[];
};

struct classDesc
{	// 0x30+ bytes
	// at 0x4
	uint32_t trueDataOffset; // Subtraction
	// at 0xC
	void *typeInfo;
	// at 0x20
	void *beginParents; // +0x4
	void *endParents; // -0x4
	// at 0x28
	classDesc *parents[];
	//void* typeInfo;
};


struct FILE
{
    char *_ptr;
	int _cnt;
	char *_base;
	int _flag;
	int _file;
	int _charbuf;
	int _bufsiz;
	char *_tmpfname;
};

template<typename T>
struct basic_string;
using string = basic_string<char>;
using wstring = basic_string<wchar_t>;

wstring *__cdecl wstring_copy_ctor(wstring *ws, const char *s) asm("0x938720");
string *__thiscall InitString(string *this_, const char *str) asm("0x405550");
string *__thiscall AssignString(string *this_, const char *str, size_t size) asm("0x4059E0");

#define SSO_bytes 0x10ul
template<typename T>
struct basic_string {
    static constexpr uint32_t sso_size = SSO_bytes/sizeof(T);
    uint32_t ptr;  // ?
    T str[sso_size]; // pointer to data
    uint32_t strLen;
    uint32_t size; // capacity?

    basic_string() {
        ptr = 0;
        str[0] = T(0);
        strLen = 0;
        size = 0;
    }

    basic_string(const char*s) {
        if constexpr(std::is_same_v<char, T>)
        InitString(this, s); else
        if constexpr(std::is_same_v<wchar_t, T>)
        wstring_copy_ctor(this, s); else
        static_assert(false, "Unknown type T.");
    }

    const T* data() {
        return size < sso_size ? &str : *(const T**)str;
    }
};

VALIDATE_SIZE(string, 0x1C)
static_assert(string::sso_size == 0x10);
VALIDATE_SIZE(wstring, 0x1C)
static_assert(wstring::sso_size == 0x8);


template<typename T>
struct vector
{	// 0x10 bytes
	uint32_t pad;
	T *begin, *end, *capacity_end;

	T operator[](int i) { return begin[i]; }
	size_t size() { return begin ? end - begin : 0; }
};
VALIDATE_SIZE(vector<unk_t>, 0x10)

template<typename T>
struct list
{       // 0xC bytes
	T *begin, *end, *capacity_end;

	T operator[](int i) { return begin[i]; }
	size_t size() { return begin ? end - begin : 0; }
};
VALIDATE_SIZE(list<unk_t>, 0xC)

template<class T>
struct linked_list
{
	linked_list<T> *next;
	linked_list<T> *prev;
	T item;
};



extern "C" {
void* realloc(void *ptr, size_t new_size) asm("0x957B00");
void* malloc(size_t size) asm("0x958B20");
void free(void *ptr) asm("0x958C40");
size_t msize(void *memblock) asm("0x957EA0");
void* calloc(size_t num, size_t size) asm("0x957AB0");
void* memset(void *dest, int ch, size_t count) asm("0xA89110");
void* memcpy(void *dest, const void *src, size_t count) asm("0xA89190");
size_t strlen(const char *str) asm("0xA94450");
int strcmp(const char *str1, const char *str2) asm("0xAA549E");
int sprintf_s(char *Buffer, size_t BufferCount, const char *Format, ...) asm("0xA82F32");
float sqrtf(float) asm("0x452FC0");
}


int FileWrite(int fileIndex, const char *str, int strlen) asm("0xA9BAAC"); //index 3 is log.
int write_nolock(FILE* file, const char *str, int strlen) asm("0xA9B4E6");
bool CopyToClipboard(const wchar_t *str) asm("0x4F2730");
void* shi_new(size_t size) asm("0xA825B9");



#define GetModuleHandleA  WDecl(0xC0F378, __stdcall void* (*)(const char *lpLibFileName))
#define GetProcAddress    WDecl(0xC0F48C, __stdcall void* (*)(void* hModule, const char *lpProcName))
#define GetCurrentProcess WDecl(0xC0F58C, __stdcall void* (*)())

#define QueryPerformanceCounter   WDecl(0xC0F470, __stdcall bool (*)(int64_t*))
#define QueryPerformanceFrequency WDecl(0xC0F46C, __stdcall bool (*)(int64_t*))

#define DebugLog(_s) LogF("%s", (_s))

template <typename T>
struct Result {
    T *object = nullptr;
    const char *reason = nullptr;

    constexpr static Result<T> Fail(const char *reason) { return {nullptr, reason}; }
    constexpr static Result<T> Success(void *data) { return {(T *)data, nullptr}; }

    inline bool IsFail() { return reason != nullptr; }
};

