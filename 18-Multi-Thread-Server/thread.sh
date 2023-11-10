#!/bin/bash

gcc thread1.c -D_REENTRANT -g -lpthread -o tr1
gcc thread2.c -D_REENTRANT -g -lpthread -o tr2
gcc thread3.c -D_REENTRANT -g -lpthread -o tr3

if [ $? -ne 0 ]; then
    echo -e "\nfail! \n"
else
    echo -e "\nSuccess! \n"
fi
