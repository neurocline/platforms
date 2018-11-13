// <stdarg.h>
// - handle variable argument list
//
// Defined in ISO C18 Standard: 7.16 Input/output <stdarg.h>.
// Aligned with POSIX.1-2017 <stdarg.h>

#pragma once
#ifndef DIAGNOSTIC_ISO_C18_STDARG_H
#define DIAGNOSTIC_ISO_C18_STDARG_H

#include <internal/carp.h>

// ---------------------------------------------------------------------------
// Diagnostic header

// The function-like macros in <stdarg.h> need compiler knowledge in order
// to be implemenented, because there is no standard that mandates that
// arguments are laid out in memory in a specific way. If all compilers
// used cdecl calling convention in a naive way, then parameters would
// be laid out in memory from left to right, and you could just use
// simple typecasting to access arguments, as we do in this header file.
//
// However, compilers are not bound to do this, and in fact many compilers
// put arguments in registers or in other layouts.
//
// So, in reality, the va_arg mechanism requires compiler-specifics functions,
// because only the compiler knows in all cases where and how function
// arguments are placed. This is typically done with compiler intrinsics
// that are wrapped by the standard names.

// 7.16
typedef char* va_list;

// 7.16.1.1
#define va_arg(VA_LIST, ARG_TYPE) *(ARG_TYPE*)((VA_LIST += sizeof(ARG_TYPE)) - sizeof(ARG_TYPE))

// 7.16.1.2
#define va_copy(DEST_VA_LIST, SRC_VA_LIST) (void)(DEST_VA_LIST = SRC_VA_LIST)

// 7.16.1.3
#define va_end(VA_LIST) (void)(VA_LIST = (va_list)0)

// 7.16.1.4
#define va_start(VA_LIST, VA_PARAM) (void)(VA_LIST = (char*)&VA_PARAM)

// -----------------------------------------------------------------------------------------------

#endif // DIAGNOSTIC_ISO_C18_STDARG_H
