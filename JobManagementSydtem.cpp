#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip> 
#include <windows.h>
using namespace std;
// Function Prototypes
void setColor(int c);
void printTitle();
// File Handling
void loadEmployeesFromFile();
void saveEmployeesToFile();
void loadJobsFromFile();
void saveJobsToFile();
// Admin Functions
void addEmployee();
void viewEmployees();
void deleteEmployee();
void addJob();
void viewAllJobs();
void deleteJob();
void assignJob();
void viewEmployeeDetails();
// Employee Functions
void viewMyJobs(int empID);
void viewJobDetails(int empID);
void updateJobStatus(int empID);
// Menus & Login
void adminMenu();
void employeeMenu(int id);
void loginAdmin();
void loginEmployee();
//Global variables
const int MAX_EMPLOYEES = 20; //Max Data storage for employees
const int MAX_JOBS = 50;   //Max Data storage for jobs
const string ADMIN_PASSWORD = "admin123"; //Admin pass
//variables for employees
int employeeIDs[MAX_EMPLOYEES];
string employeeNames[MAX_EMPLOYEES];
string employeePasswords[MAX_EMPLOYEES];
int employeeCount = 0;
//variables for jobs
int jobIDs[MAX_JOBS];
string jobTitles[MAX_JOBS];
string jobDescriptions[MAX_JOBS];
string jobStatuses[MAX_JOBS];
int assignedEmployeeID[MAX_JOBS];
int jobCount = 0;
int main() {
    loadEmployeesFromFile();
    loadJobsFromFile();
    int choice;
    do {
        printTitle();
        cout << "1. Admin Login\n2. Employee Login\n3. Exit\n";
        cout << "Choice: "; cin >> choice;
        switch (choice) {
            case 1: loginAdmin(); break;
            case 2: loginEmployee(); break;
            case 3: setColor(10); cout << "Goodbye!\n"; setColor(7); return 0;
            default: setColor(12); cout << "Invalid choice.\n"; setColor(7);
        }
    } while (true);
}
void setColor(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void printTitle() {
    setColor(11);
    cout << "\n=========================================\n";
    cout << "         JOB MANAGEMENT SYSTEM           \n";
    cout << "=========================================\n\n";
    setColor(7);
}

void loadEmployeesFromFile() {
    fstream file("employees.txt", ios::in);
    if (!file) return;
    string line;
    while (getline(file, line)) {
        if (line == "--- Employee ---") {
            string idLine, nameLine, passLine, sep;
            getline(file, idLine);
            getline(file, nameLine);
            getline(file, passLine);
            getline(file, sep);
            int id;
            stringstream(idLine.substr(idLine.find(": ") + 2)) >> id;
            string name = nameLine.substr(nameLine.find(": ") + 2);
            string pass = passLine.substr(passLine.find(": ") + 2);
            employeeIDs[employeeCount] = id;
            employeeNames[employeeCount] = name;
            employeePasswords[employeeCount] = pass;
            employeeCount++;
        }
    }
    file.close();
}
void loadJobsFromFile() {
    fstream file("jobs.txt", ios::in);
    if (!file) return;
    string line;
    while (getline(file, line)) {
        if (line == "--- Job ---") {
            string idLine, titleLine, descLine, statusLine, empLine, sep;
            getline(file, idLine);
            getline(file, titleLine);
            getline(file, descLine);
            getline(file, statusLine);
            getline(file, empLine);
            getline(file, sep);
            int id, emp;
            stringstream(idLine.substr(idLine.find(": ") + 2)) >> id;
            string title = titleLine.substr(titleLine.find(": ") + 2);
            string desc = descLine.substr(descLine.find(": ") + 2);
            string status = statusLine.substr(statusLine.find(": ") + 2);
            string empValue = empLine.substr(empLine.find(": ") + 2);
            if (empValue == "No one") emp = -1;
            else stringstream(empValue) >> emp;
            jobIDs[jobCount] = id;
            jobTitles[jobCount] = title;
            jobDescriptions[jobCount] = desc;
            jobStatuses[jobCount] = status;
            assignedEmployeeID[jobCount] = emp;
            jobCount++;
        }
    }
    file.close();
}

void saveEmployeesToFile() {
    fstream file("employees.txt", ios::out);
    for (int i = 0; i < employeeCount; i++) {
        file << "--- Employee ---\n";
        file << "ID: " << employeeIDs[i] << "\n";
        file << "Name: " << employeeNames[i] << "\n";
        file << "Password: " << employeePasswords[i] << "\n";
        file << "---------------\n";
    }
    file.close();
}
void saveJobsToFile() {
    fstream file("jobs.txt", ios::out);
    for (int i = 0; i < jobCount; i++) {
        file << "--- Job ---\n";
        file << "ID: " << jobIDs[i] << "\n";
        file << "Title: " << jobTitles[i] << "\n";
        file << "Description: " << jobDescriptions[i] << "\n";
        file << "Status: " << jobStatuses[i] << "\n";
        if (assignedEmployeeID[i] == -1) {
            file << "Assigned To: No one\n";
        } else {
            string empName = "Unknown";
            for (int j = 0; j < employeeCount; j++) {
                if (employeeIDs[j] == assignedEmployeeID[i]) {
                    empName = employeeNames[j];
                    break;
                }
            }
            file << "Assigned To: " << assignedEmployeeID[i] << " (" << empName << ")\n";
        }
        file << "------------\n";
    }
    file.close();
}
void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        setColor(12); cout << "Employee limit reached.\n"; setColor(7);
        return;
    }
    int id;
    cout << "Enter Employee ID (0 to cancel): ";
    cin >> id;
    if (id <= 0) return;
    for (int i = 0; i < employeeCount; i++) {
        if (employeeIDs[i] == id) {
            setColor(12); cout << "Employee ID already exists.\n"; setColor(7);
            return;
        }
    }
    cin.ignore();
    string name, pass;
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Password: ";
    getline(cin, pass);
    employeeIDs[employeeCount] = id;
    employeeNames[employeeCount] = name;
    employeePasswords[employeeCount] = pass;
    employeeCount++;
    saveEmployeesToFile();
    setColor(10); cout << "Employee added successfully.\n"; setColor(7);
}

void viewEmployees() {
    setColor(14); cout << "\n--- All Employees ---\n"; setColor(7);
    for (int i = 0; i < employeeCount; i++) {
        cout << "ID: " << employeeIDs[i] << ", Name: " << employeeNames[i] << "\n";
    }
}

void deleteEmployee() {
    int id;
    cout << "Enter Employee ID to delete (0 to cancel): ";
    cin >> id;
    if (id <= 0) return;
    for (int i = 0; i < employeeCount; i++) {
        if (employeeIDs[i] == id) {
            for (int j = i; j < employeeCount - 1; j++) {
                employeeIDs[j] = employeeIDs[j + 1];
                employeeNames[j] = employeeNames[j + 1];
                employeePasswords[j] = employeePasswords[j + 1];
            }
            employeeCount--;
            saveEmployeesToFile();
            setColor(10); cout << "Employee deleted.\n"; setColor(7);
            return;
        }
    }
    setColor(12); cout << "Employee not found.\n"; setColor(7);
}

void addJob() {
    if (jobCount >= MAX_JOBS) {
        setColor(12); cout << "Job limit reached.\n"; setColor(7);
        return;
    }
    int id;
    cout << "Enter Job ID (0 to cancel): ";
    cin >> id;
    if (id <= 0) return;
    for (int i = 0; i < jobCount; i++) {
        if (jobIDs[i] == id) {
            setColor(12); cout << "Job ID already exists.\n"; setColor(7);
            return;
        }
    }
    cin.ignore();
    string title, desc;
    cout << "Enter Job Title: ";
    getline(cin, title);
    cout << "Enter Description: ";
    getline(cin, desc);
    jobIDs[jobCount] = id;
    jobTitles[jobCount] = title;
    jobDescriptions[jobCount] = desc;
    jobStatuses[jobCount] = "Pending";
    assignedEmployeeID[jobCount] = -1;
    jobCount++;
    saveJobsToFile();
    setColor(10); cout << "Job added successfully.\n"; setColor(7);
}

void viewAllJobs() {
    setColor(11);
    cout << "\n=========================================" << endl;
    cout << "               ALL JOBS                 " << endl;
    cout << "=========================================" << endl;
    setColor(7);
    cout << left << setw(10) << "Job ID"
         << setw(25) << "Title"
         << setw(15) << "Status"
         << "Assigned To" << endl;
    cout << "---------------------------------------------------------------" << endl;
  for (int i = 0; i < jobCount; i++) 
  {
    string empName = "No one";
    if (assignedEmployeeID[i] != -1) {
        for (int j = 0; j < employeeCount; j++) {
            if (employeeIDs[j] == assignedEmployeeID[i]) {
                stringstream ss;
                ss << employeeIDs[j] << " (" << employeeNames[j] << ")";
                empName = ss.str();
                break;
            }
        }
    }
    cout << left << setw(10) << jobIDs[i]
         << setw(25) << jobTitles[i]
         << setw(15) << jobStatuses[i]
         << empName << endl;
    }
}
void deleteJob() {
    int id;
    cout << "Enter Job ID to delete (0 to cancel): ";
    cin >> id;
    if (id <= 0) return;
    for (int i = 0; i < jobCount; i++) {
        if (jobIDs[i] == id) {
            for (int j = i; j < jobCount - 1; j++) {
                jobIDs[j] = jobIDs[j + 1];
                jobTitles[j] = jobTitles[j + 1];
                jobDescriptions[j] = jobDescriptions[j + 1];
                jobStatuses[j] = jobStatuses[j + 1];
                assignedEmployeeID[j] = assignedEmployeeID[j + 1];
            }
            jobCount--;
            saveJobsToFile();
            setColor(10); cout << "Job deleted.\n"; setColor(7);
            return;
        }
    }
    setColor(12); cout << "Job not found.\n"; setColor(7);
}

void assignJob() {
    int jid, eid;
    cout << "Enter Job ID to assign (0 to cancel): ";
    cin >> jid;
    if (jid <= 0) return;
    cout << "Enter Employee ID: ";
    cin >> eid;
    if (eid <= 0) return;
    int jobIndex = -1;
    bool employeeExists = false;
    for (int i = 0; i < jobCount; i++)
        if (jobIDs[i] == jid) jobIndex = i;
    for (int i = 0; i < employeeCount; i++)
        if (employeeIDs[i] == eid) employeeExists = true;

    if (jobIndex == -1 || !employeeExists) {
        setColor(12); cout << "Invalid Job or Employee ID.\n"; setColor(7);
        return;
    }
    if (assignedEmployeeID[jobIndex] == eid) {
        setColor(12); cout << "Job already assigned to this employee.\n"; setColor(7);
        return;
    }
    assignedEmployeeID[jobIndex] = eid;
    saveJobsToFile();
    setColor(10); cout << "Job assigned successfully.\n"; setColor(7);
}
void viewMyJobs(int empID) {
    setColor(11);
    cout << "\n=========================================" << endl;
    cout << "                MY JOBS                 " << endl;
    cout << "=========================================" << endl;
    setColor(7);
    cout << left << setw(10) << "Job ID"
         << setw(25) << "Title"
         << setw(15) << "Status" << endl;
    cout << "--------------------------------------------------" << endl;
    bool found = false;
    for (int i = 0; i < jobCount; i++) {
        if (assignedEmployeeID[i] == empID) {
            cout << left << setw(10) << jobIDs[i]
                 << setw(25) << jobTitles[i]
                 << setw(15) << jobStatuses[i] << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No jobs assigned." << endl;
    }
}
void viewJobDetails(int empID) {
    int id;
    cout << "Enter Job ID to view (0 to cancel): ";
    cin >> id;
    if (id <= 0) return;
    for (int i = 0; i < jobCount; i++) {
        if (jobIDs[i] == id && assignedEmployeeID[i] == empID) {
            cout << "Title: " << jobTitles[i] << "\n";
            cout << "Description: " << jobDescriptions[i] << "\n";
            cout << "Status: " << jobStatuses[i] << "\n";
            return;
        }
    }
    setColor(12); cout << "Job not found.\n"; setColor(7);
}

void updateJobStatus(int empID) {
    int id;
    cout << "Enter Job ID to update (0 to cancel): ";
    cin >> id;
    if (id <= 0) return;
    for (int i = 0; i < jobCount; i++) {
        if (jobIDs[i] == id && assignedEmployeeID[i] == empID) {
            cin.ignore();
            cout << "Enter new status: ";
            getline(cin, jobStatuses[i]);
            saveJobsToFile();
            setColor(10); cout << "Status updated.\n"; setColor(7);
            return;
        }
    }
    setColor(12); cout << "Job not found.\n"; setColor(7);
}
void viewEmployeeDetails() {
    int id;
    cout << "Enter Employee ID to view details (0 to cancel): ";
    cin >> id;
    if (id <= 0) return;

    int index = -1;
    for (int i = 0; i < employeeCount; i++) {
        if (employeeIDs[i] == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        setColor(12);
        cout << "Employee not found." << endl;
        setColor(7);
        return;
    }
    setColor(11);
    cout << "\n=========================================" << endl;
    cout << "          EMPLOYEE DETAILS              " << endl;
    cout << "=========================================" << endl;
    setColor(7);
    cout << "ID: " << employeeIDs[index] << endl;
    cout << "Name: " << employeeNames[index] << endl;

    cout << "\nAssigned Jobs:\n";
    cout << left << setw(10) << "Job ID"
         << setw(25) << "Title"
         << setw(15) << "Status" << endl;
    cout << "--------------------------------------------------" << endl;

    bool found = false;
    for (int j = 0; j < jobCount; j++) {
        if (assignedEmployeeID[j] == employeeIDs[index]) {
            found = true;
            cout << left << setw(10) << jobIDs[j]
                 << setw(25) << jobTitles[j]
                 << setw(15) << jobStatuses[j] << endl;
        }
    }

    if (!found) {
        cout << "  No jobs assigned." << endl;
    }
}
void adminMenu() {
    int choice;
    do {
        setColor(14); cout << "\n--- Admin Menu ---\n"; setColor(7);
        cout << "1. Add Employee\n2. View All Employees\n3. Delete Employee\n";
        cout << "4. Add Job\n5. View All Jobs\n6. Assign Job\n";
        cout << "7. Delete Job\n8. Logout\n";
        cout << "8. View Employee Details\n9. Logout\n";
        cout << "Choice: "; cin >> choice;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: deleteEmployee(); break;
            case 4: addJob(); break;
            case 5: viewAllJobs(); break;
            case 6: assignJob(); break;
            case 7: deleteJob(); break;
            case 8: viewEmployeeDetails(); break;
            case 9: return;
            default: setColor(12); cout << "Invalid choice.\n"; setColor(7);
        }
    } while (true);
}

void employeeMenu(int id) {
    int choice;
    do {
        setColor(14); cout << "\n--- Employee Menu ---\n"; setColor(7);
        cout << "1. View My Jobs\n2. View Job Details\n3. Update Job Status\n4. Logout\n";
        cout << "Choice: "; cin >> choice;
        switch (choice) {
            case 1: viewMyJobs(id); break;
            case 2: viewJobDetails(id); break;
            case 3: updateJobStatus(id); break;
            case 4: return;
            default: setColor(12); cout << "Invalid choice.\n"; setColor(7);
        }
    } while (true);
}
void loginAdmin() {
    string pass;
    cout << "Enter Admin Password: ";
    cin >> pass;
    if (pass == ADMIN_PASSWORD) {
        setColor(10); cout << "Login successful.\n"; setColor(7);
        adminMenu();
    } else {
        setColor(12); cout << "Incorrect password.\n"; setColor(7);
    }
}
void loginEmployee() {
    int id;
    string pass;
    cout << "Enter Employee ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;
    for (int i = 0; i < employeeCount; i++) {
        if (employeeIDs[i] == id && employeePasswords[i] == pass) {
            setColor(10); cout << "Login successful. Welcome, " << employeeNames[i] << ".\n"; setColor(7);
            employeeMenu(id);
            return;
        }
    }
    setColor(12); cout << "Invalid credentials.\n"; setColor(7);
}


