import os
import shutil


def recurcive_files(path):
    files = []
    for i in os.listdir(path):
        if os.path.exists(path+i):
            files.append(path+i)
            if os.path.isdir(path+i):
                for j in recurcive_files(path+i+"/"):
                    files.append(j)
    return files

if not os.path.isdir("build"):
    os.mkdir("build")
    print ("mkdir build")

if not os.path.isdir("build/windows"):
    os.mkdir("build/windows")
    print ("mkdir build/windows")

if not os.path.isdir("build/windows/assets"):
    os.mkdir ("build/windows/assets")
    print ("mkdir build/windows/assets")

for i in recurcive_files ("assets/"):
    if os.path.isdir(i):
        if not os.path.isdir("build/windows/"+i):
            os.mkdir("build/windows/"+i)
            print ("build/windows/"+i)
    elif os.path.isfile(i):
        if (not os.path.isfile("build/windows/"+i) or os.stat(i).st_mtime > os.stat("build/windows/"+i).st_mtime):
            shutil.copyfile(i, "build/windows/"+i)
            print ("cp "+i+" build/windows/"+i)

if (not os.path.isfile("build/windows/milionario") or os.stat("src/main.c").st_mtime > os.stat("build/windows/milionario.exe").st_mtime):
    os.system("clang src/main.c -o build/windows/milionario.exe")
    print ("clang src/main.c -o build/windows/milionario.exe")