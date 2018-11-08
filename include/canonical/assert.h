// assert.h
//
// Defined in ISO C18 Standard: 7.2 Diagnostics <assert.h>.
// Unchanged since C11, where static_assert was added.
// Also defined in POSIX.1-2017 <assert.h>, identical to ISO C99.
// Glibc <assert.h> follows C11 standard.
// Microsoft <assert.h> follows C95 standard (no __func__).
// FreeBSD <assert.h> follows C99 standard (??).
// C++ <assert.h> is identical to ISO C99, and typically accessed through <casssert> wrapper.

// ---------------------------------------------------------------------------
// Canonical header

// ----------------------------
// C89

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
    __canonical_assert_impl(#condition, __FILE__, __LINE__, __FUNC__))

#endif // !defined(NDEBUG)

// ----------------------------
// C11

// (C++ already has static_assert)
#if !defined __cplusplus
#define static_assert _Static_assert
#endif

// ----------------------------
//
// GNU extension
// Their pattern is that system headers use __USE_GNU but that this is set
// from _GNU_SOURCE by a prefix header (like <features.h>)
#if defined(__USE_GNU)

#if defined(NDEBUG)
#define assert_perror(errnum) ((void)0)
#else
#define assert_perror(errnum) (!(errnum) ? ((void)0) : \
    __canonical_assert_perror_impl((errnum), __FILE__, __LINE__, __FUNC__))
#endif

#endif // defined(__USE_GNU)


// ---------------------------------------------------------------------------
// Implementation detail

// This is the one header in C and C++ that does not have an include guard
// around the whole thing, and it can't use #pragma once either. This is to
// allow assert behavior to be toggled on/off in a translation unit.
#ifndef CANONICAL_ISO_C18_ASSERT_H
#define CANONICAL_ISO_C18_ASSERT_H

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

// Typically, assert(condition) tests the condition and dispatches to
// a function like this to do the actual work of the assert.
// If you follow the C standard precisely, this writes a message on
// the standard error stream and then calls the abort function.
void __canonical_assert_impl(const char* assertion, const char* file,
               unsigned int line, const char* function);

// This is typically a function that converts the errnum to a error
// message string and then calls __canonical_assert_impl.
#if defined(__USE_GNU)
void __canonical_assert_perror_impl(int errnum, const char* file,
               unsigned int line, const char* function);
#endif

#ifdef  __cplusplus
}
#endif

#endif // CANONICAL_ISO_C18_ASSERT_H
