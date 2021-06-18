#pragma once
#include <stdint.h>
#ifndef _DETOURS_H_
#define _DETOURS_H_

#define DETOURS_VERSION 0x4c0c1

#define DETOUR_INSTRUCTION_TARGET_NONE          ((void *)0)
#define DETOUR_INSTRUCTION_TARGET_DYNAMIC       ((void *)(long *)-1)
#define DETOUR_SECTION_HEADER_SIGNATURE         0x00727444   // "Dtr\0"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define DETOUR_OFFLINE_LIBRARY(x)                                       \
void *DetourCopyInstruction##x(AddrBuffer pDst,              \
                            void * *ppDstPool,     \
                            AddrBuffer pSrc,                  \
                            void * *ppTarget,        \
                            long *plExtra);

extern int DetoursLastError;

enum DetoursErrors {
    DetoursNoError = 0,
    DetoursInvalidData = 1,
};

struct AddrBuffer {
    uintptr_t addr;
    uint8_t *buf;
};

#ifdef __cplusplus
}
#endif // __cplusplus

#endif