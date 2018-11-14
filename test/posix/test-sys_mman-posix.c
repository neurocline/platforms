// test-sys_mman-posix.c

#include <assert.h>
#include <sys/mman.h>

int test_sys_mman()
{
    size_t len = 16384;
    void* addr = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
    assert(addr != MAP_FAILED);
    munmap(addr, len);

    return 0;
}
