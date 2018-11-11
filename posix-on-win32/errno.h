// <errno.h>
//
// ISO C18 Standard: 7.5 errno.h header file
// system error numbers
// Extended by POSIX.1-2017 <errno.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__ERRNO_H
#define _POSIX_ON_WIN32__ERRNO_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// Default to using the Windows errno.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_ERRNO
#define _POSIX_ON_WIN32_USE_WIN32_ERRNO
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_ERRNO)

// Microsoft does support thread-local errno, so we use it.

// Only a few ERRNO constants are returned from Microsoft code.
// - E2BIG, EACCES, EAGAIN, EBADF, ECHILD, EDEADLOC, EDOM,
//   EEXIST, EILSEQ, EINVAL, EMFILE, ENOENT, ENOEXEC, ENOMEM,
//   ENOSPC, ERANGE, EXDEV, STRUNCATE
// The rest are defined "just to be complete"
// See https://docs.microsoft.com/en-us/cpp/c-runtime-library/errno-constants?view=vs-2017

// When we include the Windows <errno.h>, do not let it
// introduce specific types
#pragma push_macro("__STDC__")
#pragma push_macro("_CRT_NO_TIME_T")
#pragma push_macro("_CRT_NO_POSIX_ERROR_CODES")
#undef __STDC__
#define __STDC__ 1
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#undef _CRT_NO_POSIX_ERROR_CODES
#pragma push_macro("errno")
#undef errno
#include _MICROSOFT_UCRT_INCLUDE_NEXT(errno.h)
#pragma pop_macro("errno")
#pragma pop_macro("__STDC__")
#pragma pop_macro("_CRT_NO_TIME_T")
#pragma pop_macro("_CRT_NO_POSIX_ERROR_CODES")

// Errno values missing from Microsoft headers. Use numbers well outside their range.
#define EDQUOT          300  // Reserved.
#define EMULTIHOP       301  // Reserved.

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_ERRNO)

// -----------------------------------------------------------------------------------------------

#if !defined(_POSIX_ON_WIN32_USE_WIN32_ERRNO)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_ERRNO)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__ERRNO_H
