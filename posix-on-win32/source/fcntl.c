// fcntl.c

#define __STDC__ 1

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <io.h> // for _open, _close

// The single biggest thing we should do is assume that the application
// uses UTF-8, and translate to/from UTF16LE for Windows. For now,
// we just expect ANSI strings.

// TBD handle the things Microsoft doesn't
int _posix_on_win32_vaopen(const char *path, int oflag, va_list args)
{
    // If we have O_CREAT or O_TMPFILE, then we have the
    // three-argument version, so get mode. Otherwise, it
    // defaults to 0, and we won't pass a 0.
    mode_t mode = 0;
    if ((oflag & (O_CREAT|O_TMPFILE)) != 0)
        mode = va_arg(args, mode_t);
    va_end(args);

    // The Win32 CRT _open can handle these flags and mode
    int win32_oflag = 0;
    int win32_mode = mode;

    #define MAP_OFLAG(f) if (oflag & f) win32_oflag |= _ ## f
    MAP_OFLAG(O_APPEND);
    MAP_OFLAG(O_CREAT);
    MAP_OFLAG(O_EXCL);
    MAP_OFLAG(O_TRUNC);

    // O_RDONLY is the absence of O_WRONLY and O_RDWR
    MAP_OFLAG(O_WRONLY);
    MAP_OFLAG(O_RDWR);

    // These are Microsoft extensions, so free for us for now
    MAP_OFLAG(O_TEXT);
    MAP_OFLAG(O_WTEXT);
    MAP_OFLAG(O_U16TEXT);
    MAP_OFLAG(O_U8TEXT);
    MAP_OFLAG(O_BINARY);
    MAP_OFLAG(O_RAW);
    MAP_OFLAG(O_RANDOM);
    MAP_OFLAG(O_SEQUENTIAL);
    MAP_OFLAG(O_TEMPORARY);
    MAP_OFLAG(O_SHORT_LIVED);

    // O_TMPFILE (from Linux) does not have the same semantics as _O_TEMPORARY
    // or _O_SHORT_LIVED on Windows. For now, ignore this, but this will make
    // security people angry.
    if (oflag & O_TMPFILE)
        win32_oflag |= (_O_TEMPORARY|_O_SHORT_LIVED);

    // We can ignore O_NOCTTY, there are no terminal devices on Windows
    // We ignore O_NONBLOCK for now.

    // Not handled yet and we really need to
    if (oflag & (O_CLOEXEC|O_NOFOLLOW))
    {
        errno = EINVAL;
        return -1;
    }

    // No execution semantics on Windows - what should we do?
    // This is probably not used very often?
    if (oflag & O_EXEC)
    {
        errno = EINVAL;
        return -1;
    }

    // Opening a directory is legal in POSIX - TBD, synthesize this
    // if we find people are doing it.
    if (oflag & (O_SEARCH|O_DIRECTORY))
    {
        errno = EINVAL;
        return -1;
    }

    // And these probably make no sense, but not sure what to do.
    if (oflag & O_TTY_INIT)
    {
        errno = EINVAL;
        return -1;
    }

    // And finally, we can open - hopefully.
    int fd = (win32_mode != 0)
             ? _open(path, win32_oflag, win32_mode)
             : _open(path, win32_oflag);

    return fd;
}
