// <stddef.h>
// - standard type definitions
//
// Defined in ISO C18 Standard: 7.19 Common definitions <stddef.h>.
// Aligned with POSIX.1-2017 <stddef.h>

#ifndef CANONICAL_ISO_C18_STDDEF_H
#define CANONICAL_ISO_C18_STDDEF_H

// ---------------------------------------------------------------------------
// Canonical header

// Null pointer constant.
// [CX] The macro shall expand to an integer constant expression with the value 0 cast to type void *.
// For C++, NULL is simply the value 0.
#ifndef __cplusplus
#define NULL ((void*) 0)
#else
#define NULL 0
#endif

// Integer constant expression of type size_t, the value of which is the
// offset in bytes to the structure member (member-designator), from
// the beginning of its structure (type).
#define offsetof(T, m) ((size_t)&(((T*)0)->m))

// Signed integer type of the result of subtracting two pointers
#ifdef _WIN64
typedef long long ptrdiff_t;
#else
typedef int ptrdiff_t;
#endif

// Integer type whose range of values can represent distinct codes for all
// members of the largest extended character set specified among the supported
// locales; the null character shall have the code value zero. Each member
// of the basic character set shall have a code value equal to its value when
// used as the lone character in an integer character constant if an
// implementation does not define __STDC_MB_MIGHT_NEQ_WC__.
// This is a builtin type for C++
#ifndef __cplusplus
typedef unsigned short wchar_t;
#endif

// Unsigned integer type of the result of the sizeof operator
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif

#endif // CANONICAL_ISO_C18_STDDEF_H
