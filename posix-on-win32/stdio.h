// stdio.h
//
// POSIX.1-2008.7 stdio.h header file
// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdio.h.html

#pragma once
#ifndef _POSIX_ON_WIN32__STDIO_H
#define _POSIX_ON_WIN32__STDIO_H

// Get emulation of #include_next
#include <posix_win32_include_next.h>

// Do we want to use the Windows errno.h or not?
#ifndef _POSIX_ON_WIN32_NO_WIN32_STDIO
#define _POSIX_ON_WIN32_USE_WIN32_STDIO
#endif

// -----------------------------------------------------------------------------------------------

// If we are piggybacking on top of the Windows <stdio.h>, just
// define what's missing. We have to include it first.
#if defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)

#include _MICROSOFT_UCRT_INCLUDE_NEXT(stdio.h)

#ifdef _WIN64
typedef unsigned long long off_t;
typedef long long ssize_t;
#else
typedef unsigned int off_t;
typedef int ssize_t;
#endif

typedef char* va_list;

#define L_ctermid 16

// The default temp directory is in the env var %TEMP%
// old: C:/Temp, then %WinDir%/Temp
// Windows XP: %USERPROFILE%/Local Settings/Temp
// Windows Vista and up: %USERPROFILE%/AppData/Local/Temp
#define P_tmpdir "%TEMP%"

char *ctermid(char *s);
int dprintf(int fildes, const char * format, ...);

void flockfile(FILE *file);
int ftrylockfile(FILE *file);
void funlockfile(FILE *file);

FILE *fmemopen(void * buf, size_t size, const char * mode);
int fseeko(FILE *stream, off_t offset, int whence);
off_t ftello(FILE *stream);

int getc_unlocked(FILE *stream);
int getchar_unlocked(void);
int putc_unlocked(int c, FILE *stream);
int putchar_unlocked(int c);

ssize_t getdelim(char ** lineptr, size_t * n,
       int delimiter, FILE * stream);
ssize_t getline(char ** lineptr, size_t * n,
       FILE * stream);

FILE *open_memstream(char **bufp, size_t *sizep);

FILE *popen(const char *command, const char *mode);
int pclose(FILE *stream);

int renameat(int oldfd, const char *old, int newfd, const char *new);

int vdprintf(int fildes, const char * format, va_list ap);

#endif // defined(_POSIX_ON_WIN32_USE_WIN32_ERRNO)

// -----------------------------------------------------------------------------------------------

// Otherwise, we have to declare a complete stdio.h environment
#if !defined(_POSIX_ON_WIN32_USE_WIN32_STDIO)


#endif // _POSIX_ON_WIN32_USE_WIN32_STDIO

// -----------------------------------------------------------------------------------------------

#endif // _POSIX_ON_WIN32__STDIO_H
