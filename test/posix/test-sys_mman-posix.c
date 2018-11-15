// test-sys_mman-posix.c

#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

void test_mman_anon()
{
    // Test 16K read/write shared
    size_t len = 16384;
    void* addr = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
    assert(addr != MAP_FAILED);
    int err = munmap(addr, len);
    assert(err == 0);

    // Test 16K read/write private
    len = 16384;
    addr = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
    assert(addr != MAP_FAILED);
    err = munmap(addr, len);
    assert(err == 0);
}

void test_mman_file()
{
    char* path = "../test/file_100bytes";
	int fd = open(path, O_RDONLY);
    assert(fd != -1);
    size_t len = 100;
    void* addr = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
    assert(addr != NULL);
    assert(memcmp(addr, "this file is 100 bytes long. Really", 35) == 0);
    int err = munmap(addr, len);
    assert(err == 0);
    err = close(fd);
    assert(err == 0);
}

int test_sys_mman()
{
    test_mman_anon();
    test_mman_file();
    return 0;
}
