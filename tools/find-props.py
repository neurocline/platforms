#! python3
# coding=utf-8

import os
import sys

def main():
    if len(sys.argv) < 2 or not os.path.exists(sys.argv[1]):
        raise Exception("need valid paths")

    if os.path.exists(sys.argv[2]):
        found = load_props(sys.argv[2])
    else:
        found = find_files()
        save_props(found, sys.argv[2])

    # print_files(found)
    find_paths(found, "Windows Kits")

def load_props(path):
    found = []
    with open(path, "rt", encoding="utf-8") as f:
        for line in f:
            found.append(line.rstrip())
    return found

def save_props(found, path):
    with open(path, "wt", encoding="utf-8") as f:
        for entry in found:
            print("%s" % entry, file=f)

def print_files(found):
    byname = dict()
    for entry in found:
        leaf = os.path.basename(entry)
        if leaf not in byname:
            byname[leaf] = []
        byname[leaf].append(entry[:-len(leaf)-1])

    for entry in sorted(byname):
        print("%s" % entry)
        for p in byname[entry]:
            print("    %s" % p)

def find_paths(found, s):
    wk = set()
    for path in found:
        with open(path, "rt", encoding="utf-8") as f:
            for line in f:
                if line.find(s) != -1:
                    wk.add(path)
                    break

    print("Props containing Windows Kits")
    for path in sorted(wk):
        print("%s" % path)

def find_files():
    found = []
    count = 0
    dot = 0
    n = 0
    base = sys.argv[1].replace('\\', '/')

    for root, dirs, files in os.walk(base):
        #par = root.rfind("/")
        #if par == -1:
        #    par = root.rfind("\\")
        #par = root[par+1:] if par != -1 else ""

        for f in files:
            n = n + 1
            if f.lower().endswith(".props"):
                path = os.path.join(root, f)
                #print("%s" % path)
                found.append(path)
            #elif (par+"/"+f).lower() in headers:
            #    path = os.path.join(root, f)
            #    print("%s" % path)
            #    found.append(path)

            count = count + 1
            if count > 1000:
                print(".", end="", file=sys.stderr, flush=True)
                count = count - 1000
                dot = dot + 1
            if dot == 60:
                print(" (%d/%d)" % (len(found), n), file=sys.stderr, flush=True)
                dot = 0
        n = n + len(dirs)
    print("")
    return found

# -----------------------------------------------------------------------------------------------

# This is just so that we can write code in what seems reasonable rather than
# in the order Python execution needs it.
if __name__ == '__main__':
    main()
