#! python3
# coding=utf-8

import os
import sys

def main():
	headers = build()
	found = find_files(headers)
	show_files(found, headers)
	print("\n")
	show_paths(found, headers)

def show_files(found, headers):
	byfile = dict()
	for L in sorted(found):
		i = L.rfind("\\")
		leaf = L[i+1:]
		if leaf.lower() not in headers:
			j = L.rfind("\\", 0, i-1)
			if j == -1:
				raise Exception("don't understand %s" % L)
			leaf = L[j+1:i] + "/" + L[i+1:]
		if leaf not in byfile:
			byfile[leaf] = []
		byfile[leaf].append(L)

	for f in sorted(byfile):
		print("%s: %s" % (f, ", ".join(headers[f.lower()]))
		)
		for L in byfile[f]:
			print("    %s" % L)

def show_paths(found, headers):
	bypath = dict()
	for L in sorted(found):
		i = L.rfind("\\")
		leaf = L[i+1:]
		prefix = L[:i]

		if prefix not in bypath:
			bypath[prefix] = []
		bypath[prefix].append(leaf)

	for p in sorted(bypath):
		print("%s" % p)
		print("    %s" % ", ".join(bypath[p]))

def find_files(headers):
	found = []
	count = 0
	dot = 0
	n = 0
	for root, dirs, files in os.walk(sys.argv[1]):
		par = root.rfind("/")
		if par == -1:
			par = root.rfind("\\")
		par = root[par+1:] if par != -1 else ""
		for f in files:
			n = n + 1
			if f.lower() in headers:
				path = os.path.join(root, f)
				#print("%s" % path)
				found.append(path)
			elif (par+"/"+f).lower() in headers:
				path = os.path.join(root, f)
				#print("%s" % path)
				found.append(path)

			count = count + 1
			if count > 1000:
				print(".", end="", file=sys.stderr, flush=True)
				count = count - 1000
				dot = dot + 1
			if dot == 60:
				print(" (%d/%d)" % (len(found), n), file=sys.stderr, flush=True)
				dot = 0
		n = n + len(dirs)
	return found

def build():
	headers = dict()
	add(headers, C_headers, 'C')
	add(headers, C95_headers, 'C95')
	add(headers, C99_headers, 'C99')
	add(headers, C11_headers, 'C11')
	add(headers, POSIX_2017_headers, 'POSIX.1-2017')
	#print(headers)
	return headers

def test_out():
	for item in sorted(headers):
		if len(headers[item]) > 1:
			# print("%s - %s" % (item, headers[item]))
			continue

		if headers[item][0][0] == 'C':
			print("%s - %s" % (item, headers[item]))

		#print("%s - %s" % (item, headers[item]))

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
