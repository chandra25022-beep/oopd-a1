#!/bin/bash
nasm -f elf64 syscall.S -o syscall.o
g++ -nostdlib step3.cpp basicIO.cpp syscall.o -o step3
