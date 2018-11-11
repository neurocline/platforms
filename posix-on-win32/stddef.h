// <stddef.h>
//
// Defined in ISO C18 Standard: 7.19 Common definitions <stddef.h>.
// Also defined in POSIX.1-2017 <stddef.h>, identical to ISO C99.
// standard type definitions
// See http://pubs.opengroup.org/onlinepubs/9699919799.2018edition/basedefs/stddef.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__STDDEF_H
#define _POSIX_ON_WIN32__STDDEF_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// Default to using the Windows stddef.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_STDDEF
#define _POSIX_ON_WIN32_USE_WIN32_STDDEF
#endif

// There's not much reason in actually wrapping this, other than symmetry, because
// the Windows stddef.h makes a complete ISO C and POSIX header. The only reason to
// suppress it would be that the Windows stddef.h, like many other Microsoft header
// files, puts things in the wrong places, and that's more of a maintenance issue,
// not a correctness issue.

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_STDDEF)

#include _MICROSOFT_UCRT_INCLUDE_NEXT(stddef.h)

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_STDDEF)

// -----------------------------------------------------------------------------------------------

// Otherwise, we have to declare a complete <assert.h> environment
// that works for both POSIX and Windows-kinda-POSIX
#if !defined(_POSIX_ON_WIN32_USE_WIN32_STDDEF)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_STDDEF)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__STDDEF_H
