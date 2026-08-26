// RollNo: MT25022, Name: Chandra
#include "basicIO.h"

// System call numbers
#define SYS_MMAP 9
#define SYS_MUNMAP 11
#define SYS_MREMAP 25

#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20
#define MREMAP_MAYMOVE 1

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

void* my_realloc(void* old_ptr, long old_size, long new_size) {
    long result = syscall6(SYS_MREMAP, (long)old_ptr, old_size, new_size, MREMAP_MAYMOVE, 0, 0);
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

int parse_int(const char* str) {
    int val = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            val = val * 10 + (str[i] - '0');
        }
    }
    return val;
}

int main() {
    char count_str[32];
    io.outputstring("Enter the number of names you need: ");
    io.inputstring(count_str, 31);
    
    int num_names = parse_int(count_str);

    if (num_names <= 0 || num_names > 1000000) {
        io.outputstring("Invalid number of names. Exiting.\n");
        return 1;
    }

    long alloc_size = num_names * sizeof(Person);
    Person* people = (Person*)my_alloc(alloc_size);

    if (!people) {
        io.outputstring("Memory allocation failed!\n");
        return 1;
    }

    // Step 5 functionality: Allow user to change the number of names
    io.outputstring("Do you want to change the number of names? (y/n): ");
    char change_confirm[10];
    io.inputstring(change_confirm, 9);

    if (change_confirm[0] == 'y' || change_confirm[0] == 'Y') {
        io.outputstring("Enter the NEW number of names you need: ");
        io.inputstring(count_str, 31);
        int new_num_names = parse_int(count_str);

        if (new_num_names <= 0 || new_num_names > 1000000) {
            io.outputstring("Invalid new number. Reverting to old number.\n");
        } else {
            long new_alloc_size = new_num_names * sizeof(Person);
            Person* new_people = (Person*)my_realloc(people, alloc_size, new_alloc_size);
            if (!new_people) {
                io.outputstring("Reallocation failed! Exiting.\n");
                return 1;
            }
            people = new_people;
            num_names = new_num_names;
            alloc_size = new_alloc_size;
            io.outputstring("Number of names successfully changed!\n");
        }
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
