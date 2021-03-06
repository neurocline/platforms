// <sys/mman.h>
// - memory management declarations
//
// Defined in POSIX.1-2017 <sys/mman.h>

#pragma once
#ifndef CANONICAL_POSIX_2017_SYS_MMAN_H
#define CANONICAL_POSIX_2017_SYS_MMAN_H

// ---------------------------------------------------------------------------
// Canonical header

// ----------------------------
// POSIX

// protection options
#define PROT_NONE       0       // Page cannot be accessed.
#define PROT_READ       (1<<2)  // Page can be read.
#define PROT_WRITE      (1<<1)  // Page can be written.
#define PROT_EXEC       (1<<0)  // Page can be executed.

// flag options
#define MAP_SHARED      (1<<0)   // Share changes.
#define MAP_PRIVATE     (1<<1)   // Changes are private.
#define MAP_FIXED       (1<<2)   // Interpret addr exactly.
#define MAP_ANON        (1<<3)   // Don't use a file. (proposed for POSIX)

// msync() options
#define MS_ASYNC        1   // Perform asynchronous writes.
#define MS_INVALIDATE   2   // Invalidate mappings.
#define MS_SYNC         3   // Perform synchronous writes

// mlockall() options
#define MCL_CURRENT     1   // Lock currently mapped pages.
#define MCL_FUTURE      2   // Lock pages that become mapped.

// failure return from mmap
#define MAP_FAILED      ((void*)-1)

// posix_madvise() values for advice argument
#define POSIX_MADV_DONTNEED     1   // The application expects that it will not access the specified range in the near future.
#define POSIX_MADV_NORMAL       2   // The application has no advice to give on its behavior with respect to the specified range. It is the default characteristic if no advice is given for a range of memory.
#define POSIX_MADV_RANDOM       3   // The application expects to access the specified range in a random order.
#define POSIX_MADV_SEQUENTIAL   4   // The application expects to access the specified range sequentially from lower addresses to higher addresses.
#define POSIX_MADV_WILLNEED     5   // The application expects to access the specified range in the near future.

// posix_typed_mem_open() flags
#define POSIX_TYPED_MEM_ALLOCATE        1   // Allocate on mmap().
#define POSIX_TYPED_MEM_ALLOCATE_CONTIG 2   // Allocate contiguously on mmap().
#define POSIX_TYPED_MEM_MAP_ALLOCATABLE 3   // Map on mmap(), without affecting allocatability.

// as in sys/types.h
typedef unsigned int mode_t;
typedef long long off_t;

// as in sys/types.h
#ifdef _WIN64
typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif

// posix_typed_mem_info
struct posix_typed_mem_info
{
    size_t  posix_tmi_length;   // Maximum length which may be allocated from a typed memory object.
};

// ----------------------------
// Glibc

// Additional flag options
#define MAP_ANONYMOUS   MAP_ANON // Don't use a file (Glibc name)

// Tell C++ this is a C header
#ifdef  __cplusplus
extern "C" {
#endif

int mlock(const void* addr, size_t len);
int munlock(const void* addr, size_t len);
int mlockall(int flags);
int munlockall(void);
void* mmap(void* addr, size_t len, int prot, int flags, int fildes, off_t off);
int mprotect(void* addr, size_t len, int prot);
int msync(void* addr, size_t len, int flags);
int munmap(void* addr, size_t len);
int posix_madvise(void* addr, size_t len, int advice);
int posix_mem_offset(const void* addr, size_t len, off_t* off, size_t* contig_len, int* fildes);
int posix_typed_mem_get_info(int fildes, struct posix_typed_mem_info* info);
int posix_typed_mem_open(const char* name, int oflag, int tflag);
int shm_open(const char* name, int oflag, mode_t mode);
int shm_unlink(const char* name);

#ifdef  __cplusplus
}
#endif

// -----------------------------------------------------------------------------------------------

#endif // CANONICAL_POSIX_2017_SYS_MMAN_H
