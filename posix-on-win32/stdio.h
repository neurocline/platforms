// <stdio.h>
//
// POSIX.1-2008.7 sys/types.h header file
// data types
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdio.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__STDIO_H
#define _POSIX_ON_WIN32__STDIO_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// Default to using the Windows stdio.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_STDIO
#define _POSIX_ON_WIN32_USE_WIN32_STDIO
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

// When we include the Windows <stdio.h>, do not let it
// introduce specific types
#pragma push_macro("__STDC__")
#pragma push_macro("_CRT_NO_TIME_T")
#undef __STDC__
#define __STDC__ 1
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#include _MICROSOFT_UCRT_INCLUDE_NEXT(stdio.h)
#pragma pop_macro("__STDC__")
#pragma pop_macro("_CRT_NO_TIME_T")

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

// -----------------------------------------------------------------------------------------------

// Otherwise, we have to declare a complete <stdio.h> environment
// that works for both POSIX and Windows-kinda-POSIX
#if !defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__STDIO_H
