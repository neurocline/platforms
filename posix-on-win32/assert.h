// <assert.h>
// - verify program assertion
//
// Defined in ISO C18 Standard: 7.2 Diagnostics <assert.h>.
// POSIX.1-2017 <assert.h> aligned with ISO C.
// Glibc extensions.

// Default to using the Windows assert.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_ASSERT
#define _POSIX_ON_WIN32_USE_WIN32_ASSERT
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_ASSERT)
// Get MSVC emulation of #include_next
#include <posix_win32_include_next.h>

#pragma push_macro("_CRT_NO_TIME_T")
#pragma push_macro("_CRT_NONSTDC_NO_DEPRECATE")
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#undef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include _MICROSOFT_UCRT_INCLUDE_NEXT(assert.h)
#pragma pop_macro("_CRT_NONSTDC_NO_DEPRECATE")
#pragma pop_macro("_CRT_NO_TIME_T")

// ----------------------------
// C11

#if !defined __cplusplus && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define static_assert _Static_assert
#endif

// ----------------------------
// Glibc

// Their pattern is that system headers use __USE_GNU but that this is set
// from _GNU_SOURCE by a prefix header (like <features.h>)
#if defined(_GNU_SOURCE)

#if defined(NDEBUG)
#define assert_perror(errnum) ((void)0)
#else
#define assert_perror(errnum) (!(errnum) ? ((void)0) : \
    __assert_perror_impl((errnum), __FILE__, __LINE__, __FUNC__))
#endif

#endif // defined(_GNU_SOURCE)

// ---------------------------------------------------------------------------
// Implementation detail

// TBD - we don't want to use the Windows assert.h, we want to use our own,
// so that we can support __func__ (Microsoft does not)

// This is the one header in C and C++ that does not have an include guard
// around the whole thing, and it can't use #pragma once either. This is to
// allow assert behavior to be toggled on/off in a translation unit.
#ifndef _POSIX_ON_WIN32_ISO_ASSERT_H
#define _POSIX_ON_WIN32_ISO_ASSERT_H

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

// This is typically a function that converts the errnum to a error
// message string and then calls __assert_impl.
#if defined(_GNU_SOURCE)
void __assert_perror_impl(int errnum, const char* file,
               unsigned int line, const char* function);
#endif

#ifdef  __cplusplus
}
#endif

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32_ISO_ASSERT_H
#endif // defined(_POSIX_ON_WIN32_USE_WIN32_ASSERT)

// -----------------------------------------------------------------------------------------------

#if !defined(_POSIX_ON_WIN32_USE_WIN32_ASSERT)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_ASSERT)

