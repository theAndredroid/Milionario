recurcive_files() {
    for i in $1\.\.?* $1\.[!.]* $1*; do
        if [ -e $i ]; then
            echo $i
            if [ -d $i ]; then
                recurcive_files $i/
            fi
        fi
    done;
}

if [ ! -d build ]; then
    mkdir build
    echo mkdir build
fi

if [ ! -d build/linux ]; then
    mkdir build/linux
    echo mkdir build/linux
fi

if [ ! -d build/linux/assets ]; then
    mkdir build/linux/assets
    echo mkdir build/linux/assets
fi

for i in $(recurcive_files assets/); do
    if [ -d $i ]; then
        if [ ! -d build/linux/$i ]; then
            mkdir build/linux/$i
            echo mkdir build/linux/$i
        fi
    elif [ -f $i ]; then
        if [ ! -f build/linux/$i ] || [ $i -nt  build/linux/$i ]; then
            cp $i build/linux/$i
            echo cp $i build/linux/$i
        fi
    fi
done

if [ ! -f build/linux/milionario ] || [ src/main.c -nt  build/linux/milionario ]; then
    gcc src/main.c -o build/linux/milionario
    echo gcc src/main.c -o build/linux/milionario
fi 

if [ ! -x build/linux/milionario ]; then
    chmod u+x build/linux/milionario
    echo chmod u+x build/linux/milionario
fi