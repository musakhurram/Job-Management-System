# Job-Management-System

A console-based Job Management System built in C++ for managing employees and their assigned tasks, designed for academic learning and practical application in small organizations.

---

##  Features

###  Admin
- Secure login with hardcoded password (`admin123`)
- Add, view, and delete employees
- Add, view, and delete jobs
- Assign jobs to employees
- View complete data of an employee (with assigned jobs)

### 👨‍🔧 Employee
- Login using employee ID and password
- View assigned jobs
- View job details
- Update job status (Pending, In Progress, Completed)

---

## File Handling

- Data is stored persistently in text files:
  - `employees.txt`
  - `jobs.txt`
- Files are structured in human-readable format with labeled blocks.

Example:
```txt
--- Job ---
ID: 123
Title: Website Design
Description: Create company landing page
Status: In Progress
Assigned To: 123 (xyz)
------------
