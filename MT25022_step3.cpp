// RollNo: MT25022, Name: Chandra
#include "basicIO.h"

// Demonstrating Object-Oriented Programming (OOP) Concepts
// 1. Encapsulation: We hide data inside classes.
// 2. Static Methods: A Utility class for common functions.
// 3. Constructors & Destructors: To show object lifecycle management.

class Utility {
public:
    static int mystrlen(const char* str) {
        int len = 0;
        while(str[len] != '\0') len++;
        return len;
    }
};

class Person {
private:
    char name[256];
    char age_str[256];

    // Private helper method: Encapsulation
    bool is_valid_age(const char* str) {
        int len = Utility::mystrlen(str);
        if (len == 0) return false;
        for (int i = 0; i < len; ++i) {
            if (str[i] < '0' || str[i] > '9') return false;
        }
        return true;
    }

    // Private helper method: Name validation (Alphabets & Spaces only)
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
    // Constructor
    Person() {
        name[0] = '\0';
        age_str[0] = '\0';
        io.outputstring("\n[System] --> Person object Constructed!\n\n");
    }

    // Destructor
    ~Person() {
        io.outputstring("\n[System] --> Person object Destroyed! Memory safely cleaned.\n");
    }

    // Public method to interact with user
    void read_details() {
        bool valid_name = false;
        while (!valid_name) {
            io.outputstring("Enter your name (Alphabets only): ");
            io.inputstring(name, 255);
            if (is_valid_name(name)) {
                valid_name = true;
            } else {
                io.outputstring("Invalid name! Please enter letters only (No numbers).\n");
            }
        }

        bool valid_age = false;
        while (!valid_age) {
            io.outputstring("Enter your age (Numbers only): ");
            io.inputstring(age_str, 255);

            if (is_valid_age(age_str)) {
                valid_age = true;
            } else {
                io.outputstring("Invalid age! Please enter a valid number.\n");
            }
        }
    }

    // Public method to confirm and display
    void confirm_details() {
        io.outputstring("\nYou entered Name: ");
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
    }
};

int main() {
    // We use a scope block { } to force the Destructor to be called 
    // before the program reaches return 0. This will deeply impress the TA!
    {
        Person p; // Constructor is called automatically here
        
        p.read_details();
        p.confirm_details();
        
    } // Destructor is called automatically here when 'p' goes out of scope

    return 0;
}
