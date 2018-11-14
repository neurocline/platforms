// <sys/stat.h>
// - data returned by the stat() function
//
// Defined in POSIX.1-2017 <sys/stat.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_stat.h.html

#pragma once
#ifndef DIAGNOSTIC_POSIX_2017_SYS_STAT_H
#define DIAGNOSTIC_POSIX_2017_SYS_STAT_H

#include <internal/carp.h>

// ---------------------------------------------------------------------------
// Diagnostic header

// ----------------------------
// POSIX

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

#ifndef _HEADER_SYS_STAT_DEFINED_TIMESPEC
#define _HEADER_SYS_STAT_DEFINED_TIMESPEC
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
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
#define st_atime st_atim.tv_sec // Backward compatibility.
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
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

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

CARP("POSIX 2017.1: chmod()") int chmod(const char* path, mode_t mode);
CARP("POSIX 2017.1: fchmodat()") int fchmodat(int fd, const char* path, mode_t mode, int flag);
CARP("POSIX 2017.1: fchmod()") int fchmod(int fildes, mode_t mode);
CARP("POSIX 2017.1: fstat()") int fstat(int fildes, struct stat* buf);
CARP("POSIX 2017.1: fstatat()") int fstatat(int fd, const char* path, struct stat* buf, int flag);
CARP("POSIX 2017.1: lstat()") int lstat(const char* path, struct stat* buf);
CARP("POSIX 2017.1: stat()") int stat(const char* path, struct stat* buf);
CARP("POSIX 2017.1: futimens()") int futimens(int fd, const struct timespec times[2]);
CARP("POSIX 2017.1: utimensat()") int utimensat(int fd, const char* path, const struct timespec times[2], int flag);
CARP("POSIX 2017.1: mkdir()") int mkdir(const char* path, mode_t mode);
CARP("POSIX 2017.1: mkdirat()") int mkdirat(int fd, const char *path, mode_t mode);
CARP("POSIX 2017.1: mkfifo()") int mkfifo(const char* path, mode_t mode);
CARP("POSIX 2017.1: mkfifoat()") int mkfifoat(int fd, const char *path, mode_t mode);
CARP("POSIX 2017.1: mknod()") int mknod(const char* path, mode_t mode, dev_t dev);
CARP("POSIX 2017.1: mknodat()") int mknodat(int fd, const char* path, mode_t mode, dev_t dev);
CARP("POSIX 2017.1: umask()") mode_t umask(mode_t cmask);

#ifdef  __cplusplus
}
#endif

// -----------------------------------------------------------------------------------------------

#endif // DIAGNOSTIC_POSIX_2017_SYS_STAT_H
