// test-limits-posix.c

#include <assert.h>
#include <limits.h>

int test_limits()
{
    assert(CHAR_BIT == 8);
    return 0;
}
