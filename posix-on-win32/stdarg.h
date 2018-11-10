// <stdarg.h>
//
// ISO C18 Standard: 7.16 stdarg.h header file
// handle variable argument list
// Aligned with POSIX.1-2017 <stdarg.h
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdarg.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__STDARG_H
#define _POSIX_ON_WIN32__STDARG_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// Default to not using the Windows stdarg.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_STDARG
//#define _POSIX_ON_WIN32_USE_WIN32_STDARG
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_STDARG)

#error "This path not supported"

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_STDARG)

// -----------------------------------------------------------------------------------------------

// We declare a complete but compatible <starg.h>. We do this because we don't
// want Windows to include internal header files. Many details of ISO and
// POSIX headers are put into internal headers and thus visible to every header.
// This causes us problems, so we work around it by restricting key visible
// items or just eliminating use of the system header.
#if !defined(_POSIX_ON_WIN32_USE_WIN32_STDARG)

typedef char* va_list;

// Amazingly, Windows x86 compilers lay out args in a regular fashion.
// Maybe by definition, a varargs function gets arguments laid out
// in a simple fashion? Note that this probably can't ever change, or
// precompiled libraries would break when linked to newer built code.
#if defined(_M_IX86) && !defined _M_HYBRID_X86_ARM64
    // x86 args laid out on stack left to right, 4-byte aligned

    #ifdef __cplusplus
    // C++ 18.10 #228: Cast first in case unary operator& is overloaded for param's type.
    // (reinterpret_cast alone can't cast away cv-qualifiers, and static_cast could fail).
    #define va_start(va, param) ((void)(va = (va_list)(\
        &const_cast<char&>(reinterpret_cast<const volatile char&>(param)) + ((sizeof(param) + 3) & ~3))))
    #else
    #define va_start(va, param) ((void)(va = (va_list)&(param) + ((sizeof(param) + 3) & ~3)))
    #endif

    #define va_arg(va, t) (*(t*)((va += ((sizeof(t) + 3) & ~3)) - ((sizeof(t) + 3) & ~3)))

// However, Windows x64 compilers aren't simple enough to do in macro
// form, so there are internal compiler functions to do it for us.
#elif defined(_M_X64)

    // Magic intrinsic that compiler uses to insert "address" of arg, wrapped
    // in extern "C" to handle C++ compiler inclusion
    void __cdecl __va_start(va_list* , ...);

    // x64 args laid out on stack left to right, 8-byte aligned, except
    // that >8-byte arguments and non-power-of-2-size arguments aren't on the
    // stack; instead a pointer to the arg is on the stack.
    // We use the bit-hacking trick is_pow2(n) { return (n & (n-1)) == 0; }

    #define va_start(va, param) ((void)(__va_start(&va, param)))

    #define va_arg(va, t) (                                   \
        (sizeof(t) > 8 || (sizeof(t) & (sizeof(t) - 1)) != 0) \
            ? **(t**)((va += 8) - 8)                          \
            : *(t* )((va += 8) - 8))

#else
    #error "Unsupported"
#endif

#define va_end(va) ((void)(va = (va_list)0))
#define va_copy(va_dst, va_src) ((va_dst) = (va_src))

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_STDARG)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__STDARG_H
