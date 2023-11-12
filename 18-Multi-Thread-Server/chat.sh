#!/bin/bash

gcc chat_server.c -D_REENTRANT -g -lpthread -o serv
gcc chat_client.c -D_REENTRANT -g -lpthread -o clnt

if [ $? -eq 0 ]; then
    echo "Success... "
    echo "Then you can open two terminals as two clients to chat with each other. "
else 
    echo "Fail... "
fi
