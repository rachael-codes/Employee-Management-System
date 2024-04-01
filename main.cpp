#include <iostream>
#include <string>
#include <limits>    // Include the <limits> header for numeric_limits
#include <algorithm> // Include the <algorithm> header for max
using namespace std;

const int MAX_EMPLOYEES = 100; // Define MAX_EMPLOYEES constant

// Structure to store employee details
struct Employee {  // Employee is a structure (struct) that represents a collection of related data fields.
    int id;
    string name;
    float salary;
    float bonus;
};

// Function prototypes
void displayMainMenu();
void addEmployee(Employee employees[], int& employeeCount); // Employee employees[]: This is an array of Employee structures. The square brackets [] indicate that employees is an array. Since no size is specified inside the brackets, it means that the size of the array is not fixed and will be determined by the caller
void viewAllEmployees(Employee employees[], int employeeCount); // int& employeeCount: This is a reference to an integer (int&). The ampersand & indicates that employeeCount is a reference, which means that changes made to it inside the function will affect the original variable outside the function. This is typically used to allow a function to modify a variable passed to it.
void checkTotalPay(Employee employees[], int employeeCount);
void editEmployee(Employee employees[], int employeeCount);
void deleteEmployee(Employee employees[], int& employeeCount);

// Function that manages an employee management system, including user interaction and data manipulation

int main() {
    Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;
    bool exitProgram = false;

    while (!exitProgram) {
        displayMainMenu();

        int choice;
        cin >> choice; // cin is an object of the istream class, which is used for reading input from the standard input stream (usually the keyboard)

        switch (choice) {
            case 1:
                addEmployee(employees, employeeCount);
                break;
            case 2:
                viewAllEmployees(employees, employeeCount);
                break;
            case 3:
                checkTotalPay(employees, employeeCount);
                break;
            case 4:
            	editEmployee(employees, employeeCount);
            	break;
            case 5:
        		deleteEmployee(employees, employeeCount);
        		break;
            case 6:
                exitProgram = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}

// Function to display the main menu
void displayMainMenu() {
    cout << "\nEmployee Management System" << endl;
    cout << "1. Add new employee" << endl; // "<<": This is the insertion operator in C++. It is used to insert data into the output stream.
    cout << "2. View all employees" << endl;
    cout << "3. Check total pay" << endl;
    cout << "4. Edit employee information" << endl;
    cout << "5. Delete employee" << endl;
    cout << "6. Exit" << endl; // "endl": This is an object in C++ that represents the end of a line. When endl is inserted into the output stream, it not only inserts a newline character (\n) but also flushes the output buffer, ensuring that the text is displayed immediately.
    cout << "\nEnter your choice: ";
}

// Function to add a new employee
void addEmployee(Employee employees[], int& employeeCount) {
    if (employeeCount < MAX_EMPLOYEES) {
        int newId;
        bool idExists;

        do {
            idExists = false;
            cout << "\nEnter Employee ID: ";
            cin >> newId;

            // Check if ID already exists
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i].id == newId) {
                    idExists = true;
                    cout << "Employee ID already exists. Please enter a different ID." << endl;
                    break;
                }
            }
        } while (idExists);

        employees[employeeCount].id = newId;

        cout << "Enter Employee Name: ";
        cin.ignore();
        getline(cin, employees[employeeCount].name);

        cout << "Enter Employee Salary: ";
        while (!(cin >> employees[employeeCount].salary)) {
            cout << "Invalid input. Please enter a valid salary: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter Bonus: ";
        while (!(cin >> employees[employeeCount].bonus)) {
            cout << "Invalid input. Please enter a valid bonus: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        employeeCount++;
        cout << "Employee added successfully." << endl;
    } else {
        cout << "Cannot add more employees. Maximum limit reached." << endl;
    }
}


void viewAllEmployees(Employee employees[], int employeeCount) {
    if (employeeCount == 0) {
        cout << "No employees to display." << endl;
    } else {
        cout << "\nAll Employees:" << endl;
        for (int i = 0; i < employeeCount; i++) {
            cout << "ID: " << employees[i].id << "\tName: " << employees[i].name
                 << "\tSalary: " << employees[i].salary << "\tBonus: " << employees[i].bonus
                 << "\tTotal Pay: " << employees[i].salary + employees[i].bonus << endl;
        }
    }
}

void checkTotalPay(Employee employees[], int employeeCount) {
    if (employeeCount == 0) {
        cout << "No employees to calculate total pay." << endl;
    } else {
        int id;
        cout << "Enter Employee ID to check total pay: ";
        cin >> id;

        bool found = false;
        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].id == id) {
                cout << "Total Pay for " << employees[i].name << " is: "
                     << employees[i].salary + employees[i].bonus << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Employee with ID " << id << " not found." << endl;
        }
    }
}

void editEmployee(Employee employees[], int employeeCount) {
    if (employeeCount == 0) {
        cout << "No employees to edit." << endl;
        return;
    }

    int id;
    cout << "Enter the ID of the employee you want to edit: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            found = true;
            cout << "\nEmployee found. What would you like to edit?" << endl;
            cout << "\n1. Name" << endl;
            cout << "2. Salary" << endl;
            cout << "3. Bonus\n" << endl;
            int choice;
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "\nEnter new name: ";
                    cin.ignore();
                    getline(cin, employees[i].name);
                    cout << "Name updated successfully." << endl;
                    break;
                case 2:
                    cout << "\nEnter new salary: ";
                    cin >> employees[i].salary;
                    cout << "Salary updated successfully." << endl;
                    break;
                case 3:
                    cout << "\nEnter new bonus: ";
                    cin >> employees[i].bonus;
                    cout << "Bonus updated successfully." << endl;
                    break;
                default:
                    cout << "\nInvalid choice. No changes made." << endl;
                    break;
            }
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << id << " not found." << endl;
    }
}

void deleteEmployee(Employee employees[], int& employeeCount) {
    if (employeeCount == 0) {
        cout << "No employees to delete." << endl;
        return;
    }

    int id;
    cout << "Enter the ID of the employee you want to delete: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            // Shift elements to the left to remove the employee
            for (int j = i; j < employeeCount - 1; j++) {
                employees[j] = employees[j + 1];
            }
            employeeCount--;
            found = true;
            cout << "Employee deleted successfully." << endl;
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << id << " not found." << endl;
    }
}




//std is a namespace provided by the standard library that contains many standard functions, objects, and types. It's used to organize these elements and avoid naming conflicts with user-defined names.

//When you see std:: in C++ code, it means that the function or object being used is part of the standard library and is located within the std namespace.

//A struct is a way to define a composite data type that groups together variables of different types under a single name. It's similar to a class in object-oriented programming but with some key differences

//Void is a keyword used to indicate that a function does not return a value.
