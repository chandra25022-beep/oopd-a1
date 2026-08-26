#!/bin/bash
nasm -f elf64 syscall.S -o syscall.o
g++ -nostdlib step2.cpp syscall.o -o step2
