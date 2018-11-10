// test-assert-posix.c

#include <assert.h>

#ifndef _POSIX_ON_WIN32__ASSERT_H
#error "Expected the posix-on-win32 assert.h header"
#endif

int test_assert()
{
    assert("this doesn't go off");
    return 0;
}
