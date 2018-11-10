// main.c

// 
#include <stdarg.h>

void f(int p, ...)
{
    va_list va;
    va_start(va, p);
    char c = va_arg(va, char);
    short s = va_arg(va, short);
    int i = va_arg(va, int);
    va_end(va);
    (void)(c + s + i);
}

int main(int argc, char** argv)
{
    argc = 0; argv = 0;
    char c = 1;
    short s = 0x0203;
    int i = 0x04050607;
    f(1, c, s, i);
    return 0;
}

#if 0

#include <stddef.h>

void output(size_t v);

int main(int argc, char** argv)
{
    argc; argv;
    size_t v = 0;
    output(v);
    return 0;
}

#include <stdio.h>

void output(size_t v)
{
    printf("sizeof(size_t): %zu\n", sizeof(v));
}

// Make sure our errno.h got included
#include <errno.h>
#ifndef _POSIX_ON_WIN32__ERRNO_H
#error "did not include the correct <errno.h>"
#endif

#include <fcntl.h>
#ifndef _POSIX_ON_WIN32__FCNTL_H
#error "did not include the correct <fcntl.h>"
#endif

// Make sure our pwd.h got included
#include <pwd.h>
#ifndef _POSIX_ON_WIN32__PWD_H
#error "did not include the correct <pwd.h>"
#endif

#include <stddef.h>
#include <stdarg.h>

// Make sure our stdio.h got included
#include <stdio.h>
#ifndef _POSIX_ON_WIN32__STDIO_H
#error "did not include the correct <stdio.h>"
#endif

// Make sure our stdlib.h got included
#include <stdlib.h>
#ifndef _POSIX_ON_WIN32_USE_WIN32_STDLIB
#error "did not include the correct <stdlib.h>"
#endif

// Make sure our string.h got included
#include <string.h>
#ifndef _POSIX_ON_WIN32_USE_WIN32_STRING
#error "did not include the correct <string.h>"
#endif

// Make sure our sys/mman.h got included
#include <sys/mman.h>
#ifndef _POSIX_ON_WIN32__SYS_MMAN_H
#error "did not include the correct <sys/mman.h>"
#endif

// Make sure our sys/stat.h got included
#include <sys/stat.h>
#ifndef _POSIX_ON_WIN32__SYS_STAT_H
#error "did not include the correct <sys/stat.h>"
#endif

// Make sure our sys/types.h got included
#include <sys/types.h>
#ifndef _POSIX_ON_WIN32__SYS_TYPES_H
#error "did not include the correct <sys/types.h>"
#endif

// Make sure our time.h got included
#include <time.h>
#ifndef _POSIX_ON_WIN32__TIME_H
#error "did not include the correct <time.h>"
#endif

#endif
