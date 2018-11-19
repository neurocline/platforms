[!MSVCRT]
// There's not much reason in actually wrapping this, other than symmetry, because
// the Windows stddef.h makes a complete ISO C and POSIX header. The only reason to
// suppress it would be that the Windows stddef.h, like many other Microsoft header
// files, puts things in the wrong places, and that's more of a maintenance issue,
// not a correctness issue.
[/!MSVCRT]
[MSVCRT]
// Null pointer constant.
// [CX] The macro shall expand to an integer constant expression with the value 0 cast to type void *.
// For C++, NULL is simply the value 0.
#ifndef NULL
#ifndef __cplusplus
#define NULL ((void*) 0)
#else
#define NULL 0
#endif
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
[/MSVCRT]
