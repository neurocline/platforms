// test-unistd-posix.c

#include <assert.h>
#include <pwd.h>
#include <unistd.h>

#pragma comment(lib, "Secur32.lib")

static void test_getpwuid()
{
    struct passwd* pw = getpwuid(getuid());
    printf("pw_gecos = %s\n", pw->pw_gecos);
}

int test_unistd()
{
    test_getpwuid();
    return 0;
}
