# OOPD Assignment 1 - Basic Programming Practices
**Roll Number:** MT25022
**Name:** Chandra

## Description of the Assignment
This assignment demonstrates the foundational concepts of C++ programming by building applications without the use of standard C/C++ libraries (such as `<iostream>`) or standard memory allocation functions (such as `new` or `malloc`). 

Instead of relying on high-level abstractions, the assignment requires direct interaction with the Linux kernel through system calls. We use an assembly file (`syscall.S`) to execute these low-level instructions. The assignment is divided into several steps:
1. **Step 2:** A basic C++ program that simply returns 0, compiled with flags to exclude default libraries.
2. **Step 3:** A program that utilizes system calls (`SYS_READ` and `SYS_WRITE`) wrapped in a custom `basicIO` class to ask for the user's name and age, validate the age, and ask for confirmation.
3. **Step 4:** Expanding the program to dynamically allocate memory for multiple names and ages. Because `new` is forbidden, memory is requested directly from the OS using the `SYS_MMAP` system call.
4. **Step 5:** Adding reallocation functionality to allow the user to change the number of names required. This is achieved using the `SYS_MREMAP` system call to safely resize the memory block.

## Technique of Building
The building process entirely bypasses the standard C and C++ library linkage.

1. **Assembly Compilation:** 
   The `syscall.S` file is compiled using `nasm` into a 64-bit ELF object file:
   `nasm -f elf64 syscall.S -o syscall.o`

2. **C++ Compilation:**
   The C++ files are compiled using `g++` with the `-nostdlib` flag. This critical flag instructs the compiler to NOT link the standard C runtime (`libc`) or the standard C++ libraries (`libstdc++`). 
   Because standard startup files are excluded, `syscall.S` provides the `_start` entry point which manually calls `main()` and exits using `SYS_EXIT` (syscall 60).
   `g++ -nostdlib MT25022_stepX.cpp basicIO.cpp syscall.o -o MT25022_stepX`

3. **Makefile:**
   A `Makefile` is provided to automate this build process. Running `make` will build all executables (step 2 through 5) cleanly.
