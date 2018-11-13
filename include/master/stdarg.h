// <stdarg.h>
// - handle variable argument list
//
// Defined in ISO C18 Standard: 7.16 Input/output <stdarg.h>.
// Aligned with POSIX.1-2017 <stdarg.h>

#pragma once
[GUARD]

[IGNOREWINDOWS]
[BODY]
[MSVCRT]
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

[/MSVCRT]
[!MSVCRT]
// We declare a complete-for-our-purposes and compatible <starg.h>, not
// because we can do it better than Microsoft, but to prevent information
// from other headers to leak in just because <stddef.h> was included.

// 7.16
typedef char* va_list;

// 7.16.1.2
#define va_copy(va_dst, va_src) ((va_dst) = (va_src))

// Amazingly, Windows x86 compilers lay out args in a regular fashion.
// Maybe by definition, a varargs function gets arguments laid out
// in a simple fashion? Note that this probably can't ever change, or
// precompiled libraries would break when linked to newer built code.
#if defined(_M_IX86) && !defined _M_HYBRID_X86_ARM64
    // x86 args laid out on stack left to right, 4-byte aligned

    // 7.16.1.4
    #ifdef __cplusplus
    // C++ 18.10 #228: Cast first in case unary operator& is overloaded for param's type.
    // (reinterpret_cast alone can't cast away cv-qualifiers, and static_cast could fail).
    #define va_start(va, param) ((void)(va = (va_list)(\
        &const_cast<char&>(reinterpret_cast<const volatile char&>(param)) + ((sizeof(param) + 3) & ~3))))
    #else
    #define va_start(va, param) ((void)(va = (va_list)&(param) + ((sizeof(param) + 3) & ~3)))
    #endif

    // 7.16.1.2
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

    // 7.16.1.4
    #define va_start(va, param) ((void)(__va_start(&va, param)))

    // 7.16.1.2
   #define va_arg(va, t) (                                   \
        (sizeof(t) > 8 || (sizeof(t) & (sizeof(t) - 1)) != 0) \
            ? **(t**)((va += 8) - 8)                          \
            : *(t* )((va += 8) - 8))

#else
    #error "Unsupported"
#endif

// 7.16.1.3
#define va_end(va) ((void)(va = (va_list)0))

[/!MSVCRT]
[FOOTER]
[/GUARD]
