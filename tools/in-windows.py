#! python3
# coding=utf-8

import os
import sys

def main():
    if len(sys.argv) < 2 or not os.path.exists(sys.argv[1]):
        raise Exception("need valid paths")
    includesfile = sys.argv[1]

    found = []
    if os.path.exists(includesfile):
        found = load_found(includesfile)
    else:
        raise Exception("run find-includes first")

    headers = build()

    in_windows = set()
    for path in found:
        path = path.replace('\\', '/')
        print("looking at %s" % path)

        in_windowsKit = False
        in_msvc = False
        if path.lower().find("Windows Kits") != -1:
            in_windowsKit = True
            print("in_windowsKit")
        if path.lower().find("vc/tools/msvc") != -1:
            in_msvc = True
            print("in_msvc")
        if path.lower().find("vc/include") != -1:
            in_msvc = True
            print("in_msvc")

        if in_windowsKit or in_msvc:
            leaf = path.rfind("/") + 1
            par = path[:leaf-1].rfind("/") + 1
            print("  parent=%s leaf=%s" % (path[par:], path[leaf:]))
            if path[leaf:] in headers:
                in_windows.add(path[leaf:])
            elif path[par:] in headers:
                in_windows.add(path[par:])

    print("In Windows:\n----------")
    for header in sorted(headers):
        if header in in_windows:
            print("%s" % header)

    print("Notn in Windows:\n----------")
    for header in sorted(headers):
        if header not in in_windows:
            print("%s" % header)

def load_found(path):
    found = []
    with open(path, "rt", encoding="utf-8") as f:
        for line in f:
            found.append(line.rstrip())
    return found

def build():
    headers = dict()
    add(headers, C_headers, 'C')
    add(headers, C95_headers, 'C95')
    add(headers, C99_headers, 'C99')
    add(headers, C11_headers, 'C11')
    add(headers, POSIX_2017_headers, 'POSIX.1-2017')
    return headers

def add(h, L, tag):
    for item in L:
        if item not in h:
            h[item] = []
        h[item].append(tag)

C_headers = [
    "assert.h",
    "ctype.h",
    "errno.h",
    "float.h",
    "limits.h",
    "locale.h",
    "math.h",
    "setjmp.h",
    "signal.h",
    "stdarg.h",
    "stddef.h",
    "stdio.h",
    "stdlib.h",
    "string.h",
    "time.h",
]

C95_headers = [
    "iso646.h",
    "wchar.h",
    "wctype.h",
]

C99_headers = [
    "complex.h",
    "fenv.h",
    "inttypes.h",
    "stdbool.h",
    "stdint.h",
    "tgmath.h",
]

C11_headers = [
    "stdalign.h",
    "stdatomic.h",
    "stdnoreturn.h",
    "threads.h",
    "uchar.h",
]

# If I care, break it down

POSIX_2017_headers = [
    "aio.h",
    "arpa/inet.h",
    "assert.h",
    "complex.h",
    "cpio.h",
    "ctype.h",
    "dirent.h",
    "dlfcn.h",
    "errno.h",
    "fcntl.h",
    "fenv.h",
    "float.h",
    "fmtmsg.h",
    "fnmatch.h",
    "ftw.h",
    "glob.h",
    "grp.h",
    "iconv.h",
    "inttypes.h",
    "iso646.h",
    "langinfo.h",
    "libgen.h",
    "limits.h",
    "locale.h",
    "math.h",
    "monetary.h",
    "mqueue.h",
    "ndbm.h",
    "net/if.h",
    "netdb.h",
    "netinet/in.h",
    "netinet/tcp.h",
    "nl_types.h",
    "poll.h",
    "pthread.h",
    "pwd.h",
    "regex.h",
    "sched.h",
    "search.h",
    "semaphore.h",
    "setjmp.h",
    "signal.h",
    "spawn.h",
    "stdarg.h",
    "stdbool.h",
    "stddef.h",
    "stdint.h",
    "stdio.h",
    "stdlib.h",
    "string.h",
    "strings.h",
    "stropts.h",
    "sys/ipc.h",
    "sys/mman.h",
    "sys/msg.h",
    "sys/resource.h",
    "sys/select.h",
    "sys/sem.h",
    "sys/shm.h",
    "sys/socket.h",
    "sys/stat.h",
    "sys/statvfs.h",
    "sys/time.h",
    "sys/times.h",
    "sys/types.h",
    "sys/uio.h",
    "sys/un.h",
    "sys/utsname.h",
    "sys/wait.h",
    "syslog.h",
    "tar.h",
    "termios.h",
    "tgmath.h",
    "time.h",
    "trace.h",
    "ulimit.h",
    "unistd.h",
    "utime.h",
    "utmpx.h",
    "wchar.h",
    "wctype.h",
    "wordexp.h",
]

# -----------------------------------------------------------------------------------------------

# This is just so that we can write code in what seems reasonable rather than
# in the order Python execution needs it.
if __name__ == '__main__':
    main()
