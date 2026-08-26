#!/bin/bash
# RollNo: MT25022, Name: Chandra
nasm -f elf64 syscall.S -o syscall.o
g++ -nostdlib MT25022_step2.cpp syscall.o -o MT25022_step2
