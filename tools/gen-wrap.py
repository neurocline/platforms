#! python3
# coding=utf-8

import os
import sys

def main():
    if len(sys.argv) < 2:
        raise Exception("need output directory")

    headers = build()
    gen(headers, sys.argv[1])

def gen(headers, outdir):
    for header in sorted(headers):
        c_type = headers[header][0] if headers[header][0] != 'POSIX.1-2017' else None
        is_posix = True if 'POSIX.1-2017' in headers[header] else False
        # print("%s C:%s POSIX:%s" % (header, c_type, is_posix))

        gen_header(header, outdir, c_type, is_posix)

def gen_header(header, outdir, c_type, is_posix):
    outpath = os.path.join(outdir, header)
    os.makedirs(os.path.dirname(outpath), exist_ok=True)
    with open(outpath, "wt", encoding="utf-8") as fout:
        text = gen_preamble(header, c_type, is_posix)
        text += gen_body(header, c_type, is_posix)

        for line in text:
            print("%s" % line, file=fout)

def gen_preamble(header, c_type, is_posix):
    text = []
    if header not in Windows_headers:
        text += [ '[NOWINDOWS]' ]
    if c_type is not None:
        text += [
            '// <%s>' % header,
        ]
        if header in POSIX_blurb:
            text += [ '// - %s' % POSIX_blurb[header] ]
        text += [
            '//',
            '// Defined in ISO C18 Standard: %s <%s>.' % (C_blurb[header], header)
        ]
        if is_posix:
            if header in POSIX_aligned:
                text += [ '// Aligned with POSIX.1-2017 <%s>' % header ]
            else:
                text += [ '// Extended in POSIX.1-2017 <%s>' % header ]

            posix_link = header.replace('/', '_')
            text += [ '// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/%s.html' % posix_link ]
        if header in Glib_extended:
            text += [ '// Has Glibc 2.28 extensions' ]
        text += [
            '',
            '#pragma once',
            '[GUARD]',
        ]
    else:
        posix_link = header.replace('/', '_')
        text += [
            '// <%s>' % header,
            '// - %s' % POSIX_blurb[header],
            '//',
            '// Defined in POSIX.1-2017 <%s>' % header,
            '// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/%s.html' % posix_link
        ]
        if header in Glib_extended:
            text += [ '// Has Glibc 2.28 extensions' ]
        text += [
            '',
            '#pragma once',
            '[GUARD_POSIX]',
        ]

    return text

def gen_body(header, c_type, is_posix):
    text = [
        '',
        '[BODY]',
        '[FOOTER]',
    ]

    if c_type is not None:
        text += [ '[/GUARD]' ]
    else:
        text += [ '[/GUARD_POSIX]' ]

    return text

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

POSIX_aligned = [
    "assert.h",
    "complex.h",
    "fenv.h",
    "float.h",
    "iso646.h",
    "stdarg.h",
    "stdbool.h",
    "stddef.h",
    "tgmath.h",
]

Glib_extended = [
    "assert.h",
    "fcntl.h",
    "stdio.h",
    "sys/mman.h",
]

# Aligned with C18 standard
C_blurb = {
    'assert.h': "7.2 Diagnostics",
    'complex.h': "7.3 Complex arithmetic",
    'ctype.h': "7.4 Character handling",
    'errno.h': "7.5 Errors",
    'fenv.h': "7.6 Floating-point environment",
    'float.h': "7.7 Characteristics of floating types",
    'inttypes.h': "7.8 Format conversions of integer types",
    'iso646.h': "7.9 Alternative spellings",
    'limits.h': "7.10 Sizes of integer types",
    'locale.h': "7.11 Localization",
    'math.h': "7.12 Mathematics",
    'setjmp.h': "7.13 Nonlocal jumps",
    'signal.h': "7.14 Signal handling",
    'stdalign.h': "7.15 Alignment",
    'stdarg.h': "7.16 Variable arguments",
    'stdatomic.h': "7.17 Atomics",
    'stdbool.h': "7.18 Boolean type and values",
    'stddef.h': "7.19 Common definitions",
    'stdint.h': "7.20 Integer types",
    'stdio.h': "7.21 Input/output",
    'stdlib.h': "7.22 General utilities",
    'stdnoreturn.h': "7.23 _Noreturn",
    'string.h': "7.24 String handling",
    'tgmath.h': "7.25 Type-generic math",
    'threads.h': "7.26 Threads",
    'time.h': "7.27 Date and time",
    'uchar.h': "7.28 Unicode utilities",
    'wchar.h': "7.29 Extended multibyte and wide character utilities",
    'wctype.h': "7.30 Wide character classification and mapping utilities",
}

POSIX_blurb = {
    'aio.h': "asynchronous input and output",
    'arpa/inet.h': "definitions for internet operations",
    'assert.h': "verify program assertion",
    'complex.h': "complex arithmetic",
    'cpio.h': "cpio archive values",
    'ctype.h': "character types",
    'dirent.h': "format of directory entries",
    'dlfcn.h': "dynamic linking",
    'errno.h': "system error numbers",
    'fcntl.h': "file control options",
    'fenv.h': "floating-point environment",
    'float.h': "floating types",
    'fmtmsg.h': "message display structures",
    'fnmatch.h': "filename-matching types",
    'ftw.h': "file tree traversal",
    'glob.h': "pathname pattern-matching types",
    'grp.h': "group structure",
    'iconv.h': "codeset conversion facility",
    'inttypes.h': "fixed size integer types",
    'iso646.h': "alternative spellings",
    'langinfo.h': "language information constants",
    'libgen.h': "definitions for pattern matching functions",
    'limits.h': "implementation-defined constants",
    'locale.h': "category macros",
    'math.h': "mathematical declarations",
    'monetary.h': "monetary types",
    'mqueue.h': "message queues",
    'ndbm.h': "definitions for ndbm database operations",
    'net/if.h': "sockets local interfaces",
    'netdb.h': "definitions for network database operations",
    'netinet/in.h': "Internet address family",
    'netinet/tcp.h': "definitions for the Internet Transmission Control Protocol (TCP)",
    'nl_types.h': "data types",
    'poll.h': "definitions for the poll() function",
    'pthread.h': "threads",
    'pwd.h': "password structure",
    'regex.h': "regular expression matching types",
    'sched.h': "execution scheduling",
    'search.h': "search tables",
    'semaphore.h': "semaphores",
    'setjmp.h': "stack environment declarations",
    'signal.h': "signals",
    'spawn.h': "spawn",
    'stdarg.h': "handle variable argument list",
    'stdbool.h': "boolean type and values",
    'stddef.h': "standard type definitions",
    'stdint.h': "integer types",
    'stdio.h': "standard buffered input/output",
    'stdlib.h': "standard library definitions",
    'string.h': "string operations",
    'strings.h': "string operations",
    'stropts.h': "STREAMS interface",
    'sys/ipc.h': "XSI interprocess communication access structure",
    'sys/mman.h': "memory management declarations",
    'sys/msg.h': "XSI message queue structures",
    'sys/resource.h': "definitions for XSI resource operations",
    'sys/select.h': "select types",
    'sys/sem.h': "XSI semaphore facility",
    'sys/shm.h': "XSI shared memory facility",
    'sys/socket.h': "main sockets header",
    'sys/stat.h': "data returned by the stat() function",
    'sys/statvfs.h': "VFS File System information structure",
    'sys/time.h': "time types",
    'sys/times.h': "file access and modification times structure",
    'sys/types.h': "data types",
    'sys/uio.h': "definitions for vector I/O operations",
    'sys/un.h': "definitions for UNIX domain sockets",
    'sys/utsname.h': "system name structure",
    'sys/wait.h': "declarations for waiting",
    'syslog.h': "definitions for system error logging",
    'tar.h': "extended tar definitions",
    'termios.h': "define values for termios",
    'tgmath.h': "type-generic macros",
    'time.h': "time types",
    'trace.h': "tracing",
    'ulimit.h': "ulimit commands",
    'unistd.h': "standard symbolic constants and types",
    'utime.h': "access and modification times structure",
    'utmpx.h': "user accounting database definitions",
    'wchar.h': "wide-character handling",
    'wctype.h': "wide-character classification and mapping utilities",
    'wordexp.h': "word-expansion types",
}

Windows_headers = [
    "assert.h",
    "complex.h",
    "ctype.h",
    "errno.h",
    "fcntl.h",
    "fenv.h",
    "float.h",
    "inttypes.h",
    "iso646.h",
    "limits.h",
    "locale.h",
    "math.h",
    "search.h",
    "setjmp.h",
    "signal.h",
    "stdarg.h",
    "stdbool.h",
    "stddef.h",
    "stdint.h",
    "stdio.h",
    "stdlib.h",
    "string.h",
    "sys/stat.h",
    "sys/types.h",
    "threads.h",
    "time.h",
    "utime.h",
    "wchar.h",
    "wctype.h",
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
