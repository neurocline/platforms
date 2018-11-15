// sys_mmap.c

#define _WIN32_LEAN_AND_MEAN
#define __STDC__ 1

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/mman.h>

#include <io.h> // for _get_osfhandle
#include <Windows.h>

struct _maps
{
    HANDLE file; // backing store file
    HANDLE view; // view object
    void* addr;  // the mapped view itself
    size_t len;  // how much was mapped
} maps[16];

void* mmap(void* addr, size_t len, int prot, int flags, int fildes, off_t off)
{
    // We don't support mapping into a fixed address
    if (addr != NULL)
    {
        errno = EADDRNOTAVAIL;
        return MAP_FAILED;
    }

    // Find a new slot to put a mapping into
    int slot;
    for (slot = 0; slot < 16; slot++)
        if (maps[slot].addr == NULL)
            break;
    if (slot == 16)
    {
        errno = ENOBUFS;
        return MAP_FAILED;
    }

    // Convert POSIX prot and flags into Win32 values. We only handle
    // some combinations at the moment
    DWORD winProt = 0;
    DWORD winAccess = 0;

    if (prot == (PROT_EXEC|PROT_WRITE|PROT_READ))
    {
        winProt = PAGE_EXECUTE_READWRITE;
        winAccess = FILE_MAP_ALL_ACCESS;
    }
    else if (prot == (PROT_EXEC|PROT_READ))
    {
        winProt = PAGE_EXECUTE_READ;
        winAccess = FILE_MAP_READ;
    }
    else if (prot == (PROT_WRITE|PROT_READ))
    {
        winProt = PAGE_READWRITE;
        winAccess = FILE_MAP_WRITE;
    }
    else if (prot == PROT_READ)
    {
        winProt = PAGE_READONLY;
        winAccess = FILE_MAP_READ;
    }
    else
    {
        // This is a combination we don't allow just now (ever?)
        // Specifically, Windows doesn't allow write-only access,
        // and we shouldn't lie and give the user a readwrite view.
        errno = EACCES;
        return MAP_FAILED;
    }

    // Now interpret flags
    if ((flags & (MAP_PRIVATE|MAP_SHARED|MAP_FIXED)) == MAP_PRIVATE)
    {
        winAccess |= FILE_MAP_COPY;
    }
    else if ((flags & (MAP_PRIVATE|MAP_SHARED|MAP_FIXED)) == MAP_SHARED)
    {
        // this is the default
    }
    else
    {
        // Ilegal combination for us
        errno = EACCES;
        return MAP_FAILED;
    }

    // Anonymous mmap can't specify a fildes, non-anonymous must have a file
    bool anon = (flags & MAP_ANON) == MAP_ANON;
    if (anon && fildes != -1 || !anon && fildes == -1)
    {
        errno = EACCES;
        return MAP_FAILED;
    }

    // If there is a backing file, get it
    HANDLE backing = INVALID_HANDLE_VALUE;
    if (fildes != -1)
        backing = (HANDLE) _get_osfhandle(fildes);

    // Microsoft APIs pass 64-bit values as two 32-bit values in many places
    DWORD lenhi = (DWORD)((unsigned long long)len >> 32);
    DWORD lenlo = (DWORD)(len & 0xFFFFFFFF);
    DWORD offhi = (DWORD)((unsigned long long)off >> 32);
    DWORD offlo = (DWORD)(off & 0xFFFFFFFF);

    maps[slot].file = backing;
    maps[slot].view = CreateFileMappingA(maps[slot].file, NULL, winProt, lenhi, lenlo, NULL);
    maps[slot].addr = MapViewOfFile(maps[slot].view, winAccess, offhi, offlo, len);
    maps[slot].len = len;

    return maps[slot].addr;
}

int munmap(void* addr, size_t len)
{
    // Find the object in our list
    int slot;
    for (slot = 0; slot < 16; slot++)
        if (maps[slot].addr == addr)
            break;
    if (slot == 16)
    {
        errno = EINVAL;
        return -1;
    }

    // Right now, we only support "unmap everything you mapped". TBD to handle
    // splitting of mapped views, which means we need to compare the passed-in
    // address and length against every range
    if (maps[slot].len != len)
    {
        errno = EACCES;
        return -1;
    }

    // Do the unmap and remove this entry (we don't own the file,
    // so it stays open)
    BOOL ok = UnmapViewOfFile(maps[slot].addr);
    if (!ok)
    {
        errno = EACCES;
        _set_doserrno(GetLastError());
        return -1;
    }

    maps[slot].addr = NULL;
    maps[slot].view = NULL;
    maps[slot].file = NULL;
    maps[slot].len = 0;

    return 0;
}
