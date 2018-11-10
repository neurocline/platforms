// test-stdarg-posix.c

#include <assert.h>
#include <stdarg.h>

#ifndef _POSIX_ON_WIN32__STDARG_H
#error "Expected the posix-on-win32 stdarg.h header"
#endif

int vargs(char* fmt, ...)
{
    int rv = 0;
    va_list va;
    va_start(va, fmt);
    char b = va_arg(va, char);
    int c = va_arg(va, int);
    short d = va_arg(va, short);
    long long e = va_arg(va, long long);
    if (fmt != 0 && fmt[0] == 'a' && fmt[2] == 0)
    {
        assert(b == 0x11);
        assert(c == 0x22334455);
        assert(d == 0x6677);
        assert(e == 66);
        rv = 1;
    }
    va_end(va);
    return rv;
}

int test_stdarg()
{
    int rv = vargs("a", (char)0x11, (int)0x22334455, (short)0x6677, (long long)66);
    assert(rv == 1);
    return 0;
}
