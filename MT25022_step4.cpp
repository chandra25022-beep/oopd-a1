// RollNo: MT25022, Name: Chandra
#include "basicIO.h"

// System call numbers
#define SYS_MMAP 9
#define SYS_MUNMAP 11

#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20

extern "C" long syscall6(long number, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

struct Person {
    char name[256];
    char age_str[256];
};

void* my_alloc(long size) {
    long result = syscall6(SYS_MMAP, 0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (result < 0 && result > -4096) { 
        return nullptr;
    }
    return (void*)result;
}

int mystrlen(const char* str) {
    int len = 0;
    while(str[len] != '\0') len++;
    return len;
}

bool is_valid_age(const char* str) {
    int len = mystrlen(str);
    if (len == 0) return false;
    for (int i = 0; i < len; ++i) {
        if (str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

int main() {
    char count_str[32];
    io.outputstring("Enter the number of names you need: ");
    io.inputstring(count_str, 31);
    
    int num_names = 0;
    for (int i = 0; count_str[i] != '\0'; ++i) {
        if (count_str[i] >= '0' && count_str[i] <= '9') {
            num_names = num_names * 10 + (count_str[i] - '0');
        }
    }

    if (num_names <= 0 || num_names > 1000000) {
        io.outputstring("Invalid number of names. Preventing overflow. Exiting.\n");
        return 1;
    }

    long alloc_size = num_names * sizeof(Person);
    Person* people = (Person*)my_alloc(alloc_size);

    if (!people) {
        io.outputstring("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < num_names; ++i) {
        io.outputstring("\n--- Person ");
        io.outputint(i + 1);
        io.outputstring(" ---\n");

        io.outputstring("Enter name: ");
        io.inputstring(people[i].name, 255);

        bool valid_age = false;
        while (!valid_age) {
            io.outputstring("Enter age (number only): ");
            io.inputstring(people[i].age_str, 255);

            if (is_valid_age(people[i].age_str)) {
                valid_age = true;
            } else {
                io.outputstring("Invalid age! Please enter a valid number.\n");
            }
        }
    }

    io.outputstring("\n--- Confirmation ---\n");
    for (int i = 0; i < num_names; ++i) {
        io.outputstring("Person ");
        io.outputint(i + 1);
        io.outputstring(": Name: ");
        io.outputstring(people[i].name);
        io.outputstring(", Age: ");
        io.outputstring(people[i].age_str);
        io.outputstring("\n");
    }
    
    io.outputstring("\nIs this correct? (y/n): ");
    char confirm[10];
    io.inputstring(confirm, 9);
    
    if (confirm[0] == 'y' || confirm[0] == 'Y') {
        io.outputstring("Confirmed. Thank you!\n");
    } else {
        io.outputstring("Not confirmed.\n");
    }

    syscall6(SYS_MUNMAP, (long)people, alloc_size, 0, 0, 0, 0);

    return 0;
}
