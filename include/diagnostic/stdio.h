// <stdio.h>
// - standard buffered input/output
//
// Defined in ISO C18 Standard: 7.21 Input/output <stdio.h>.
// Extended in POSIX.1-2017 <stdio.h>
// See http://pubs.opengroup.org/onlinepubs/9699919799.2018edition/basedefs/stdio.h.html

#pragma once
#ifndef DIAGNOSTIC_ISO_C18_STDIO_H
#define DIAGNOSTIC_ISO_C18_STDIO_H

#include <internal/carp.h>

// ---------------------------------------------------------------------------
// Diagnostic header

// If we don't have at least C11, then make new keywords vanish
// so older compilers still work (notably MSVC))
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define restrict
#define _Noreturn
#endif

// va_list as in stdarg.h
typedef char* va_list;

// size_t as in stddef.h
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif

// as in sys/types.h
typedef long long off_t;

// An object type capable of recording all the information needed to control a stream
typedef struct _FILE
{
    int reserved;
} FILE;

// a complete object type other than an array type capable of recording
// all the information needed to specify uniquely every position within a file
typedef long long fpos_t;

// Null as in stddef.h
#ifndef NULL
#ifndef __cplusplus
#define NULL ((void*) 0)
#else
#define NULL 0
#endif
#endif

// used for third argument to setvbuf
#define _IOFBF 1
#define _IOLBF 2
#define _IONBF 3

// size of buffer in setbuf
#define BUFSIZ 2048

// end-of-file constant
#define EOF -1

// minimum number of files that the implementation guarantees can be open simultaneously
#define FOPEN_MAX 32

// the longest file name string that the implementation guarantees can be opened
#define FILENAME_MAX 1024

// large enough to hold a temporary file name string generated by the tmpnam function
#define L_tmpnam 1024

// used for the third argument to fseek
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

// minimum number of unique file names that can be generated by the tmpnam function
// POSIX: XSI-conformant systems, the value of TMP_MAX is at least 10000.
#define TMP_MAX 256

extern FILE* stderr;
extern FILE* stdin;
extern FILE* stdout;

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

// 7.21.4.1
int remove(const char *filename);

// 7.21.4.2
int rename(const char *old, const char *new);

// 7.21.4.3
FILE *tmpfile(void);

// 7.21.4.4
char *tmpnam(char *s);

// 7.21.5.1
int fclose(FILE *stream);

// 7.21.5.2
int fflush(FILE *stream);

// 7.21.5.3
FILE *fopen(const char * restrict filename, const char * restrict mode);

// 7.21.5.4
FILE *freopen(const char * restrict filename, const char * restrict mode, FILE * restrict stream);

// 7.21.5.5
void setbuf(FILE * restrict stream, char * restrict buf);

// 7.21.5.6
int setvbuf(FILE * restrict stream, char * restrict buf, int mode, size_t size);

// 7.21.6.1
int fprintf(FILE * restrict stream, const char * restrict format, ...);

// 7.21.6.2
int fscanf(FILE * restrict stream, const char * restrict format, ...);

// 7.21.6.3
int printf(const char * restrict format, ...);

// 7.21.6.4
int scanf(const char * restrict format, ...);

// 7.21.6.5
int snprintf(char * restrict s, size_t n, const char * restrict format, ...);

// 7.21.6.6
int sprintf(char * restrict s, const char * restrict format, ...);

// 7.21.6.7
int sscanf(const char * restrict s, const char * restrict format, ...);

// 7.21.6.8
int vfprintf(FILE * restrict stream, const char * restrict format, va_list arg);

// 7.21.6.9
int vfscanf(FILE * restrict stream, const char * restrict format, va_list arg);

// 7.21.6.10
int vprintf(const char * restrict format, va_list arg);

// 7.21.6.11
int vscanf(const char * restrict format, va_list arg);

// 7.21.6.12
int vsnprintf(char * restrict s, size_t n, const char * restrict format, va_list arg);

// 7.21.6.13
int vsprintf(char * restrict s, const char * restrict format, va_list arg);

// 7.21.6.14
int vsscanf(const char * restrict s, const char * restrict format, va_list arg);

// 7.21.7.1
int fgetc(FILE *stream);

// 7.21.7.2
char *fgets(char * restrict s, int n, FILE * restrict stream);

// 7.21.7.3
int fputc(int c, FILE *stream);

// 7.21.7.4
int fputs(const char * restrict s, FILE * restrict stream);

// 7.21.7.5
int getc(FILE *stream);

// 7.21.7.6
int getchar(void);

// 7.21.7.7
int putc(int c, FILE *stream);

// 7.21.7.8
int putchar(int c);

// 7.21.7.9
int puts(const char *s);

// 7.21.7.10
int ungetc(int c, FILE *stream);

// 7.21.8.1
size_t fread(void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);

// 7.21.8.2
size_t fwrite(const void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);

// 7.21.9.1
int fgetpos(FILE * restrict stream, fpos_t * restrict pos);

// 7.21.9.2
int fseek(FILE *stream, long int offset, int whence);

// 7.21.9.3
int fsetpos(FILE *stream, const fpos_t *pos);

// 7.21.9.4
long int ftell(FILE *stream);

// 7.21.9.5
void rewind(FILE *stream);

// 7.21.10.1
void clearerr(FILE *stream);

// 7.21.10.2
int feof(FILE *stream);

// 7.21.10.3
int ferror(FILE *stream);

// 7.21.10.4
void perror(const char *s);

#ifdef  __cplusplus
}
#endif

// ----------------------------
// POSIX

// size_t as in sys/types.h
#ifdef _WIN64
typedef long long ssize_t;
#else
typedef int ssize_t;
#endif

// [CX] Maximum size of character array to hold ctermid() output.
#define L_ctermid 1024

// Default directory prefix for tempnam().
extern char* P_tmpdir;

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

char* ctermid(char *s);
int dprintf(int fildes, const char* restrict format, ...);

void flockfile(FILE* file);
int ftrylockfile(FILE* file);
void funlockfile(FILE* file);

FILE* fmemopen(void* restrict buf, size_t size, const char* restrict mode);
int fseeko(FILE *stream, off_t offset, int whence);
off_t ftello(FILE *stream);

int getc_unlocked(FILE *stream);
int getchar_unlocked(void);
int putc_unlocked(int c, FILE *stream);
int putchar_unlocked(int c);

ssize_t getdelim(char ** restrict lineptr, size_t* restrict n, int delimiter, FILE* restrict stream);
ssize_t getline(char** restrict lineptr, size_t* restrict n, FILE* restrict stream);

FILE *open_memstream(char **bufp, size_t *sizep);

int pclose(FILE *stream);
FILE *popen(const char *command, const char *mode);

int renameat(int oldfd, const char* old, int newfd, const char* new);

int vdprintf(int fildes, const char* restrict format, va_list ap);

// ----------------------------
// Glibc

typedef long long off64_t;

int fseeko64(FILE *stream, off64_t offset, int whence);
off64_t ftello64(FILE *stream);

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------------------------

#endif // DIAGNOSTIC_ISO_C18_STDIO_H
