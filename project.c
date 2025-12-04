#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"
#define TEMP_FILE "temp.txt"

char currentRole[20];
char currentUser[20];

struct Student {
    char roll[30];
    char name[50];
    float marks;
};

// FUNCTION DECLARATIONS
void writeDefaultCredentials();
int loginSystem();
void mainMenu();
void adminMenu();
void staffMenu();
void userMenu();
void guestMenu();
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

// MAIN FUNCTION
int main() {
    writeDefaultCredentials();   // always create accounts

    if (loginSystem())
        mainMenu();
    else
        printf("\nLogin Failed. Exiting...\n");

    return 0;
}

// CREATE DEFAULT ACCOUNTS
void writeDefaultCredentials() {
    FILE *fp = fopen(CREDENTIAL_FILE, "w");
    fprintf(fp, "admin admin123 ADMIN\n");
    fprintf(fp, "staff staff123 STAFF\n");
    fprintf(fp, "user user123 USER\n");
    fprintf(fp, "guest guest123 GUEST\n");
    fclose(fp);

    FILE *s = fopen(STUDENT_FILE, "a");
    fclose(s);
}

// LOGIN SYSTEM
int loginSystem() {
    char username[20], password[20];
    char u[20], p[20], r[20];

    printf("============= Login Screen ===========\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");

    while (fscanf(fp, "%s %s %s", u, p, r) == 3) {
        if (strcmp(username, u) == 0 && strcmp(password, p) == 0) {
            strcpy(currentUser, u);
            strcpy(currentRole, r);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// MAIN MENU
void mainMenu() {
    if (strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else if (strcmp(currentRole, "USER") == 0)
        userMenu();
    else
        guestMenu();
}

// ADMIN MENU
void adminMenu() {
    int choice;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

// STAFF MENU
void staffMenu() {
    int choice;
    do {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

// USER MENU
void userMenu() {
    int choice;
    do {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

// GUEST MENU
void guestMenu() {
    printf("\nWelcome GUEST: %s\n", currentUser);
    printf("You have read-only access.\n");
    displayStudents();
}

// ADD STUDENT
void addStudent() {
    FILE *fp = fopen(STUDENT_FILE, "a");
    struct Student st;

    printf("\nEnter Roll Number: ");
    scanf("%s", st.roll);

    printf("Enter Name (no spaces): ");
    scanf("%s", st.name);

    printf("Enter Marks: ");
    scanf("%f", &st.marks);

    fprintf(fp, "%s %s %.2f\n", st.roll, st.name, st.marks);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

// DISPLAY STUDENTS
void displayStudents() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    struct Student st;

    printf("\n====== STUDENT LIST ======\n");
    while (fscanf(fp, "%s %s %f", st.roll, st.name, &st.marks) == 3) {
        printf("Roll: %s | Name: %s | Marks: %.2f\n",
               st.roll, st.name, st.marks);
    }
    fclose(fp);
}

// SEARCH STUDENT
void searchStudent() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    struct Student st;
    char r[30];
    int found = 0;

    printf("Enter Roll Number to Search: ");
    scanf("%s", r);

    while (fscanf(fp, "%s %s %f", st.roll, st.name, &st.marks) == 3) {
        if (strcmp(st.roll, r) == 0) {
            printf("\nStudent Found!\n");
            printf("Roll: %s\nName: %s\nMarks: %.2f\n",
                   st.roll, st.name, st.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

// UPDATE STUDENT
void updateStudent() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen(TEMP_FILE, "w");
    struct Student st;
    char r[30];
    int found = 0;

    printf("Enter Roll Number to Update: ");
    scanf("%s", r);

    while (fscanf(fp, "%s %s %f", st.roll, st.name, &st.marks) == 3) {
        if (strcmp(st.roll, r) == 0) {
            found = 1;
            printf("Enter New Name: ");
            scanf("%s", st.name);
            printf("Enter New Marks: ");
            scanf("%f", &st.marks);
            printf("Record Updated!\n");
        }
        fprintf(temp, "%s %s %.2f\n", st.roll, st.name, st.marks);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove(STUDENT_FILE);
        rename(TEMP_FILE, STUDENT_FILE);
    } else {
        printf("Record not found!\n");
        remove(TEMP_FILE);
    }
}

// DELETE STUDENT
void deleteStudent() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen(TEMP_FILE, "w");
    struct Student st;
    char r[30];
    int found = 0;

    printf("Enter Roll Number to Delete: ");
    scanf("%s", r);

    while (fscanf(fp, "%s %s %f", st.roll, st.name, &st.marks) == 3) {
        if (strcmp(st.roll, r) == 0) {
            found = 1;
            printf("Record Deleted!\n");
            continue;
        }
        fprintf(temp, "%s %s %.2f\n", st.roll, st.name, st.marks);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove(STUDENT_FILE);
        rename(TEMP_FILE, STUDENT_FILE);
    } else {
        printf("Record not found!\n");
        remove(TEMP_FILE);
    }
}
