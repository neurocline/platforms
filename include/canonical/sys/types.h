// <sys/types.h>
// - data types
//
// Defined in POSIX.1-2017 <sys/types.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_types.h.html

#pragma once
#ifndef CANONICAL_POSIX_2017_SYS_TYPES_H
#define CANONICAL_POSIX_2017_SYS_TYPES_H

// ---------------------------------------------------------------------------
// Canonical header

// ----------------------------
// POSIX

// Used for file block counts.
// blkcnt_t and off_t shall be signed integer types.
typedef int blkcnt_t;

// Used for block sizes. Must be signed integer.
// blksize_t, pid_t, and ssize_t shall be signed integer types.
typedef int     blksize_t;

// Used for system times in clock ticks or CLOCKS_PER_SEC; see <time.h>.
// clock_t shall be an integer or real-floating type
typedef int     clock_t;

// Used for clock ID type in the clock and timer functions.
typedef int     clockid_t;

// Used for device IDs.
// dev_t shall be an integer type.
typedef unsigned int     dev_t;

// Used for file system block counts.
// fsblkcnt_t, fsfilcnt_t, and ino_t shall be defined as unsigned integer types.
typedef int     fsblkcnt_t;

// Used for file system file counts.
// fsblkcnt_t, fsfilcnt_t, and ino_t shall be defined as unsigned integer types.
typedef int     fsfilcnt_t;

// Used for group IDs.
// nlink_t, uid_t, gid_t, and id_t shall be integer types.
typedef unsigned int     gid_t;

 // Used as a general identifier; can be used to contain at least a pid_t, uid_t, or gid_t.
// nlink_t, uid_t, gid_t, and id_t shall be integer types.
typedef unsigned int     id_t;

// Used for file serial numbers.
// fsblkcnt_t, fsfilcnt_t, and ino_t shall be defined as unsigned integer types.
typedef int     ino_t;

// Used for XSI interprocess communication.
typedef int     key_t;

// Used for some file attributes.
// mode_t shall be an integer type
typedef unsigned int     mode_t;

// Used for link counts.
// nlink_t, uid_t, gid_t, and id_t shall be integer types.
typedef int     nlink_t;

// Used for file sizes.
// blkcnt_t and off_t shall be signed integer types.
typedef long long off_t;

 // Used for process IDs and process group IDs. Must be signed integer.
// blksize_t, pid_t, and ssize_t shall be signed integer types.
typedef int     pid_t;

// Used for time in microseconds. Must be signed integer.
// The type suseconds_t shall be a signed integer type capable of storing values at least in the range [-1, 1000000].
typedef int     suseconds_t;

// Used for sizes of objects. Must be unsigned integer. Same size as ssize.t.
// size_t shall be an unsigned integer type.
#ifdef _WIN64
typedef unsigned long long  size_t;
#else
typedef unsigned int       size_t;
#endif

// Used for a count of bytes or an error indication. Must be signed integer.
// blksize_t, pid_t, and ssize_t shall be signed integer types.
// The type ssize_t shall be capable of storing values at least in the range [-1, {SSIZE_MAX}].
#ifdef _WIN64
typedef long long           ssize_t;
#else
typedef int                ssize_t;
#endif

// Make time_t be the largest natural size.
// This is used for time in seconds.
// time_t shall be an integer type.
#ifdef _WIN64
typedef long long time_t;
#else
typedef int time_t;
#endif

// nlink_t, uid_t, gid_t, and id_t shall be integer types.
typedef unsigned int     uid_t;          // Used for user IDs.

// All of the types shall be defined as arithmetic types of an appropriate length, with the following exceptions:
typedef struct { int v; } pthread_attr_t;    // Used to identify a thread attribute object.
typedef struct { int v; } pthread_barrier_t;    // Used to identify a barrier.
typedef struct { int v; } pthread_barrierattr_t;    // Used to define a barrier attributes object.
typedef struct { int v; } pthread_cond_t;    // Used for condition variables.
typedef struct { int v; } pthread_condattr_t;    // Used to identify a condition attribute object.
typedef struct { int v; } pthread_key_t;    // Used for thread-specific data keys.
typedef struct { int v; } pthread_mutex_t;    // Used for mutexes.
typedef struct { int v; } pthread_mutexattr_t;    // Used to identify a mutex attribute object.
typedef struct { int v; } pthread_once_t;    // Used for dynamic package initialization.
typedef struct { int v; } pthread_rwlock_t;    // Used for read-write locks.
typedef struct { int v; } pthread_rwlockattr_t;    // Used for read-write lock attributes.
typedef struct { int v; } pthread_spinlock_t;    // Used to identify a spin lock.
typedef struct { int v; } pthread_t;    // Used to identify a thread.
#ifndef _HEADER_SYS_TYPES_DEFINED_TIMER_T
#define _HEADER_SYS_TYPES_DEFINED_TIMER_T
typedef struct { int v; } timer_t;    // Used for timer ID returned by timer_create().
#endif
typedef struct { int v; } trace_attr_t;    // [OB TRC] Used to identify a trace stream attributes object.
typedef struct { int v; } trace_event_id_t;    // [OB TRC] Used to identify a trace event type.
typedef struct { int v; } trace_event_set_t;    // [OB TEF] Used to identify a trace event type set.
typedef struct { int v; } trace_id_t;    // [OB TRC] Used to identify a trace stream.

// -----------------------------------------------------------------------------------------------

#endif // CANONICAL_POSIX_2017_SYS_TYPES_H
