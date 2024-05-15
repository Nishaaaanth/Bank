#! /usr/bin/bash

if [ ! -d "./build" ]; then
    mkdir build
fi

if [ ! -f "./Database/bank.db" ]; then
    mkdir Database
    touch Database/bank.db
fi

name=main
Include="./Include/sqlite3/sqlite3.c"

clang $Include $name.c -o ./build/$name
./build/$name
