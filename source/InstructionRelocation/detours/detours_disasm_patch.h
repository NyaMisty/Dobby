#include "detours.h"
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

#ifndef _In_opt_
#define _In_opt_
#endif

#ifndef _In_
#define _In_
#endif

#ifndef _Out_opt_
#define _Out_opt_
#endif

#define WINAPI

typedef char CHAR;
typedef uint8_t BYTE;
typedef uint8_t *PBYTE;
typedef uint16_t USHORT;
typedef int16_t SHORT;
typedef int32_t BOOL;
typedef int32_t INT, INT32;
typedef uint32_t UINT, UINT32;
typedef long long LONGLONG;
typedef void VOID, *HMODULE, *PVOID;
#define TRUE ((BOOL)1)
#define FALSE ((BOOL)0)
typedef long LONG;
typedef unsigned long ULONG;
typedef uintptr_t ULONG_PTR;
typedef intptr_t LONG_PTR;
typedef size_t SIZE_T;

#define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]
#define ARRAYSIZE(A) (sizeof(A)/sizeof(A[0]))

#define UNALIGNED

struct PBYTEMEM {
    uint8_t *m_buf;
    uintptr_t m_addr;

    explicit PBYTEMEM() : m_addr(0), m_buf(NULL) {
    }
    PBYTEMEM(AddrBuffer &addrbuf) : PBYTEMEM(addrbuf.buf, addrbuf.addr) {}
    PBYTEMEM(uint8_t *buf, uintptr_t addr) : m_buf(buf), m_addr(addr) { }
    
    BYTE &operator[](size_t idx) {
        return m_buf[idx];
    }

    template<typename T>
    PBYTEMEM operator+(T off) {
        return PBYTEMEM(m_buf + off, m_addr + off);
    }

    ptrdiff_t operator-(PBYTEMEM &mem) { return m_addr - mem.m_addr; };
    operator ULONG *() { return (ULONG *)m_buf; };

    operator PBYTE *() { return (PBYTE *)m_buf; };

    operator PVOID() { return (PVOID)m_buf; };

    operator PBYTE() { return (PBYTE)m_buf; };

    friend bool operator==(void *a, PBYTEMEM &b) {
        return (uintptr_t)a == b.m_addr;
    }

    void operator=(BYTE *b) {
        return;
    }
};

#define UNREFERENCED_PARAMETER(P) (P)

#define ERROR_INVALID_DATA DetoursInvalidData

static void SetLastError(int err) {
    DetoursLastError = err;
}

static ULONG DetourGetModuleSize(HMODULE) {
    return 0x1337;
}

static void CopyMemory(
  _In_       PVOID  Destination,
  _In_ const VOID   *Source,
  _In_       SIZE_T Length
) {
    memcpy(Destination, Source, Length);
}
