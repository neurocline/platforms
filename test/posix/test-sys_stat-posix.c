// test-sys_stat-posix.c

#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

static void test_stat()
{
    char* path = "../test/file_100bytes";
    struct stat buf;
    int ret = stat(path, &buf);
    assert(ret != -1);
}

static void test_fstat()
{
    char* path = "../test/file_100bytes";
    int fd = open(path, O_RDONLY);
    assert(fd != -1);
    struct stat buf;
    int ret = fstat(fd, &buf);
    assert(ret != -1);
    ret = close(fd);
    assert(ret != -1);
}

int test_sys_stat()
{
    test_stat();
    test_fstat();
    return 0;
}
