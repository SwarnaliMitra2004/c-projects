#include <stdio.h>
#include <string.h>
#include <conio.h>   // for getch()

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30

typedef struct {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

// Function declarations
void register_user();
int login_user();
void input_credentials(char* username, char* password);
void fix_fgets_input(char* str);

int main() {
    int option, user_index;

    while (1) {
        printf("\n====== User Management System ======");
        printf("\n1. Register");
        printf("\n2. Login");
        printf("\n3. Exit");
        printf("\nSelect an option: ");
        scanf("%d", &option);
        getchar();  // consume newline

        switch (option) {
            case 1:
                register_user();
                break;

            case 2:
                user_index = login_user();
                if (user_index >= 0) {
                    printf("\nLogin successful! Welcome, %s\n",
                           users[user_index].username);
                } else {
                    printf("\nLogin failed! Invalid username or password.\n");
                }
                break;

            case 3:
                printf("\nExiting program.\n");
                return 0;

            default:
                printf("\nInvalid option. Try again.\n");
        }
    }
}

// Register a new user 
void register_user() {
    if (user_count == MAX_USERS) {
        printf("\nMaximum %d users allowed!\n", MAX_USERS);
        return;
    }

    printf("\n--- Register New User ---");
    input_credentials(users[user_count].username,
                      users[user_count].password);

    // Check for duplicate username
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username,
                   users[user_count].username) == 0) {
            printf("\nUsername already exists!\n");
            return;
        }
    }

    user_count++;
    printf("\nRegistration successful!\n");
}

// Login user
int login_user() {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    printf("\n--- Login ---");
    input_credentials(username, password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            return i;
        }
    }
    return -1;
}

// Input username and masked password (Windows) 
void input_credentials(char* username, char* password) {
    printf("\nEnter username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);

    printf("Enter password: ");
    char ch;
    int i = 0;

    while ((ch = getch()) != '\r') {   // Enter key
        if (ch == '\b' && i > 0) {     // Backspace
            i--;
            printf("\b \b");
        } else if (i < CREDENTIAL_LENGTH - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

// Remove newline from fgets
void fix_fgets_input(char* str) {
    int index = strcspn(str, "\n");
    str[index] = '\0';
}
