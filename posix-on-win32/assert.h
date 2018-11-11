// <assert.h>
//
// Defined in ISO C18 Standard: 7.21 Input/output <assert.h>.
// Also defined in POSIX.1-2017 <assert.h>, identical to ISO C99.
// verify program assertion
// See http://pubs.opengroup.org/onlinepubs/9699919799.2018edition/basedefs/assert.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__ASSERT_H
#define _POSIX_ON_WIN32__ASSERT_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// TBD - we don't want to use the Windows assert.h, we want to use our own,
// so that we can support __func__ (Microsoft does not)

// Default to using the Windows assert.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_ASSERT
#define _POSIX_ON_WIN32_USE_WIN32_ASSERT
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_ASSERT)

#pragma push_macro("_CRT_NO_TIME_T")
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#include _MICROSOFT_UCRT_INCLUDE_NEXT(assert.h)
#pragma pop_macro("_CRT_NO_TIME_T")

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_ASSERT)

// -----------------------------------------------------------------------------------------------

// Otherwise, we have to declare a complete <assert.h> environment
// that works for both POSIX and Windows-kinda-POSIX
#if !defined(_POSIX_ON_WIN32_USE_WIN32_ASSERT)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_ASSERT)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__ASSERT_H
