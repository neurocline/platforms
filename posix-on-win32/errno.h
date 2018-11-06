// errno.h
//
// POSIX.1-2008.7 errno.h header file
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__ERRNO_H
#define _POSIX_ON_WIN32__ERRNO_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// Do we want to use the Windows errno.h or not?
#ifndef _POSIX_ON_WIN32_NO_WIN32_ERRNO
#define _POSIX_ON_WIN32_USE_WIN32_ERRNO
#endif

// -----------------------------------------------------------------------------------------------

// If we are piggybacking on top of the Windows <errno.h>, just
// define what's missing
#if defined(_POSIX_ON_WIN32_USE_WIN32_ERRNO)

// Get as many Microsoft ERRNO values as we can
#pragma push_macro("_CRT_NO_POSIX_ERROR_CODES")
#undef _CRT_NO_POSIX_ERROR_CODES

// Only a few ERRNO constants are returned from Microsoft code. The rest are
// defined "just to be complete"
// - E2BIG, EACCES, EAGAIN, EBADF, ECHILD, EDEADLOC, EDOM,
//   EEXIST, EILSEQ, EINVAL, EMFILE, ENOENT, ENOEXEC, ENOMEM,
//   ENOSPC, ERANGE, EXDEV, STRUNCATE
// See https://docs.microsoft.com/en-us/cpp/c-runtime-library/errno-constants?view=vs-2017

// Errno values missing from Microsoft headers. Use numbers well outside their range.
#define EDQUOT          300  // Reserved.
#define EMULTIHOP       301  // Reserved.

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_ERRNO)

// -----------------------------------------------------------------------------------------------

// Otherwise, we have to declare a complete errno.h environment,
// including the errno global
#if !defined(_POSIX_ON_WIN32_USE_WIN32_ERRNO)

// errno acts like a global. For now, we just use a global, but this needs
// to be replaced with something that can be per-thread
extern int errno;

// We use an arbitrary numbering, because it should not matter. If we interop
// with a lower platform layer, we need to mimic their numbers, and so we would
// tunnel their errno.h definition

#define E2BIG			1	// Argument list too long.
#define EACCES			2	// Permission denied.
#define EADDRINUSE		3	// Address in use.
#define EADDRNOTAVAIL	4	// Address not available.
#define EAFNOSUPPORT	5	// Address family not supported.
#define EAGAIN			6	// Resource unavailable, try again (may be the same value as EWOULDBLOCK).
#define EALREADY		7	// Connection already in progress.
#define EBADF			8	// Bad file descriptor.
#define EBADMSG			9	// Bad message.
#define EBUSY			10	// Device or resource busy.
#define ECANCELED		11	// Operation canceled.
#define ECHILD			12	// No child processes.
#define ECONNABORTED	13	// Connection aborted.
#define ECONNREFUSED	14	// Connection refused.
#define ECONNRESET		15	// Connection reset.
#define EDEADLK			16	// Resource deadlock would occur.
#define EDESTADDRREQ	17	// Destination address required.
#define EDOM			18	// Mathematics argument out of domain of function.
#define EDQUOT			19	// Reserved.
#define EEXIST			20	// File exists.
#define EFAULT			21	// Bad address.
#define EFBIG			22	// File too large.
#define EHOSTUNREACH	23	// Host is unreachable.
#define EIDRM			24	// Identifier removed.
#define EILSEQ			25	// Illegal byte sequence.
#define EINPROGRESS		26	// Operation in progress.
#define EINTR			27	// Interrupted function.
#define EINVAL			28	// Invalid argument.
#define EIO				29	// I/O error.
#define EISCONN			30	// Socket is connected.
#define EISDIR			31	// Is a directory.
#define ELOOP			32	// Too many levels of symbolic links.
#define EMFILE			33	// File descriptor value too large.
#define EMLINK			34	// Too many links.
#define EMSGSIZE		35	// Message too large.
#define EMULTIHOP		36	// Reserved.
#define ENAMETOOLONG	37	// Filename too long.
#define ENETDOWN		38	// Network is down.
#define ENETRESET		39	// Connection aborted by network.
#define ENETUNREACH		40	// Network unreachable.
#define ENFILE			41	// Too many files open in system.
#define ENOBUFS			42	// No buffer space available.
#define ENODATA			43	// [OB XSR] No message is available on the STREAM head read queue
#define ENODEV			44	// No such device.
#define ENOENT			45	// No such file or directory.
#define ENOEXEC			46	// Executable file format error.
#define ENOLCK			47	// No locks available.
#define ENOLINK			48	// Reserved.
#define ENOMEM			49	// Not enough space.
#define ENOMSG			50	// No message of the desired type.
#define ENOPROTOOPT		51	// Protocol not available.
#define ENOSPC			52	// No space left on device.
#define ENOSR			53	// [OB XSR] No STREAM resources.
#define ENOSTR			54	// [OB XSR] Not a STREAM.
#define ENOSYS			55	// Functionality not supported.
#define ENOTCONN		56	// The socket is not connected.
#define ENOTDIR			57	// Not a directory or a symbolic link to a directory.
#define ENOTEMPTY		58	// Directory not empty.
#define ENOTRECOVERABLE	59	// State not recoverable.
#define ENOTSOCK		60	// Not a socket.
#define ENOTSUP 		61	// Not supported (may be the same value as EOPNOTSUPP).
#define ENOTTY			62	// Inappropriate I/O control operation.
#define ENXIO			63	// No such device or address.
#define EOPNOTSUPP		64	// Operation not supported on socket (may be the same value as ENOTSUP).
#define EOVERFLOW		65	// Value too large to be stored in data type.
#define EOWNERDEAD		66	// Previous owner died.
#define EPERM			67	// Operation not permitted.
#define EPIPE			68	// Broken pipe.
#define EPROTO			69	// Protocol error.
#define EPROTONOSUPPORT	70	// Protocol not supported.
#define EPROTOTYPE		71	// Protocol wrong type for socket.
#define ERANGE			72	// Result too large.
#define EROFS			73	// Read-only file system.
#define ESPIPE			74	// Invalid seek.
#define ESRCH			75	// No such process.
#define ESTALE			76	// Reserved.
#define ETIME			77	// [OB XSR] Stream ioctl() timeout.
#define ETIMEDOUT		78	// Connection timed out.
#define ETXTBSY			79	// Text file busy.
#define EWOULDBLOCK		80	// Operation would block (may be the same value as EAGAIN).
#define EXDEV			81	// Cross-device link.

// Microsft defines this for some reason. Removed from POSIX? I can't find
// any mention of it. Maybe this is just a mistake on Microsoft's part.
#define EOTHER			82

// Microsoft safe-string functions using _TRUNCATE can return this error. From MSDN:
// "A string copy or concatenation resulted in a truncated string."
// https://docs.microsoft.com/en-us/cpp/c-runtime-library/truncate?view=vs-2017
#define STRUNCATE       83

// Support EDEADLOCK for compatibility
#define EDEADLOCK EDEADLK

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_ERRNO)

// -----------------------------------------------------------------------------------------------

// Now pull in the platform header if desired
#ifdef _POSIX_ON_WIN32_USE_WIN32_ERRNO
// workaround to get Microsoft errno defined so we can
// then temporarily undefine it
#include <stddef.h>
#pragma push_macro("errno")
#undef errno
#include _MICROSOFT_UCRT_INCLUDE_NEXT(errno.h)
#pragma pop_macro("errno")
#pragma pop_macro("_CRT_NO_POSIX_ERROR_CODES")
#endif

#endif // _POSIX_ON_WIN32__ERRNO_H
