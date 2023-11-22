#include <stdio.h>
#include <stdlib.h>

#define FILENAME "employee_records.dat"
#define MAX_NAME_LENGTH 50
struct Employee {
    int empID;
    char empName[MAX_NAME_LENGTH];
    float empSalary;
};
void addEmployee();
void displayAllEmployees();
void searchEmployee(int empID);

int main() {
    int choice;

    while (1) {
        printf("\n1. Add Employee\n2. Display All Employees\n3. Search Employee\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayAllEmployees();
                break;
            case 3: {
                int empID;
                printf("Enter employee ID to search: ");
                scanf("%d", &empID);
                searchEmployee(empID);
                break;
            }
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

void addEmployee() {
    struct Employee emp;
    FILE *file;

    file = fopen(FILENAME, "ab");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("Enter employee ID: ");
    scanf("%d", &emp.empID);
    printf("Enter employee name: ");
    scanf("%s", emp.empName);
    printf("Enter employee salary: ");
    scanf("%f", &emp.empSalary);

    fwrite(&emp, sizeof(struct Employee), 1, file);

    fclose(file);

    printf("Employee added successfully.\n");
}

void displayAllEmployees() {
    struct Employee emp;
    FILE *file;

    file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\nEmployee Records:\n");
    printf("ID\tName\tSalary\n");

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        printf("%d\t%s\t%.2f\n", emp.empID, emp.empName, emp.empSalary);
    }

    fclose(file);
}

void searchEmployee(int empID) {
    struct Employee emp;
    FILE *file;

    file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empID == empID) {
            printf("\nEmployee Found:\n");
            printf("ID\tName\tSalary\n");
            printf("%d\t%s\t%.2f\n", emp.empID, emp.empName, emp.empSalary);
            fclose(file);
            return;
        }
    }
	  fclose(file);
    printf("Employee with ID %d not found.\n", empID);
}