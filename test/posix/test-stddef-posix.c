// test-stddef-posix.c

#include <assert.h>
#include <stddef.h>

int test_stddef()
{
    char* p = NULL;

    struct a { int b; int c; };
    assert(offsetof(struct a, b) == 0);
    assert(offsetof(struct a, c) == 4);

    char* p2 = NULL;
    ptrdiff_t d = p2 - p;
    wchar_t ch = 0;

    struct a gob;
    size_t n = sizeof(gob);

    ch += 1;
    n += 1;
    d = 0;

    return 0;
}
