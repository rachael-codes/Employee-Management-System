#include <iostream>
#include <string>
#include <limits>    
#include <algorithm> 
using namespace std;

const int MAX_EMPLOYEES = 100; // Define MAX_EMPLOYEES constant

// Structure to store employee details
struct Employee {  
    int id;
    string name;
    float salary;
    float bonus;
};

// Function prototypes
void displayMainMenu();
void addEmployee(Employee employees[], int& employeeCount); 
void viewAllEmployees(Employee employees[], int employeeCount); 
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
        cin >> choice; 

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
    cout << "1. Add new employee" << endl; 
    cout << "2. View all employees" << endl;
    cout << "3. Check total pay" << endl;
    cout << "4. Edit employee information" << endl;
    cout << "5. Delete employee" << endl;
    cout << "6. Exit" << endl; 
    cout << "\nEnter the number of your choice: ";
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

// Function to view all employees
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

// Function to Check Total Pay
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

// Function to edit an employee
void editEmployee(Employee employees[], int employeeCount) {
    if (employeeCount == 0) {
        cout << "No employees to edit." << endl;
        return;
    }

    int id;
    cout << "\nEnter the ID of the employee you want to edit: ";
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

// Function to delete an employee
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
