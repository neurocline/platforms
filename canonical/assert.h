// assert.h
//
// ISO C99 Standard: 7.2 Diagnostics <assert.h>
// POSIX.1-2017 <assert.h>
// Glibc <assert.h>
// Microsoft <assert.h>
// FreeBSD <assert.h>

#ifndef CANONICAL_ISO_C99_ASSERT_H
#define CANONICAL_ISO_C99_ASSERT_H

// ---------------------------------------------------------------------------
// Canonical header

#if defined(CANONICAL_NODIAG)

#ifdef NDEBUG
#define assert(condition) ((void)0)
#else
#define assert(condition) ((condition) ? ((void)0) : \
    __canonical_assert_impl(#condition, __FILE__, __LINE__, __func__))
#endif

#endif // defined(CANONICAL_NODIAG)

// ---------------------------------------------------------------------------
// Diagnostic header

// By default, we emit diagnostics
#if !defined(CANONICAL_NODIAG)

#include <carp/carp.h>

// always "triggers" but we aren't building this to run, just to get used msgs
#define assert(condition) \
    __diagnostic_assert_impl(#condition, __FILE__, __LINE__, __func__)


#endif // !defined(CANONICAL_NODIAG)

// ---------------------------------------------------------------------------
// Implementation detail

// Typically, assert(condition) tests the condition and dispatches to
// a function to do the actual work of the assert. This is an implementation
// detail
void __canonical_assert_impl(const char* assertion, const char* file,
               unsigned int line, const char* function);

void CARP("ISO C99: assert()") \
__diagnostic_assert_impl(const char* assertion, const char* file,
               unsigned int line, const char* function);

#endif // CANONICAL_ISO_C99_ASSERT_H
