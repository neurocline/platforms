// <errno.h>
// - system error numbers
//
// Defined in ISO C18 Standard: 7.5 Errors <errno.h>.
// Extended in POSIX.1-2017 <errno.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html

#pragma once
#ifndef DIAGNOSTIC_ISO_C18_ERRNO_H
#define DIAGNOSTIC_ISO_C18_ERRNO_H

#include <internal/carp.h>

// ---------------------------------------------------------------------------
// Diagnostic header

// All identifiers matching the pattern E[A-Z0-9].+ are reserved for
// future use.

#define EDOM 18
#define EILSEQ 25
#define ERANGE 72

// According to the standard, this needs to be a modifiable lvalue that
// has thread-local storage duration. It could be a function returning
// an lvalue, e.g. int *errno()
extern int errno;

// ----------------------------
// POSIX

// We use an arbitrary numbering, because it should not matter. If we interop
// with a lower platform layer, we need to mimic their numbers, and so we would
// tunnel their errno.h definition

// The standard notes that there are pairs of error constants that are
// allowed to map to the same value. They are
// - EAGAIN and EWOULDBLOCK
// - ENOTSUP and EOPNOTSUPP
// It would be nice if the standard stopped being wishy-washy, and just said
// these were the same error values.

#define E2BIG           1   // Argument list too long.
#define EACCES          2   // Permission denied.
#define EADDRINUSE      3   // Address in use.
#define EADDRNOTAVAIL   4   // Address not available.
#define EAFNOSUPPORT    5   // Address family not supported.
#define EAGAIN          6   // Resource unavailable, try again (may be the same value as EWOULDBLOCK).
#define EALREADY        7   // Connection already in progress.
#define EBADF           8   // Bad file descriptor.
#define EBADMSG         9   // Bad message.
#define EBUSY           10  // Device or resource busy.
#define ECANCELED       11  // Operation canceled.
#define ECHILD          12  // No child processes.
#define ECONNABORTED    13  // Connection aborted.
#define ECONNREFUSED    14  // Connection refused.
#define ECONNRESET      15  // Connection reset.
#define EDEADLK         16  // Resource deadlock would occur.
#define EDESTADDRREQ    17  // Destination address required.
#define EDOM            18  // Mathematics argument out of domain of function.
#define EDQUOT          19  // Reserved.
#define EEXIST          20  // File exists.
#define EFAULT          21  // Bad address.
#define EFBIG           22  // File too large.
#define EHOSTUNREACH    23  // Host is unreachable.
#define EIDRM           24  // Identifier removed.
#define EILSEQ          25  // Illegal byte sequence.
#define EINPROGRESS     26  // Operation in progress.
#define EINTR           27  // Interrupted function.
#define EINVAL          28  // Invalid argument.
#define EIO             29  // I/O error.
#define EISCONN         30  // Socket is connected.
#define EISDIR          31  // Is a directory.
#define ELOOP           32  // Too many levels of symbolic links.
#define EMFILE          33  // File descriptor value too large.
#define EMLINK          34  // Too many links.
#define EMSGSIZE        35  // Message too large.
#define EMULTIHOP       36  // Reserved.
#define ENAMETOOLONG    37  // Filename too long.
#define ENETDOWN        38  // Network is down.
#define ENETRESET       39  // Connection aborted by network.
#define ENETUNREACH     40  // Network unreachable.
#define ENFILE          41  // Too many files open in system.
#define ENOBUFS         42  // No buffer space available.
#define ENODATA         43  // [OB XSR] No message is available on the STREAM head read queue
#define ENODEV          44  // No such device.
#define ENOENT          45  // No such file or directory.
#define ENOEXEC         46  // Executable file format error.
#define ENOLCK          47  // No locks available.
#define ENOLINK         48  // Reserved.
#define ENOMEM          49  // Not enough space.
#define ENOMSG          50  // No message of the desired type.
#define ENOPROTOOPT     51  // Protocol not available.
#define ENOSPC          52  // No space left on device.
#define ENOSR           53  // [OB XSR] No STREAM resources.
#define ENOSTR          54  // [OB XSR] Not a STREAM.
#define ENOSYS          55  // Functionality not supported.
#define ENOTCONN        56  // The socket is not connected.
#define ENOTDIR         57  // Not a directory or a symbolic link to a directory.
#define ENOTEMPTY       58  // Directory not empty.
#define ENOTRECOVERABLE 59  // State not recoverable.
#define ENOTSOCK        60  // Not a socket.
#define ENOTSUP         61  // Not supported (may be the same value as EOPNOTSUPP).
#define ENOTTY          62  // Inappropriate I/O control operation.
#define ENXIO           63  // No such device or address.
#define EOPNOTSUPP      64  // Operation not supported on socket (may be the same value as ENOTSUP).
#define EOVERFLOW       65  // Value too large to be stored in data type.
#define EOWNERDEAD      66  // Previous owner died.
#define EPERM           67  // Operation not permitted.
#define EPIPE           68  // Broken pipe.
#define EPROTO          69  // Protocol error.
#define EPROTONOSUPPORT 70  // Protocol not supported.
#define EPROTOTYPE      71  // Protocol wrong type for socket.
#define ERANGE          72  // Result too large.
#define EROFS           73  // Read-only file system.
#define ESPIPE          74  // Invalid seek.
#define ESRCH           75  // No such process.
#define ESTALE          76  // Reserved.
#define ETIME           77  // [OB XSR] Stream ioctl() timeout.
#define ETIMEDOUT       78  // Connection timed out.
#define ETXTBSY         79  // Text file busy.
#define EWOULDBLOCK     80  // Operation would block (may be the same value as EAGAIN).
#define EXDEV           81  // Cross-device link.

// ----------------------------
// Microsoft

// Microsoft defines this for some reason. Removed from POSIX? I can't find
// any mention of it. Maybe this is just a mistake on Microsoft's part.
#define EOTHER          82

// Microsoft safe-string functions using _TRUNCATE can return this error. From MSDN:
// "A string copy or concatenation resulted in a truncated string."
// https://docs.microsoft.com/en-us/cpp/c-runtime-library/truncate?view=vs-2017
#define STRUNCATE       83

// Support EDEADLOCK for compatibility
#define EDEADLOCK EDEADLK

// -----------------------------------------------------------------------------------------------

#endif // DIAGNOSTIC_ISO_C18_ERRNO_H
