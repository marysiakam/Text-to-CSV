#!/bin/bash

gcc -c main.c read_csv.c convert_to_csv.c
gcc main.o convert_to_csv.o read_csv.o


./a.out
