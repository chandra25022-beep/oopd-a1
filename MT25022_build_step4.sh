#!/bin/bash
# RollNo: MT25022, Name: Chandra
nasm -f elf64 syscall.S -o syscall.o
g++ -nostdlib -fno-exceptions -fno-rtti MT25022_step4.cpp basicIO.cpp syscall.o -o MT25022_step4
