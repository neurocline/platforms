// main.c

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
