// test-assert-posix.c

#include <assert.h>

int test_assert()
{
    assert("this doesn't go off");
    return 0;
}
