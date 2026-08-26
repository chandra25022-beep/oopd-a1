# Makefile for OOPD Assignment 1
# RollNo: MT25022, Name: Chandra

CXX = g++
ASM = nasm
ASMFLAGS = -f elf64
CXXFLAGS = -nostdlib

all: step2 step3 step4 step5

syscall.o: syscall.S
	$(ASM) $(ASMFLAGS) syscall.S -o syscall.o

step2: syscall.o MT25022_step2.cpp
	$(CXX) $(CXXFLAGS) MT25022_step2.cpp syscall.o -o MT25022_step2

step3: syscall.o basicIO.cpp MT25022_step3.cpp
	$(CXX) $(CXXFLAGS) MT25022_step3.cpp basicIO.cpp syscall.o -o MT25022_step3

step4: syscall.o basicIO.cpp MT25022_step4.cpp
	$(CXX) $(CXXFLAGS) MT25022_step4.cpp basicIO.cpp syscall.o -o MT25022_step4

step5: syscall.o basicIO.cpp MT25022_step5.cpp
	$(CXX) $(CXXFLAGS) MT25022_step5.cpp basicIO.cpp syscall.o -o MT25022_step5

clean:
	rm -f syscall.o MT25022_step2 MT25022_step3 MT25022_step4 MT25022_step5
