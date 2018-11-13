// <limits.h>
// - implementation-defined constants
//
// Defined in ISO C18 Standard: 7.10 Sizes of integer types <limits.h>.
// (and really defined in 5.2.4.2.1)
// Extended in POSIX.1-2017 <limits.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/limits.h.html

#pragma once
[GUARD]

[MICROSOFT_VC_INCLUDE]
[BODY]
[MSVCRT]
// number of bits for smallest object that is not a bit-field (byte)
// [CX] Value: 8
#define CHAR_BIT 8

// minimum value for an object of type signed char
// [CX] Value: -128
#define SCHAR_MIN -128 // -(2^7 - 1)

// maximum value for an object of type signed char
// [CX] Value: +127
#define SCHAR_MAX +127 // +(2^7 - 1)

// maximum value for an object of type unsigned char
// [CX] Value: 255
#define UCHAR_MAX 255 // 2^8 - 1

// If an object of type char can hold negative values, the value
// of CHAR_MIN shall be the same as that of SCHAR_MIN and the value
// of CHAR_MAX shall be the same as that of SCHAR_MAX. Otherwise,
// the value of CHAR_MIN shall be 0 and the value of CHAR_MAX shall
// be the same as that of UCHAR_MAX.

// Some compilers that have plain char as unsigned: Cray T90, Cray SV1,
// Cray T3E, SGI MIPS IRIX, IBM PowerPC AIX. Also apparently anything
// that still uses EBCDIC. So, big TBD.

// minimum value for an object of type char
// Value: SCHAR_MIN or 0
#define CHAR_MIN -128

// maximum value for an object of type char
// Value: UCHAR_MAX or SCHAR_MAX
#define CHAR_MAX +127

// maximum number of bytes in a multibyte character, for any supported locale
// POSIX: Minimum Acceptable Value: 1
#define MB_LEN_MAX 1

// minimum value for an object of type short int
// POSIX: Maximum Acceptable Value: -32 767
#define SHRT_MIN -32767 // -(2^15 - 1)

// maximum value for an object of type short int
// POSIX: Minimum Acceptable Value: +32 767
#define SHRT_MAX +32767 // +(2^15 - 1)

// maximum value for an object of type unsigned short int
// POSIX: Minimum Acceptable Value: 65 535
#define USHRT_MAX 65535 // 2^16 - 1

// minimum value for an object of type int
// [CX] Maximum Acceptable Value: -2 147 483 647
#define INT_MIN -2147483647

// maximum value for an object of type int
// [CX] Must be at least: 2 147 483 647
#define INT_MAX +2147483647

// maximum value for an object of type unsigned int
// [CX]  Minimum Acceptable Value: 4 294 967 295
#define UINT_MAX 4294967295 // 2^32 - 1

// define minimum value for an object of type long int
// POSIX: Maximum Acceptable Value: -2 147 483 647
#define LONG_MIN -2147483647 // −(2^31 - 1)

// maximum value for an object of type long int
// POSIX: Minimum Acceptable Value: +2 147 483 647
#define LONG_MAX +2147483647 // +(2^31 - 1)

// maximum value for an object of type unsigned long int
// POSIX: Minimum Acceptable Value: 4 294 967 295
#define ULONG_MAX 4294967295 // 2^32 - 1

// minimum value for an object of type long long int
// POSIX: Maximum Acceptable Value: -9223372036854775807
#define LLONG_MIN -9223372036854775807 // -(2^63 - 1)

// maximum value for an object of type long long int
// POSIX: Must be at least: +9223372036854775807
#define LLONG_MAX +9223372036854775807 // +(2^63 - 1)

// maximum value for an object of type unsigned long long int
// POSIX: Minimum Acceptable Value: 18446744073709551615
#define ULLONG_MAX 18446744073709551615 // 2^64 - 1

[/MSVCRT]
[POSIX]
// Note: limits here are constrained by values found in <unistd.h>;
// all these values are names prefixed with _POSIX

// ----------
// Runtime Invariant Values (Possibly Indeterminate)
//
// A definition of one of the symbolic constants in the following list shall
// be omitted from <limits.h> on specific implementations where the
// corresponding value is equal to or greater than the stated minimum,
// but is unspecified.
//
// This indetermination might depend on the amount of available memory space
// on a specific instance of a specific implementation. The actual value
// supported by a specific instance shall be provided by the sysconf() function.
//
// That said, I will not follow that rule, for documentation purposes. The
// point of the rule is that many of these can be dynamic values, and the minimum
// values are specified by corresponding _POSIX-prefixed constants in <unistd.h>
//
// And, many of these only make sense on a very UNIX-like system, so their
// values on a non-UNIX system are irrelevant.

// Maximum number of I/O operations in a single list I/O call supported by the implementation.
// Must be at least _POSIX_AIO_LISTIO_MAX}
#define AIO_LISTIO_MAX 1

// Maximum number of outstanding asynchronous I/O operations supported by the implementation.
// Must be at least: _POSIX_AIO_MAX
#define AIO_MAX 1

// The maximum amount by which a process can decrease its asynchronous I/O priority level from its own scheduling priority.
// Must be at least: 0
#define AIO_PRIO_DELTA_MAX 0

// Maximum length of argument to the exec functions including environment data.
// Must be at least: _POSIX_ARG_MAX
#define ARG_MAX 1

// Maximum number of functions that may be registered with atexit().
// Must be at least: 32
#define ATEXIT_MAX 32

// Maximum number of simultaneous processes per real user ID.
// Must be at least: _POSIX_CHILD_MAX
#define CHILD_MAX 1024

// Maximum number of timer expiration overruns.
// Must be at least: _POSIX_DELAYTIMER_MAX
#define DELAYTIMER_MAX 1

// Maximum length of a host name (not including the terminating null) as returned from the gethostname() function.
// Must be at least: _POSIX_HOST_NAME_MAX
#define HOST_NAME_MAX 1

// [XSI]
// Maximum number of iovec structures that one process has available for use with readv() or writev().
// Must be at least: _XOPEN_IOV_MAX
#define IOV_MAX 1

// Maximum length of a login name.
// Must be at least: _POSIX_LOGIN_NAME_MAX
#define LOGIN_NAME_MAX 32

// [MSG]
// The maximum number of open message queue descriptors a process may hold.
// Must be at least: _POSIX_MQ_OPEN_MAX
#define MQ_OPEN_MAX 1

// [MSG]
// The maximum number of message priorities supported by the implementation.
// Must be at least: _POSIX_MQ_PRIO_MAX
#define MQ_PRIO_MAX 1

// A value one greater than the maximum value that the system may assign to a newly-created file descriptor.
// Must be at least: _POSIX_OPEN_MAX
#define OPEN_MAX 256

// Size in bytes of a page.
// Must be at least: 1
#define PAGESIZE 4096

// [XSI]
// Equivalent to PAGESIZE. If either PAGESIZE or PAGE_SIZE is defined, the other is defined with the same value.
#define PAGE_SIZE PAGESIZE

// Maximum number of attempts made to destroy a thread's thread-specific data values on thread exit.
// Must be at least: _POSIX_THREAD_DESTRUCTOR_ITERATIONS
#define PTHREAD_DESTRUCTOR_ITERATIONS 1

// Maximum number of data keys that can be created by a process.
// Must be at least: _POSIX_THREAD_KEYS_MAX
#define PTHREAD_KEYS_MAX 1

// Minimum size in bytes of thread stack storage.
// Must be at least: 0
#define PTHREAD_STACK_MIN 4096

// Maximum number of threads that can be created per process.
// Must be at least: _POSIX_THREAD_THREADS_MAX
#define PTHREAD_THREADS_MAX 1024

// Maximum number of realtime signals reserved for application use in this implementation.
// Must be at least: _POSIX_RTSIG_MAX
#define RTSIG_MAX 1

// Maximum number of semaphores that a process may have.
// Must be at least: _POSIX_SEM_NSEMS_MAX
#define SEM_NSEMS_MAX 1

// The maximum value a semaphore may have.
// Must be at least: _POSIX_SEM_VALUE_MAX
#define SEM_VALUE_MAX 1

// Maximum number of queued signals that a process may send and have pending at the receiver(s) at any time.
// Must be at least: _POSIX_SIGQUEUE_MAX
#define SIGQUEUE_MAX 1

// [SS|TSP]
// The maximum number of replenishment operations that may be simultaneously pending for a particular sporadic server scheduler.
// Must be at least: _POSIX_SS_REPL_MAX
#define SS_REPL_MAX 1

// Maximum number of streams that one process can have open at one time. If defined, it has the same value as FOPEN_MAX (see <stdio.h>).
// Must be at least: _POSIX_STREAM_MAX
#define STREAM_MAX 1

// Maximum number of symbolic links that can be reliably traversed in the resolution of a pathname in the absence of a loop.
// Must be at least: _POSIX_SYMLOOP_MAX
#define SYMLOOP_MAX 1

// Maximum number of timers per process supported by the implementation.
// Must be at least: _POSIX_TIMER_MAX
#define TIMER_MAX 1

// [OB TRC]
// Maximum length of the trace event name (not including the terminating null).
// Must be at least: _POSIX_TRACE_EVENT_NAME_MAX
#define TRACE_EVENT_NAME_MAX 1

// [OB TRC]
// Maximum length of the trace generation version string or of the trace stream name (not including the terminating null).
// Must be at least: _POSIX_TRACE_NAME_MAX
#define TRACE_NAME_MAX 1

// [OB TRC]
// Maximum number of trace streams that may simultaneously exist in the system.
// Must be at least: _POSIX_TRACE_SYS_MAX
#define TRACE_SYS_MAX 1

// [OB TRC]
// Maximum number of user trace event type identifiers that may simultaneously exist in a traced process, including the predefined user trace event POSIX_TRACE_UNNAMED_USER_EVENT.
// Must be at least: _POSIX_TRACE_USER_EVENT_MAX
#define TRACE_USER_EVENT_MAX 1

// Maximum length of terminal device name.
// Must be at least: _POSIX_TTY_NAME_MAX
#define TTY_NAME_MAX 1

// Maximum number of bytes supported for the name of a timezone (not of the TZ variable).
// Must be at least: _POSIX_TZNAME_MAX
#define TZNAME_MAX 1

// ----------
// Pathname Variable Values
//
// The values in the following list may be constants within an implementation
// or may vary from one pathname to another. For example, file systems or
// directories may have different characteristics.
//
// A definition of one of the symbolic constants in the following list shall
// be omitted from the <limits.h> header on specific implementations where
// the corresponding value is equal to or greater than the stated minimum, but
// where the value can vary depending on the file to which it is applied. The
// actual value supported for a specific pathname shall be provided by the
// pathconf() function.
//
// Again, I specify everything.

// Minimum number of bits needed to represent, as a signed integer value, the maximum size of a regular file allowed in the specified directory.
// Must be at least: 32
#define FILESIZEBITS 64

// Maximum number of links to a single file.
// Must be at least: _POSIX_LINK_MAX
#define LINK_MAX 8

// Maximum number of bytes in a terminal canonical input line.
// Must be at least: _POSIX_MAX_CANON
#define MAX_CANON (32*1024)

// Minimum number of bytes for which space is available in a terminal input queue; therefore, the maximum number of bytes a conforming application may require to be typed as input before reading them.
// Must be at least: _POSIX_MAX_INPUT
#define MAX_INPUT (32*1024)

// Maximum number of bytes in a filename (not including the terminating null of a filename string).
// Must be at least: _POSIX_NAME_MAX
// [XSI] Must be at least: _XOPEN_NAME_MAX}
#define NAME_MAX 256

// Maximum number of bytes the implementation will store as a pathname in a user-supplied buffer of unspecified size, including the terminating null character. Minimum number the implementation will accept as the maximum number of bytes in a pathname.
// Must be at least: _POSIX_PATH_MAX
// [XSI] Must be at least: _XOPEN_PATH_MAX
#define PATH_MAX 1024

// Maximum number of bytes that is guaranteed to be atomic when writing to a pipe.
// Must be at least: _POSIX_PIPE_BUF
#define PIPE_BUF 1024

// [ADV]
// Minimum number of bytes of storage actually allocated for any portion of a file.
// Must be at least: Not specified.
#define POSIX_ALLOC_SIZE_MIN 4096

// [ADV]
// Recommended increment for file transfer sizes between the POSIX_REC_MIN_XFER_SIZE and POSIX_REC_MAX_XFER_SIZE values.
// Must be at least: Not specified.
#define POSIX_REC_INCR_XFER_SIZE 4096

// [ADV]
// Maximum recommended file transfer size.
// Must be at least: Not specified.
#define POSIX_REC_MAX_XFER_SIZE (256*1024)

// [ADV]
// Minimum recommended file transfer size.
// Must be at least: Not specified.
#define POSIX_REC_MIN_XFER_SIZE 1024

// [ADV]
// Recommended file transfer buffer alignment.
// Must be at least: Not specified.
#define POSIX_REC_XFER_ALIGN 1024

// Maximum number of bytes in a symbolic link.
// Must be at least: _POSIX_SYMLINK_MAX
#define SYMLINK_MAX 4096

// ----------
// Runtime Increasable Values
//
// The magnitude limitations in the following list shall be fixed by specific
// implementations. An application should assume that the value of the
// symbolic constant defined by <limits.h> in a specific implementation
// is the minimum that pertains whenever the application is run under that
// implementation. A specific instance of a specific implementation may
// increase the value relative to that supplied by <limits.h> for that
// implementation. The actual value supported by a specific instance shall be
// provided by the sysconf() function.

// Maximum obase values allowed by the bc utility.
// Must be at least: _POSIX2_BC_BASE_MAX
#define BC_BASE_MAX 1

// Maximum number of elements permitted in an array by the bc utility.
// Must be at least: _POSIX2_BC_DIM_MAX
#define BC_DIM_MAX 1

// Maximum scale value allowed by the bc utility.
// Must be at least: _POSIX2_BC_SCALE_MAX
#define BC_SCALE_MAX 1

// Maximum length of a string constant accepted by the bc utility.
// Must be at least: _POSIX2_BC_STRING_MAX
#define BC_STRING_MAX 1

// Maximum number of bytes in a character class name.
// Must be at least: _POSIX2_CHARCLASS_NAME_MAX
#define CHARCLASS_NAME_MAX 1

// Maximum number of weights that can be assigned to an entry of the LC_COLLATE order keyword in the locale definition file; see Locale.
// Must be at least: _POSIX2_COLL_WEIGHTS_MAX
#define COLL_WEIGHTS_MAX 1

// Maximum number of expressions that can be nested within parentheses by the expr utility.
// Must be at least: _POSIX2_EXPR_NEST_MAX
#define EXPR_NEST_MAX 1

// Unless otherwise noted, the maximum length, in bytes, of a utility's input
// line (either standard input or another file), when the utility is described
// as processing text files. The length includes room for the trailing <newline>.
// Must be at least: _POSIX2_LINE_MAX
#define LINE_MAX 1

// Maximum number of simultaneous supplementary group IDs per process.
// Must be at least: _POSIX_NGROUPS_MAX
#define NGROUPS_MAX 1

// Maximum number of repeated occurrences of a BRE or ERE interval expression;
// see BREs Matching Multiple Characters and EREs Matching Multiple Characters.
// Must be at least: _POSIX_RE_DUP_MAX
#define RE_DUP_MAX 1

// ----------
// Maximum Values
//
// The <limits.h> header shall define the following symbolic constants with
// the values shown. These are the most restrictive values for certain
// features on an implementation. A conforming implementation shall provide
// values no larger than these values. A conforming application must not
// require a smaller value for correct operation.

// The resolution of the CLOCK_REALTIME clock, in nanoseconds.
// Value: 20 000 000
// [MON] If the Monotonic Clock option is supported, the resolution of the
// CLOCK_MONOTONIC clock, in nanoseconds, is represented by _POSIX_CLOCKRES_MIN.
#define _POSIX_CLOCKRES_MIN 1000

// ----------
// Minimum Values
//
// The <limits.h> header shall define the following symbolic constants with
// the values shown. These are the most restrictive values for certain
// features on an implementation conforming to this volume of POSIX.1-2017.
// Related symbolic constants are defined elsewhere in this volume of
// POSIX.1-2017 which reflect the actual implementation and which need not
// be as restrictive. For each of these limits, a conforming implementation
// shall provide a value at least this large or shall have no limit. A
// strictly conforming application must not require a larger value for
// correct operation.

// The number of I/O operations that can be specified in a list I/O call.
// Value: 2
#define _POSIX_AIO_LISTIO_MAX 2

// The number of outstanding asynchronous I/O operations.
// Value: 1
#define _POSIX_AIO_MAX 1

// Maximum length of argument to the exec functions including environment data.
// Value: 4 096
#define _POSIX_ARG_MAX 4096

// Maximum number of simultaneous processes per real user ID.
// Value: 25
#define _POSIX_CHILD_MAX 25

// The number of timer expiration overruns.
// Value: 32
#define _POSIX_DELAYTIMER_MAX 32

// Maximum length of a host name (not including the terminating null) as returned from the gethostname() function.
// Value: 255
#define _POSIX_HOST_NAME_MAX 255

// Maximum number of links to a single file.
// Value: 8
#define _POSIX_LINK_MAX 8

// The size of the storage required for a login name, in bytes (including the terminating null).
// Value: 9
#define _POSIX_LOGIN_NAME_MAX 9

// Maximum number of bytes in a terminal canonical input queue.
// Value: 255
#define _POSIX_MAX_CANON 255

// Maximum number of bytes allowed in a terminal input queue.
// Value: 255
#define _POSIX_MAX_INPUT 255

// [MSG]
// The number of message queues that can be open for a single process.
// Value: 8
#define _POSIX_MQ_OPEN_MAX 8

// [MSG]
// The maximum number of message priorities supported by the implementation.
// Value: 32
#define _POSIX_MQ_PRIO_MAX 32

// Maximum number of bytes in a filename (not including the terminating null of a filename string).
// Value: 14
#define _POSIX_NAME_MAX 14

// Maximum number of simultaneous supplementary group IDs per process.
// Value: 8
#define _POSIX_NGROUPS_MAX 8

// A value one greater than the maximum value that the system may assign to a newly-created file descriptor.
// Value: 20
#define _POSIX_OPEN_MAX 20

// Minimum number the implementation will accept as the maximum number of bytes in a pathname.
// Value: 256
#define _POSIX_PATH_MAX 256

// Maximum number of bytes that is guaranteed to be atomic when writing to a pipe.
// Value: 512
#define _POSIX_PIPE_BUF 512

// Maximum number of repeated occurrences of a BRE or ERE interval expression; see BREs Matching Multiple Characters and EREs Matching Multiple Characters.
// Value: 255
#define _POSIX_RE_DUP_MAX 255

// The number of realtime signal numbers reserved for application use.
// Value: 8
#define _POSIX_RTSIG_MAX 8

// The number of semaphores that a process may have.
// Value: 256
#define _POSIX_SEM_NSEMS_MAX 256

// The maximum value a semaphore may have.
// Value: 32 767
#define _POSIX_SEM_VALUE_MAX 32767

// The number of queued signals that a process may send and have pending at the receiver(s) at any time.
// Value: 32
#define _POSIX_SIGQUEUE_MAX 32

// The value that can be stored in an object of type ssize_t.
// Value: 32 767
#define _POSIX_SSIZE_MAX LLONG_MAX

// [SS|TSP]
// The number of replenishment operations that may be simultaneously pending for a particular sporadic server scheduler.
// Value: 4
#define _POSIX_SS_REPL_MAX 4

// The number of streams that one process can have open at one time.
// Value: 8
#define _POSIX_STREAM_MAX 8

// The number of bytes in a symbolic link.
// Value: 255
#define _POSIX_SYMLINK_MAX 255

// The number of symbolic links that can be traversed in the resolution of a pathname in the absence of a loop.
// Value: 8
#define _POSIX_SYMLOOP_MAX 8

// The number of attempts made to destroy a thread's thread-specific data values on thread exit.
// Value: 4
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS 4

// The number of data keys per process.
// Value: 128
#define _POSIX_THREAD_KEYS_MAX 128

// The number of threads per process.
// Value: 64
#define _POSIX_THREAD_THREADS_MAX 64

// The per-process number of timers.
// Value: 32
#define _POSIX_TIMER_MAX 32

// [OB TRC]
// The length in bytes of a trace event name (not including the terminating null).
// Value: 30
#define _POSIX_TRACE_EVENT_NAME_MAX 30

// [OB TRC]
// The length in bytes of a trace generation version string or a trace stream name (not including the terminating null).
// Value: 8
#define _POSIX_TRACE_NAME_MAX 8

// [OB TRC]
// The number of trace streams that may simultaneously exist in the system.
// Value: 8
#define _POSIX_TRACE_SYS_MAX

// [OB TRC]
// The number of user trace event type identifiers that may simultaneously exist in a traced process, including the predefined user trace event POSIX_TRACE_UNNAMED_USER_EVENT.
// Value: 32
#define _POSIX_TRACE_USER_EVENT_MAX 32

// The size of the storage required for a terminal device name, in bytes (including the terminating null).
// Value: 9
#define _POSIX_TTY_NAME_MAX 9

// Maximum number of bytes supported for the name of a timezone (not of the TZ variable).
// Value: 6
// Note: The length given by _POSIX_TZNAME_MAX does not include the quoting characters mentioned in Other Environment Variables.
#define _POSIX_TZNAME_MAX 6

// Maximum obase values allowed by the bc utility.
// Value: 99
#define _POSIX2_BC_BASE_MAX 99

// Maximum number of elements permitted in an array by the bc utility.
// Value: 2 048
#define _POSIX2_BC_DIM_MAX 2048

// Maximum scale value allowed by the bc utility.
// Value: 99
#define _POSIX2_BC_SCALE_MAX 99

// Maximum length of a string constant accepted by the bc utility.
// Value: 1 000
#define _POSIX2_BC_STRING_MAX 1000

// Maximum number of bytes in a character class name.
// Value: 14
#define _POSIX2_CHARCLASS_NAME_MAX 14

// Maximum number of weights that can be assigned to an entry of the LC_COLLATE order keyword in the locale definition file; see Locale.
// Value: 2
#define _POSIX2_COLL_WEIGHTS_MAX 2

// Maximum number of expressions that can be nested within parentheses by the expr utility.
// Value: 32
#define _POSIX2_EXPR_NEST_MAX 32

// Unless otherwise noted, the maximum length, in bytes, of a utility's input line (either standard input or another file), when the utility is described as processing text files. The length includes room for the trailing <newline>.
// Value: 2 048
#define _POSIX2_LINE_MAX 2048

// Maximum number of repeated occurrences of a BRE or ERE interval expression; see BREs Matching Multiple Characters and EREs Matching Multiple Characters.
// Value: 255
#define _POSIX2_RE_DUP_MAX 255

// [XSI]
// Maximum number of iovec structures that one process has available for use with readv() or writev().
// Value: 16
#define _XOPEN_IOV_MAX 16

// [XSI]
// Maximum number of bytes in a filename (not including the terminating null of a filename string).
// Value: 255
#define _XOPEN_NAME_MAX 255

// [XSI]
// Minimum number the implementation will accept as the maximum number of bytes in a pathname.
// Value: 1024
#define _XOPEN_PATH_MAX 1024

// ----------
// Numerical Limits (overlaps with ISO C standard)
//
// The <limits.h> header shall define the following macros and, except for
// CHAR_BIT, LONG_BIT, MB_LEN_MAX, and WORD_BIT, they shall be replaced by
// expressions that have the same type as would an expression that is an
// object of the corresponding type converted according to the integer promotions.
//
// If the value of an object of type char is treated as a signed integer when
// used in an expression, the value of CHAR_MIN is the same as that of SCHAR_MIN
// and the value of CHAR_MAX is the same as that of SCHAR_MAX. Otherwise, the
// value of CHAR_MIN is 0 and the value of CHAR_MAX is the same as that of UCHAR_MAX.

// [CX]
// Number of bits in an object of type long.
// Must be at least: 32
#define LONG_BIT 32

// [CX]
// Maximum value for an object of type ssize_t.
// Minimum Acceptable Value: _POSIX_SSIZE_MAX
#define SSIZE_MAX // -(2^63 - 1)

// [CX]
// Number of bits in an object of type int.
// Minimum Acceptable Value: 32
#define WORD_BIT 32

// ----------
// Other Invariant Values

// Maximum value of n in conversion specifications using the "%n$" sequence
// in calls to the printf() and scanf() families of functions.
// Must be at least: 9
#define NL_ARGMAX 9

// [XSI]
// Maximum number of bytes in a LANG name.
// Must be at least: 14
#define NL_LANGMAX 14

// Maximum message number.
// Must be at least: 32 767
#define NL_MSGMAX 32767

// Maximum set number.
// Must be at least: 255
#define NL_SETMAX 255

// Maximum number of bytes in a message string.
// Must be at least: _POSIX2_LINE_MAX
#define NL_TEXTMAX 256

// [XSI]
// Default process priority.
// Minimum Acceptable Value: 20
#define NZERO 20

// ----------
// Legacy (removed)

// The LEGACY symbols {PASS_MAX} and {TMP_MAX} are removed.
// NL_NMAX is removed.

[FOOTER]
[/GUARD]
