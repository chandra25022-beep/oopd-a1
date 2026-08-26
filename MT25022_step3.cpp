// RollNo: MT25022, Name: Chandra
#include "basicIO.h"

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
    char name[256];
    char age_str[256];

    io.outputstring("Enter your name: ");
    io.inputstring(name, 255);

    bool valid_age = false;
    while (!valid_age) {
        io.outputstring("Enter your age (number only): ");
        io.inputstring(age_str, 255);

        if (is_valid_age(age_str)) {
            valid_age = true;
        } else {
            io.outputstring("Invalid age! Please enter a valid number.\n");
        }
    }

    io.outputstring("You entered Name: ");
    io.outputstring(name);
    io.outputstring(", Age: ");
    io.outputstring(age_str);
    io.outputstring("\nIs this correct? (y/n): ");

    char confirm[10];
    io.inputstring(confirm, 9);
    
    if (confirm[0] == 'y' || confirm[0] == 'Y') {
        io.outputstring("Confirmed. Thank you!\n");
    } else {
        io.outputstring("Not confirmed.\n");
    }

    return 0;
}
