// <sys/stat.h>
//
// POSIX.1-2008.7 sys/stat.h header file
// data returned by the stat() function
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_stat.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__SYS_STAT_H
#define _POSIX_ON_WIN32__SYS_STAT_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// Do we want to use the Windows sys/stat.h or not?
#ifndef _POSIX_ON_WIN32_NO_WIN32_SYS_STAT
#define _POSIX_ON_WIN32_USE_WIN32_SYS_STAT
#endif

// -----------------------------------------------------------------------------------------------

// If we are piggybacking on top of the Windows <sys/stat.h>, just
// define what's missing. We have to include it first.
#if defined(_POSIX_ON_WIN32_USE_WIN32_SYS_STAT)

// When we include the Windows <sys/stat.h>, do not let it
// introduce the standard types stat etc into the system. Their
// code doesn't use these, and their definitions clash with ours.
#pragma push_macro("__STDC__")
#pragma push_macro("_CRT_NO_TIME_T")
#undef __STDC__
#define __STDC__ 1
#undef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#include _MICROSOFT_UCRT_INCLUDE_NEXT(sys/stat.h)
#pragma pop_macro("__STDC__")
#pragma pop_macro("_CRT_NO_TIME_T")

// The <sys/stat.h> header shall define the [XSI] [Option Start] blkcnt_t, blksize_t, [Option End]
// dev_t, ino_t, mode_t, nlink_t, uid_t, gid_t, off_t, and time_t types as described in <sys/types.h>.

typedef int blkcnt_t; // Used for file block counts.
typedef int blksize_t; // Used for block sizes. Must be signed integer.
typedef unsigned int dev_t; // Used for device IDs.
typedef unsigned int gid_t; // Used for group IDs.
typedef int ino_t; // Used for file serial numbers.
typedef unsigned int mode_t; // Used for some file attributes.
typedef int nlink_t; // Used for link counts.
typedef long long off_t; // Used for file sizes.
typedef unsigned int uid_t; // Used for user IDs.

// Make time_t be the largest natural size.
// This is used for time in seconds.
#ifdef _WIN64
typedef long long time_t;
#else
typedef int time_t;
#endif

// The <sys/stat.h> header shall define the timespec structure as described in <time.h>.
// Times shall be given in seconds since the Epoch.

#ifndef POSIX_ON_WIN32_SYS_STAT_HAS_TIMESPEC
#define POSIX_ON_WIN32_SYS_STAT_HAS_TIMESPEC
struct timespec {
    time_t tv_sec;       /* seconds */
    long tv_nsec;        /* nanoseconds */
};
#endif

struct stat {
    dev_t st_dev;
    ino_t st_ino;
    mode_t st_mode;
    nlink_t st_nlink;
    uid_t st_uid;
    gid_t st_gid;
    dev_t st_rdev;
    off_t st_size;
    struct timespec st_atime;
    struct timespec st_mtime;
    struct timespec st_ctime;
    blksize_t st_blksize;
    blkcnt_t st_blocks;
};

// File types encoded in mode_t
#define S_IFMT      0170000 // File type mask

#define S_IFBLK     (1 << 12)   // Block special
#define S_IFCHR     (2 << 12)   // Character special
#define S_IFIFO     (3 << 12)   // FIFO special
#define S_IFREG     (4 << 12)   // Regular
#define S_IFDIR     (5 << 12)   // Directory
#define S_IFLNK     (6 << 12)   // Symbolic link
#define S_IFSOCK    (7 << 12)   // Socket

#define S_ISBLK(mode) (((mode) & S_IFBLK) == S_IFBLK) // Test for a block special file
#define S_ISCHR(mode) (((mode) & S_IFCHR) == S_IFCHR) // Test for a character special file
#define S_ISDIR(mode) (((mode) & S_IFDIR) == S_IFDIR) // Test for a directory
#define S_ISFIFO(mode) (((mode) & S_IFIFO) == S_IFIFO) // Test for a pipe or FIFO special file
#define S_ISREG(mode) (((mode) & S_IFREG) == S_IFREG) // Test for a regular file
#define S_ISLNK(mode) (((mode) & S_IFLNK) == S_IFLNK) // Test for a symbolic link
#define S_ISSOCK(mode) (((mode) & S_IFSOCK) == S_IFSOCK) // Test for a socket

#define S_IRWXU 0700 // Read, write, execute/search by owner
#define S_IRUSR 0400 // Read permission, owner
#define S_IWUSR 0200 // Write permission, owner
#define S_IXUSR 0100 // Execute/search permission, owner

#define S_IRWXG 0070 // Read, write, execute/search by group
#define S_IRGRP 0040 // Read permission, group
#define S_IWGRP 0020 // Write permission, group
#define S_IXGRP 0010 // Execute/search permission, group

#define S_IRWXO 0007 // Read, write, execute/search by others
#define S_IROTH 0004 // Read permission, others
#define S_IWOTH 0002 // Write permission, others
#define S_IXOTH 0001 // Execute/search permission, others

// These are completely specious even above and beyond normal, because I have
// no idea how these would be used.
#define S_IFMQ  (8 << 12) // message queue
#define S_IFSEM (9 << 12) // semaphore
#define S_IFSHMEM (10 << 12) // shared memory object
#define S_IFTYPEMEM (11 << 12) // typed memory object
#define S_TYPEISMQ(buf) (((buf)->st_mode & S_IFMQ) == S_IFMQ) // Test for a message queue
#define S_TYPEISSEM(buf) (((buf)->st_mode & S_IFSEM) == S_IFSEM) // Test for a semaphore
#define S_TYPEISSHM(buf) (((buf)->st_mode & S_IFSHMEM) == S_IFSHMEM) // Test for a shared memory object
#define S_TYPEISTMO(buf) (((buf)->st_mode & S_IFTYPEMEM) == S_IFTYPEMEM) // Test macro for a typed memory object

int chmod(const char* path, mode_t mode);
int fchmodat(int fd, const char* path, mode_t mode, int flag);
int fchmod(int fildes, mode_t mode);
int fstat(int fildes, struct stat* buf);
int fstatat(int fd, const char* path, struct stat* buf, int flag);
int lstat(const char* path, struct stat* buf);
int stat(const char* path, struct stat* buf);
int futimens(int fd, const struct timespec times[2]);
int utimensat(int fd, const char* path, const struct timespec times[2], int flag);
int mkdir(const char* path, mode_t mode);
int mkdirat(int fd, const char *path, mode_t mode);
int mkfifo(const char* path, mode_t mode);
int mkfifoat(int fd, const char *path, mode_t mode);
int mknod(const char* path, mode_t mode, dev_t dev);
int mknodat(int fd, const char* path, mode_t mode, dev_t dev);
mode_t umask(mode_t cmask);

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_SYS_STAT)

// -----------------------------------------------------------------------------------------------

// Otherwise, we have to declare a complete <sys/stat.h> environment
#if !defined(_POSIX_ON_WIN32_USE_WIN32_SYS_STAT)

#error "This path not supported"

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_SYS_STAT)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__SYS_STAT_H
