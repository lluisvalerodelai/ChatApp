#!/bin/bash
echo "---------------------STARTING STRESS TEST---------------------"

# echo "Compiling client"
# gcc client.c -o CLIENT

for i in {1..10}
do 
  nc 127.0.0.1 42069
done

