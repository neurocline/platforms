// <assert.h>
// - verify program assertion
//
// Defined in ISO C18 Standard: 7.2 Diagnostics <assert.h>.
// POSIX.1-2017 <assert.h> aligned with ISO C.
// Glibc extensions.

#include <internal/carp.h>

// ---------------------------------------------------------------------------
// Diagnostic header

// NDEBUG is used to compile out assertions
#if defined(NDEBUG)
#define assert(condition) ((void)0)
#else

// __func__ didn't exist until C99 and C++11, so use
// empty string before that point. This is a good place to insert
// platform-specific __func__ workarounds.
#undef __FUNC__
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
    || (defined(__cplusplus) && __cplusplus >= 201103L)
#define __FUNC__ __func__
#else
#define __FUNC__ ""
#endif

#define assert(condition) ((condition) ? ((void)0) : \
    __assert_impl(#condition, __FILE__, __LINE__, __FUNC__))

#endif // !defined(NDEBUG)

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
#ifndef DIAGNOSTIC_ISO_C18_ASSERT_H
#define DIAGNOSTIC_ISO_C18_ASSERT_H

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

// Typically, assert(condition) tests the condition and dispatches to
// a function like this to do the actual work of the assert.
// If you follow the C standard precisely, this writes a message on
// the standard error stream and then calls the abort function.
CARP("Glibc: assert()") void __assert_impl(const char* assertion, const char* file,
               unsigned int line, const char* function);

// This is typically a function that converts the errnum to a error
// message string and then calls __assert_impl.
#if defined(_GNU_SOURCE)
CARP("Glibc: assert_perror()") void __assert_perror_impl(int errnum, const char* file,
               unsigned int line, const char* function);
#endif

#ifdef  __cplusplus
}
#endif

// -----------------------------------------------------------------------------------------------

#endif // DIAGNOSTIC_ISO_C18_ASSERT_H
