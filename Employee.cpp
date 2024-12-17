#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base Class: Employee
class Employee {
protected:
    int id;
    string name;
    double salary;

public:
    Employee(int empId, string empName, double empSalary) 
        : id(empId), name(empName), salary(empSalary) {}

    virtual void displayDetails() const {
        cout << "ID: " << id << ", Name: " << name << ", Salary: $" << salary << endl;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    double getSalary() const { return salary; }

    virtual ~Employee() {} // Virtual destructor
};

// Derived Class: Manager
class Manager : public Employee {
private:
    string department;

public:
    Manager(int empId, string empName, double empSalary, string dept) 
        : Employee(empId, empName, empSalary), department(dept) {}

    void displayDetails() const override {
        cout << "ID: " << id << ", Name: " << name 
             << ", Salary: $" << salary << ", Department: " << department << endl;
    }
};

// Employee Management System Class
class EmployeeManagementSystem {
private:
    vector<Employee*> employees;

public:
    void addEmployee(Employee* emp) {
        employees.push_back(emp);
        cout << "Employee added successfully!\n";
    }

    void displayAllEmployees() const {
        if (employees.empty()) {
            cout << "No employees to display.\n";
            return;
        }
        cout << "Employee Details:\n";
        for (const auto& emp : employees) {
            emp->displayDetails();
        }
    }

    void deleteEmployeeById(int empId) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if ((*it)->getId() == empId) {
                delete *it;
                employees.erase(it);
                cout << "Employee with ID " << empId << " deleted successfully!\n";
                return;
            }
        }
        cout << "Employee with ID " << empId << " not found.\n";
    }

    ~EmployeeManagementSystem() {
        for (auto& emp : employees) {
            delete emp;
        }
        employees.clear();
    }
};

// Main Function
int main() {
    EmployeeManagementSystem ems;
    int choice;

    do {
        cout << "\n--- Employee Management System Menu ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Add Manager\n";
        cout << "3. Display All Employees\n";
        cout << "4. Delete Employee by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            string name;
            double salary;
            cout << "Enter ID, Name, Salary: ";
            cin >> id >> name >> salary;
            ems.addEmployee(new Employee(id, name, salary));
            break;
        }
        case 2: {
            int id;
            string name, dept;
            double salary;
            cout << "Enter ID, Name, Salary, Department: ";
            cin >> id >> name >> salary >> dept;
            ems.addEmployee(new Manager(id, name, salary, dept));
            break;
        }
        case 3:
            ems.displayAllEmployees();
            break;
        case 4: {
            int id;
            cout << "Enter Employee ID to delete: ";
            cin >> id;
            ems.deleteEmployeeById(id);
            break;
        }
        case 5:
            cout << "Exiting Employee Management System. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
