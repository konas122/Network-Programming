#!/bin/bash

gcc HttpServer.c -g -o serv

if [ $? -eq 0 ]; then
    echo "Success"
else
    echo "Fail"
fi
