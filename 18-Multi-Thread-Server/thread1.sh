#!/bin/bash

gcc thread1.c -g -lpthread -o thread1

if [ $? -eq 0 ]; then
    echo -e "\nNow running: \n"
    ./thread1
fi
