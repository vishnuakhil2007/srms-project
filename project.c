#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

char currentRole[20];
char currentUser[20];

struct Student
{
    int roll;
    char name[50];
    float marks;
};

// FUNCTION DECLARATIONS
void mainMenu();
void adminMenu();
void staffMenu();
void userMenu();
void guestMenu();
int loginSystem();
void addStudent();
void displayStudents();
void searchStudent();

// MAIN FUNCTION
int main()
{
    if (loginSystem())
    {
        mainMenu();
    }
    else
    {
        printf("\nLogin Failed. Exiting...\n");
    }
    return 0;
}

// LOGIN SYSTEM
int loginSystem()
{
    char username[20], password[20];
    char fileUser[20], filePass[20], fileRole[20];

    printf("============= Login Screen ===========\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp)
    {
        printf("Error: credentials.txt not found!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3)
    {
        // Remove any newline or carriage return from role
        fileRole[strcspn(fileRole, "\r\n")] = 0;

        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0)
        {
            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// MAIN MENU
void mainMenu()
{
    if (strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else if (strcmp(currentRole, "USER") == 0)
        userMenu();
    else if (strcmp(currentRole, "GUEST") == 0)
        guestMenu();
    else
        printf("Access Denied! Invalid Role.\n");
}

// ADMIN MENU
void adminMenu()
{
    int choice;
    do
    {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice!\n");
        }
    } while (1);
}

// STAFF MENU
void staffMenu()
{
    int choice;
    do
    {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayStudents();
            break;
        case 2:
            searchStudent();
            break;
        case 3:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice!\n");
        }
    } while (1);
}

// USER MENU
void userMenu()
{
    int choice;
    do
    {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayStudents();
            break;
        case 2:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice!\n");
        }
    } while (1);
}

// GUEST MENU
void guestMenu()
{
    printf("\nWelcome GUEST: %s\n", currentUser);
    printf("You have read-only access.\n");
    displayStudents();
}

// ADD STUDENT
void addStudent()
{
    FILE *fp = fopen(STUDENT_FILE, "a");
    struct Student st;

    if (!fp)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &st.roll);
    printf("Enter Name: ");
    scanf("%s", st.name);
    printf("Enter Marks: ");
    scanf("%f", &st.marks);

    fprintf(fp, "%d %s %.2f\n", st.roll, st.name, st.marks);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

// DISPLAY STUDENTS
void displayStudents()
{
    FILE *fp = fopen(STUDENT_FILE, "r");
    struct Student st;

    if (!fp)
    {
        printf("No data available.\n");
        return;
    }

    printf("\n====== STUDENT LIST ======\n");
    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) == 3)
    {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", st.roll, st.name, st.marks);
    }

    fclose(fp);
}

// SEARCH STUDENT
void searchStudent()
{
    FILE *fp = fopen(STUDENT_FILE, "r");
    struct Student st;
    int r, found = 0;

    if (!fp)
    {
        printf("No data found.\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) == 3)
    {
        if (st.roll == r)
        {
            printf("\nStudent Found!\n");
            printf("Roll: %d\nName: %s\nMarks: %.2f\n", st.roll, st.name, st.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
}