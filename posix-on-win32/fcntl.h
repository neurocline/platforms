// <fcntl.h>
// - file control options
//
// Defined in POSIX.1-2017 <fcntl.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/fcntl.h.html

#pragma once
#ifndef _POSIX_ON_WIN32_POSIX_FCNTL_H
#define _POSIX_ON_WIN32_POSIX_FCNTL_H

// Default to not using the Windows fcntl.h file
#ifndef _POSIX_ON_WIN32_NO_WIN32_FCNTL
// #define _POSIX_ON_WIN32_USE_WIN32_FCNTL
#endif

// -----------------------------------------------------------------------------------------------

#if defined(_POSIX_ON_WIN32_USE_WIN32_FCNTL)

#error "This path not supported"

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_FCNTL)

// -----------------------------------------------------------------------------------------------

#if !defined(_POSIX_ON_WIN32_USE_WIN32_FCNTL)

// Microsoft doesn't really have fcntl.h. The functions that are supposed to be
// in fcntl.h are in other, nonstandard, header files. Only two fcntl.h
// functions exist in Microsoft world: _creat and _open are in <io.h>.
// So we just don't use the Microsoft fcnt.h and we wrap everything else.

// ----------------------------
// POSIX

// values for cmd argument in fcntl(int cmd, int flags, ...)
#define F_DUPFD             1   // Duplicate file descriptor.
#define F_DUPFD_CLOEXEC     2   // Duplicate file descriptor with the close-on- exec flag FD_CLOEXEC set.
#define F_GETFD             3   // Get file descriptor flags.
#define F_SETFD             4   // Set file descriptor flags.
#define F_GETFL             5   // Get file status flags and file access modes.
#define F_SETFL             6   // Set file status flags.
#define F_GETLK             7   // Get record locking information.
#define F_SETLK             8   // Set record locking information.
#define F_SETLKW            9   // Set record locking information; wait if blocked.
#define F_GETOWN            10  // Get process or process group ID to receive SIGURG signals.
#define F_SETOWN            11  // Set process or process group ID to receive SIGURG signals.

// vales for flags argument in fcntl(int cmd, int flags, ...)
#define FD_CLOEXEC          1   // Close the file descriptor upon execution of an exec family function.

// values for l_whence argument as in stdio.h
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

// arguments for l_type in fcntl(int cmd, int flags, int l_type)
#define F_RDLCK             1   // Shared or read lock.
#define F_UNLCK             2   // Unlock.
#define F_WRLCK             3   // Exclusive or write lock.

// file access mode flags for open(), openat(), and fcntl()
#define O_RDONLY        0           // Open for reading only
#define O_WRONLY        (1 << 0)    // Open for writing only
#define O_RDWR          (1 << 1)    // Open for reading and writing
#define O_SEARCH        (1 << 2)    // Open directory for search only
#define O_EXEC          (1 << 3)

// mask for file access modes
#define O_ACCMODE  (O_WRONLY | O_RDWR)

// file status flags passed to open(), openat(), and fcntl()
#define O_APPEND        (1 << 4)    // Set append mode
#define O_DSYNC         (1 << 5)
#define O_NONBLOCK      (1 << 6)    // open as non-blocking file
#define O_RSYNC         (1 << 7)
#define O_SYNC          (1 << 8)

// file creation flags passed to open() and openat()
#define O_CLOEXEC       (1 << 9)
#define O_CREAT         (1 << 10)   // create if not already existing
#define O_DIRECTORY     (1 << 11)   // open the directory as a file
#define O_EXCL          (1 << 12)   // use with O_CREAT to open only if file doesn't yet exist
#define O_NOCTTY        0           // don't make terminal device controlling terminal
#define O_NOFOLLOW      (1 << 13)
#define O_TRUNC         (1 << 14)   // open and truncate to zero length
#define O_TTY_INIT      0

// Linux-only (not in POSIX standard)
#define O_TMPFILE       (1 << 15)   // create unnamed temporary file (deleted on close)
#define O_NOLINK        (1 << 16)   // open link instead of following it
#define O_IGNORE_CTTY   0           // don't recognize as controlling terminal
#define O_NOTRANS       (1 << 17)   // open raw non-translated file
#define O_SHLOCK        (1 << 18)   // open with shared lock
#define O_EXLOCK        (1 << 19)   // open with exclusive lock

// values for mode_t from <sys/stat.h>

// magic file descriptors used in *at() functions
#define AT_FDCWD            -2

// flag used by faccessat()
#define AT_EACCESS          1

// flags used by fstatat(), fchmodat(), fchownat(), and utimensat()
#define AT_SYMLINK_NOFOLLOW 1

// flags used by linkat()
#define AT_SYMLINK_FOLLOW   1

// flags used by unlinkat()
#define AT_REMOVEDIR        1

// symbolic constants for the advice argument used by posix_fadvise()
#define POSIX_FADV_DONTNEED 1   // The application expects that it will not access the specified data in the near future.
#define POSIX_FADV_NOREUSE  1   // The application expects to access the specified data once and then not reuse it thereafter.
#define POSIX_FADV_NORMAL   1   // The application has no advice to give on its behavior with respect to the specified data. It is the default characteristic if no advice is given for an open file.
#define POSIX_FADV_RANDOM   1   // The application expects to access the specified data in a random order.
#define POSIX_FADV_SEQUENTIAL   1   // The application expects to access the specified data sequentially from lower offsets to higher offsets.
#define POSIX_FADV_WILLNEED 1   // The application expects to access the specified data in the near future.

// --------------------------------------

typedef long long off_t; // as in sys/types.h
typedef int pid_t; // as in sys/types.h
typedef unsigned int mode_t; // as in sys/types.h

// flock structure describing a file lock
struct flock
{
    short l_type;       // Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK.
    short l_whence;     // Where l_start is relative to
    off_t l_start;      // Offset where the lock begins.
    off_t l_len;        // Size of the locked area; zero means all
    pid_t l_pid;        // Process holding the lock.
};

// --------------------------------------

// Create a file. This is identical in behavior to
// open(path, O_WRONLY|O_CREAT|O_TRUNC, mode);
static inline int creat(const char *path, mode_t mode);

// Do file-control operation. The parameter list is really just a third
// parameter which points to the appropriate control block for the command.
int fcntl(int fildes, int cmd, ...);

// Open a file and return a file descriptor. The parameter list is an
// optional third parameter mode_t mode, which is only needed for O_TMPFILE
// and O_CREAT.
static inline int open(const char *path, int oflag, ...);

// Open a file relative to the directory of the passed-in fd (only valid for
// relative paths).
int openat(int fd, const char *path, int oflag, ...);

int posix_fadvise(int fd, off_t offset, off_t len, int advice);
int posix_fallocate(int fd, off_t offset, off_t len);

// exec* are in <unistd.h>
// futimens is in <sys/stat.h>
// posix_madvise is in <sys/mman.h>

// To implement creat() and open(), we need to supply static inline functions
// so we don't conflict with Microsoft functions of the same name in system
// libraries
#include <stdarg.h>
int _posix_on_win32_creat(const char *path, mode_t mode);
int _posix_on_win32_vaopen(const char *path, int oflag, va_list args);

static inline int creat(const char *path, mode_t mode) {
    return _posix_on_win32_creat(path, mode);
}
static inline int open(const char *path, int oflag, ...) {
    va_list args;
    va_start(args, oflag);
    return _posix_on_win32_vaopen(path, oflag, args);
}

// ----------------------------
// Glibc

typedef long long off64_t; // as in sys/types.h

int posix_fadvise64(int fd, off64_t offset, off64_t len, int advice);
int posix_fallocate64(int fd, off64_t offset, off64_t len);

// ----------------------------
// Microsoft

// Windows-only (not in POSIX standard, or in Linux)
// In non-Windows systems, these would just be zeros
#define O_TEXT          (1 << 20)   // file mode is text (linefeed translation)
#define O_BINARY        O_NOTRANS   // file mode is binary, no translation
#define O_RAW           O_NOTRANS

#define O_WTEXT         (1 << 21)   // file mode is UTF16 (translated)
#define O_U16TEXT       (1 << 22)   // file mode is UTF16, no BOM
#define O_U8TEXT        (1 << 23)   // file mode is UTF8, no BOM

#define O_NOINHERIT     (1 << 24)
#define O_TEMPORARY     O_TMPFILE
#define O_SHORT_LIVED   (1 << 25)
#define O_OBTAIN_DIR    O_DIRECTORY
#define O_SEQUENTIAL    (1 << 26)
#define O_RANDOM        (1 << 27)

#endif // !defined(_POSIX_ON_WIN32_USE_WIN32_FCNTL)

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32_POSIX_FCNTL_H
