!#/bin/bash

mkdir -p bin

if [ $# -eq 1]; then
    if [ $1 == "-c" ]; then
        rm -rf test/*.enc
        exit 0
    elif [$1 == "-bc"]; then
        rm -rf bin
    fi
fi

gcc -o bin/cread cread.c aes.c

if [ $? -eq 0 ]; then
    echo "Build successful"
else
    echo "Build failed"
fi
