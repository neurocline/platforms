// <stddef.h>
// - standard type definitions
//
// Defined in ISO C18 Standard: 7.19 Common definitions <stddef.h>.
// Aligned with POSIX.1-2017 <stddef.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stddef.h.html

#pragma once
#ifndef _POSIX_ON_WIN32_ISO_STDDEF_H
#define _POSIX_ON_WIN32_ISO_STDDEF_H

// Default to using the Windows stddef.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_STDDEF
#define _POSIX_ON_WIN32_USE_WIN32_STDDEF
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_STDDEF)
// Get MSVC emulation of #include_next
#include <posix_win32_include_next.h>

#pragma push_macro("_CRT_NO_TIME_T")
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#pragma push_macro("__STDC__")
#undef __STDC__
#define __STDC__ 1
#include _MICROSOFT_UCRT_INCLUDE_NEXT(stddef.h)
#pragma pop_macro("_CRT_NO_TIME_T")
#pragma pop_macro("__STDC__")

// There's not much reason in actually wrapping this, other than symmetry, because
// the Windows stddef.h makes a complete ISO C and POSIX header. The only reason to
// suppress it would be that the Windows stddef.h, like many other Microsoft header
// files, puts things in the wrong places, and that's more of a maintenance issue,
// not a correctness issue.

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_STDDEF)

// -----------------------------------------------------------------------------------------------

#if !defined(_POSIX_ON_WIN32_USE_WIN32_STDDEF)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_STDDEF)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32_ISO_STDDEF_H
