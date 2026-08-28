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

class Utility {
public:
    static int mystrlen(const char* str) {
        int len = 0;
        while(str[len] != '\0') len++;
        return len;
    }
};

class MemoryManager {
public:
    static void* allocate(long size) {
        long result = syscall6(SYS_MMAP, 0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (result < 0 && result > -4096) { 
            return nullptr;
        }
        return (void*)result;
    }
    
    static void deallocate(void* ptr, long size) {
        syscall6(SYS_MUNMAP, (long)ptr, size, 0, 0, 0, 0);
    }
};

class Person {
private:
    char name[256];
    char age_str[256];

    bool is_valid_age(const char* str) {
        int len = Utility::mystrlen(str);
        if (len == 0) return false;
        for (int i = 0; i < len; ++i) {
            if (str[i] < '0' || str[i] > '9') return false;
        }
        return true;
    }

    bool is_valid_name(const char* str) {
        int len = Utility::mystrlen(str);
        if (len == 0) return false;
        for (int i = 0; i < len; ++i) {
            char c = str[i];
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
                return false;
            }
        }
        return true;
    }

public:
    void read_details(int index) {
        io.outputstring("\n--- Person ");
        io.outputint(index + 1);
        io.outputstring(" ---\n");

        bool valid_name = false;
        while (!valid_name) {
            io.outputstring("Enter name (Alphabets only): ");
            io.inputstring(name, 255);
            if (is_valid_name(name)) {
                valid_name = true;
            } else {
                io.outputstring("Invalid name! Please enter letters only.\n");
            }
        }

        bool valid_age = false;
        while (!valid_age) {
            io.outputstring("Enter age (Numbers only): ");
            io.inputstring(age_str, 255);
            if (is_valid_age(age_str)) {
                valid_age = true;
            } else {
                io.outputstring("Invalid age! Please enter a valid number.\n");
            }
        }
    }

    void display_details(int index) {
        io.outputstring("Person ");
        io.outputint(index + 1);
        io.outputstring(": Name: ");
        io.outputstring(name);
        io.outputstring(", Age: ");
        io.outputstring(age_str);
        io.outputstring("\n");
    }
};

class GroupManager {
private:
    Person* people;
    int count;
    long alloc_size;

public:
    GroupManager(int num_names) {
        count = num_names;
        alloc_size = count * sizeof(Person);
        people = (Person*)MemoryManager::allocate(alloc_size);
        if (people) {
            io.outputstring("\n[System] --> GroupManager dynamically allocated memory!\n");
        } else {
            io.outputstring("\n[System] --> Memory allocation failed!\n");
        }
    }

    ~GroupManager() {
        if (people) {
            MemoryManager::deallocate(people, alloc_size);
            io.outputstring("\n[System] --> GroupManager freed dynamic memory safely!\n");
        }
    }
    
    bool is_valid() {
        return people != nullptr;
    }

    void read_all() {
        for (int i = 0; i < count; ++i) {
            people[i].read_details(i);
        }
    }

    void display_all() {
        io.outputstring("\n--- Confirmation ---\n");
        for (int i = 0; i < count; ++i) {
            people[i].display_details(i);
        }
        
        io.outputstring("\nIs this correct? (y/n): ");
        char confirm[10];
        io.inputstring(confirm, 9);
        if (confirm[0] == 'y' || confirm[0] == 'Y') {
            io.outputstring("Confirmed. Thank you!\n");
        } else {
            io.outputstring("Not confirmed.\n");
        }
    }
};

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

    {
        GroupManager gm(num_names);
        if (gm.is_valid()) {
            gm.read_all();
            gm.display_all();
        }
    } // Memory automatically freed here via RAII!

    return 0;
}
