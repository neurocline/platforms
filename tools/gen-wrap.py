#! python3
# coding=utf-8

# The point of the gen-wrap.py program is to create wrapping headers for any
# header that might be on the target system, so we can evaluate cross-compiling.
# Currently, this only targets posix-on-win32, e.g. building POSIX apps on
# Windows. This could be expanded into a matrix, allowing building Win32 code
# on Linux, Mac, etc. But it seems like the need currently is building POSIX-using
# code on Windows.

# These are the four domains:
# - ISO C
# - POSIX (subsumes most but not all ISO C)
# - Unix (non-POSIX extensions)
# - Windows
# and these are the 7 products we observe as being possible
# - ISO-C
# - POSIX
# - Windows
# - ISO-C + POSIX
# - ISO-C + POSIX + Windows
# - POSIX + Windows
# - Unix
#
# For non-Windows files, obviously we aren't actually wrapping, we are shimming.
# This lets us test what specific non-Windows features are being used. For any
# categories that involve Windows, we wrap so that we can make sure the POSIX/Unix
# code works as-is on Windows (Microsoft doesn't implement all of POSIX, and some
# of what it implements diverges from POSIX).

import os
import sys

def main():
    if len(sys.argv) < 3:
        raise Exception("need output directory and kits directory")

    headers = build()
    gen_all(headers, sys.argv[1], sys.argv[2])

def gen_all(headers, outdir, kitsdir):
    for header, tag in sorted(headers.items()):
        # print(header, tag)
        body = load_body(header, kitsdir)
        gen_header(header, outdir, tag, body)

def load_body(header, kits):
    path = os.path.join(kits, "iso-c", header)
    if os.path.exists(path):
        return loadfile(path)

    path = os.path.join(kits, "posix", header)
    if os.path.exists(path):
        return loadfile(path)

    path = os.path.join(kits, "unix", header)
    if os.path.exists(path):
        return loadfile(path)

    return []

def loadfile(path):
    lines = []
    with open(path, "rt", encoding="utf-8") as fin:
        for line in fin:
            lines.append(line.rstrip())
    return lines

def gen_header(header, outdir, tag, body):
    outpath = os.path.join(outdir, header)
    os.makedirs(os.path.dirname(outpath), exist_ok=True)
    with open(outpath, "wt", encoding="utf-8") as fout:
        text = gen_preamble(header, tag)
        text += gen_body(header, tag, body)

        for line in text:
            print("%s" % line, file=fout)

def gen_preamble(header, tag):
    text = []

    # If this header isn't found anywhere in Windows, then no need to wrap anything
    if tag.find('Windows') == -1:
        text += [ '[NOWINDOWS]' ]

    # Handle ISOC, ISOC+POSIX, ISOC+POSIX+WINDOWS, ISOC+POSIX
    if tag.find('ISOC') != -1:
        return gen_c_preamble(text, header, tag)

    # Handle POSIX, POSIX+Windows
    elif tag.find('POSIX') != -1:
        return gen_POSIX_preamble(text, header, tag)

    # Handle Unix
    elif tag.find('Unix') != -1:
        return gen_Unix_preamble(text, header, tag)

    # Handle Windows
    elif tag.find('Windows') != -1:
        return gen_Windows_preamble(text, header, tag)

    else:
        raise Exception("don't know")

# This is for all headers in the ISO C standard, some of which
# are extended by POSIX or munged by Windows
def gen_c_preamble(text, header, tag):
    text += [
        '// <%s>' % header,
    ]

    if tag.find('POSIX') != -1:
        text += [ '// - %s' % POSIX_blurb[header] ]

    text += [
        '//',
        '// Defined in ISO C18 Standard: %s <%s>.' % (C_blurb[header], header)
    ]

    # Show extra notes for ISO C headers extended by POSIX
    if tag.find('POSIX') != -1:
        if header in POSIX_ISO_aligned:
            text += [ '// Aligned with POSIX.1-2017 <%s>' % header ]
        else:
            text += [ '// Extended in POSIX.1-2017 <%s>' % header ]
        posix_link = header.replace('/', '_')
        text += [ '// See http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/%s.html' % posix_link ]

    if header in Glib_extended:
        text += [ '// Has Glibc 2.28 extensions' ]

    # assert.h is special. It cannot have a guard around the whole file, so it has
    # an embedded guard deep in the body
    if header == 'assert.h':
        return text

    text += [
        '',
        '#pragma once',
        '[GUARD]',
    ]
    return text

# This is for all headers in POSIX that aren't also in ISO C. Some of these
# are munged by Windows.
def gen_POSIX_preamble(text, header, tag):
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

# These are not in POSIX or ISO C, but are used in some Unix systems (Glibc, MUSL, etc)
def gen_Unix_preamble(text, header, tag):
    text += [
        '// <%s>' % header,
        '// - %s' % Unix_blurb[header],
        '//',
        '// Unix header <%s>' % header,
    ]

    if header in Glib_extended:
        text += [ '// Has Glibc 2.28 extensions' ]

    text += [
        '',
        '#pragma once',
        '[GUARD_UNIX]',
    ]

    return text

# These are only in Windows
def gen_Windows_preamble(text, header, tag):
    text += [
        '// <%s>' % header,
        '// - %s' % Windows_blurb[header],
        '//',
        '// Windows header <%s>' % header,
    ]

    text += [
        '',
        '#pragma once',
        '[GUARD_WINDOWS]',
    ]

    return text

def gen_body(header, tag, body):
    text = []

    if header in Windows_VC_headers:
        text += [ '[MICROSOFT_VC_INCLUDE]' ]
    if header in Windows_Ignore_headers:
        text += [ '[IGNOREWINDOWS]' ]

    text += [
        '',
        '[BODY]',
    ]
    text += body

    # assert.h is special. It cannot have a guard around the whole file, so it has
    # an embedded guard deep in the body, so we need to finish this one differently
    if header == 'assert.h':
        text += [ '[FOOTER]' ]
        return text

    # Add footer tag and the right guard tag
    text += [
        '',
        '[FOOTER]',
    ]

    if tag.find('ISOC') != -1:
        text += [ '[/GUARD]' ]
    elif tag.find('POSIX') != -1:
        text += [ '[/GUARD_POSIX]' ]
    elif tag.find('Unix') != -1:
        text += [ '[/GUARD_UNIX]' ]
    elif tag.find('Windows') != -1:
        text += [ '[/GUARD_WINDOWS]' ]
    else:
        raise Exception("unexpected %s: %s" % (header, tag))

    return text

# ------------------------------------------------------------------------------------------------

# Make a master list of headers and what "kind" of header it is:
# - ISOC
# - ISOC+POSIX
# - ISOC+POSIX+Windows
# - ISOC+Windows
# - POSIX
# - POSIX+Windows
# - Unix
# - Windows
# Other combinations are not handled yet

def build():
    headers = dict()

    for k,v in ISO_C_headers.items():
        headers[k] = "ISOC"

    add(headers, POSIX_2017_headers, 'POSIX')
    add(headers, Windows_headers, 'Windows')
    add(headers, Windows_C_POSIX_headers, 'Windows')
    add(headers, Unix_headers, 'Unix')

    if 0:
        allowed = {'ISOC', 'ISOC+POSIX', 'ISOC+POSIX+Windows', 'ISOC+Windows', 'POSIX', 'POSIX+Windows', 'Unix', 'Windows'}
        stats = dict()
        for h in headers:
            if headers[h] not in allowed:
                raise Exception("weird combo for %s: %s" % (h, headers[h]))
            if headers[h] not in stats:
                stats[headers[h]] = []
            stats[headers[h]].append(h)

        for tag in sorted(stats):
            print("%s: %d" % (tag, len(stats[tag])))
            for h in sorted(stats[tag]):
                print("    %s" % h)

    return headers

def add(h, L, tag):
    for item in L:
        if item in h:
            h[item] = h[item] + "+" + tag
        else:
            h[item] = tag

# ------------------------------------------------------------------------------------------------

# ISO C headers, from the ISO C 2018 specification, broken down by when they were first introduced.
# Microsoft doesn't fully implement C99 or C11.
ISO_C_headers = {
    "assert.h": "C",
    "ctype.h":  "C",
    "errno.h":  "C",
    "float.h":  "C",
    "limits.h": "C",
    "locale.h": "C",
    "math.h":   "C",
    "setjmp.h": "C",
    "signal.h": "C",
    "stdarg.h": "C",
    "stddef.h": "C",
    "stdio.h":  "C",
    "stdlib.h": "C",
    "string.h": "C",
    "time.h":   "C",

    "iso646.h": "C95",
    "wchar.h":  "C95",
    "wctype.h": "C95",

    "complex.h":  "C99",
    "fenv.h":     "C99",
    "inttypes.h": "C99",
    "stdbool.h":  "C99",
    "stdint.h":   "C99",
    "tgmath.h":   "C99",

    "stdalign.h":    "C11",
    "stdatomic.h":   "C11",
    "stdnoreturn.h": "C11",
    "threads.h":     "C11",
    "uchar.h":       "C11",
}

# ISO C titles for headers
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

# ------------------------------------------------------------------------------------------------

# POSIX subsumes the ISO C Standard, although this is true only up through C99;
# POSIX-2007.1 is the most recent standard, which predates C11.

# Some of the POSIX headers are aligned with the ISO - the rest have
# POSIX-specific extensions.
POSIX_ISO_aligned = [
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

# POSIX-2007.1 headers
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

# POSIX titles for headers
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

# ------------------------------------------------------------------------------------------------

Unix_headers = [
    "sys/poll.h",
    "sys/ioctl.h",
]

# Unix titles for headers
Unix_blurb = {
    'sys/poll.h': "definitions for the poll() function (nonstandard file)",
    "sys/ioctl.h" :"ioctl function",
}

# Glibc has added functionality to some ISO/POSIX headers (all? this is partial)
Glib_extended = [
    "assert.h",
    "fcntl.h",
    "stdio.h",
    "sys/mman.h",
]

# ------------------------------------------------------------------------------------------------

# These are the Windows headers that overlap with ISO C and POSIX headers. Windows POSIX
# functionality is limited and in some cases contradicts the POSIX standard.
Windows_C_POSIX_headers = [
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
    # "threads.h", there is a thr/threads.h which looks like C11 threads but no docs point to it
    "time.h",
    # "utime.h",
    "wchar.h",
    "wctype.h",
]

# In Windows 2013 and up, some headers were split out of the CRT and put into the
# ucrt in Windows kits. These remain in the VC headers
Windows_VC_headers = [
    "limits.h",
    "stdint.h",
]

# Some Windows headers need to be ignored by default
Windows_Ignore_headers = [
    "stdarg.h",
    "sys/types.h",
    "time.h",
]

# These headers contain POSIX functionality, in non-standard header names and sometimes
# not matching behavior in the POSIX standard. These would never be included in non-Windows
# source code, but are often referenced in projects attempting cross-platform behavior.
Windows_headers = [
    "direct.h",
    "io.h",
    "malloc.h",
    "process.h",
]

# Windows titles for headers
Windows_blurb = {
    "direct.h": "directory handling and creation",
    "io.h": "low-level I/O and file handling",
    "malloc.h": "memory allocation",
    "process.h": "process control (exec and spawn)",
}

# -----------------------------------------------------------------------------------------------

# This is just so that we can write code in what seems reasonable rather than
# in the order Python execution needs it.
if __name__ == '__main__':
    main()
