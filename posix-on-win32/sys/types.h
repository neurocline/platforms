// <sys/types.h>
//
// POSIX.1-2008.7 sys/types.h header file
// data types
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_types.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__SYS_TYPES_H
#define _POSIX_ON_WIN32__SYS_TYPES_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// Default to using the Windows sys/types.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_SYS_TYPES
#define _POSIX_ON_WIN32_USE_WIN32_SYS_TYPES
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_SYS_TYPES)

// When we include the Windows <sys/types.h>, do not let it
// introduce the standard types ino_t, dev_t and off_t. Their
// code doesn't use these, and their definitions clash with ours.
#pragma push_macro("__STDC__")
#pragma push_macro("_CRT_NO_TIME_T")
#undef __STDC__
#define __STDC__ 1
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#include _MICROSOFT_UCRT_INCLUDE_NEXT(sys/types.h)
#pragma pop_macro("__STDC__")
#pragma pop_macro("_CRT_NO_TIME_T")

// size_t and ssize_t need to be at least as big as the address space
// (and must match each other in size).
// - size_t is used for sizes of objects. Must be unsigned integer.
// - ssize_t is used for a count of bytes or error indication. Must be signed integer.
#ifdef _WIN64
typedef unsigned long long size_t;
typedef long long ssize_t;
#else
typedef unsigned int size_t;
typedef int ssize_t;
#endif

// Make time_t be the largest natural size.
// This is used for time in seconds.
#ifdef _WIN64
typedef long long time_t;
#else
typedef int time_t;
#endif

typedef int blkcnt_t; // Used for file block counts.
typedef int blksize_t; // Used for block sizes. Must be signed integer.
typedef unsigned int dev_t; // Used for device IDs.
typedef unsigned int gid_t; // Used for group IDs.
typedef int ino_t; // Used for file serial numbers.
typedef unsigned int mode_t; // Used for some file attributes.
typedef int nlink_t; // Used for link counts.
typedef long long off_t; // Used for file sizes.
typedef unsigned int uid_t; // Used for user IDs.

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_SYS_TYPES)

// -----------------------------------------------------------------------------------------------

// Otherwise, we have to declare a complete <sys/types.h> environment
// that works for both POSIX and Windows-kinda-POSIX
#if !defined(_POSIX_ON_WIN32_USE_WIN32_SYS_TYPES)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_SYS_TYPES)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__SYS_TYPES_H
