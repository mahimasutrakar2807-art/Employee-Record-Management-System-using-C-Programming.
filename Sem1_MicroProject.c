//          -: MICRO PROJECT :-
// Employee Record Management System.
// Language: C
// Micro Project by [Anjali Ahirwar  , Enroll.no. BTCS25O1018]
//         And      [ Mahima Sutrakar , Enroll.no. BTCS25O1077]
// 1st Semester.
// CSE Department.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store employee details
struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

// Function declarations
void addEmployee();
void displayEmployees();
void searchEmployee();
void updateEmployee();
void deleteEmployee();

int main() {
    int choice;

    while (1) {
        printf("\n===== EMPLOYEE RECORD MANAGEMENT SYSTEM =====\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6:
                printf("👋 Exiting program... Thankyou!\n");
                exit(0);
            default:
                printf("⚠ Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to add new employee
void addEmployee() {
    struct Employee e;
    FILE *fp;

    fp = fopen("employees.data", "a+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Employee ID: ");
    scanf("%d", &e.id);
    printf("Enter Name: ");
    scanf("%s", e.name);
    printf("Enter Designation: ");
    scanf("%s", e.designation);
    printf("Enter Salary: ");
    scanf("%f", &e.salary);

    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);

    printf("✅ Employee record added successfully!\n");
}

// Function to display all employee records
void displayEmployees() {
    struct Employee e;
    FILE *fp;

    fp = fopen("employees.data", "r");
    if (fp == NULL) {
        printf("⚠ No records found!\n");
        return;
    }

    printf("\n--- Employee Records ---\n");
    while (fread(&e, sizeof(e), 1, fp)) {
        printf("ID: %d\n | Name: %s\n | Designation: %s\n | Salary: %.2f\n",
               e.id, e.name, e.designation, e.salary);
    }
    fclose(fp);
    printf("--THANKYOU--\n");
}

// Function to search employee by ID
void searchEmployee() {
    struct Employee e;
    FILE *fp;
    int id, found = 0;

    fp = fopen("employees.data", "r");
    if (fp == NULL) {
        printf("⚠ No records found!\n");
        return;
    }

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.id == id) {
            printf("🎯 Employee Found!\n");
            printf("ID: %d\n | Name: %s\n | Designation: %s\n | Salary: %.2f\n",
                   e.id, e.name, e.designation, e.salary);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("❌ Employee not found!\n");
}

// Function to delete employee record
void deleteEmployee() {
    struct Employee e;
    FILE *fp, *temp;
    int id, found = 0;

    fp = fopen("employees.data", "r");
    if (fp == NULL) {
        printf("⚠ No records found!\n");
        return;
    }

    temp = fopen("temp.data", "w");
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.id != id)
            fwrite(&e, sizeof(e), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("employees.data");
    rename("temp.data", "employees.data");

    if (found)
        printf("🗑 Record deleted successfully!\n");
    else
        printf("❌ Employee not found!\n");
}

// Function to update employee details
void updateEmployee() {
    struct Employee e;
    FILE *fp;
    int id, found = 0;
    long int pos;

    fp = fopen("employees.data", "r+");
    if (fp == NULL) {
        printf("⚠ No records found!\n");
        return;
    }

    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.id == id) {
            printf("Enter new Name: ");
            scanf("%s", e.name);
            printf("Enter new Designation: ");
            scanf("%s", e.designation);
            printf("Enter new Salary: ");
            scanf("%f", &e.salary);

            pos = ftell(fp) - sizeof(e);
            fseek(fp, pos, SEEK_SET);
            fwrite(&e, sizeof(e), 1, fp);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found)
        printf("✏ Record updated successfully!\n");
    else
        printf("❌ Employee not found!\n");
}