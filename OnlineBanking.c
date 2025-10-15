#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a command to clear the screen that works on both Windows and Linux/macOS
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// Structure to hold user data
struct user {
    char pn[50];
    char ac[50];
    char password[50];
    float balance;
};

int main() {
    struct user usr, usr1;
    FILE *fp;
    char filename[50], phone[50], pword[50];
    int opt, choice;
    float amount;

    // Main menu loop
    while (1) {
        system(CLEAR_SCREEN);
        printf("\nWhat do you want to do?");
        printf("\n\n1. Register an Account");
        printf("\n2. Login to an Account");
        printf("\n3. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1: // Register a new user
                system(CLEAR_SCREEN);
                printf("Enter your account number:\t");
                scanf("%s", usr.ac);
                printf("Enter your phone number:\t");
                scanf("%s", usr.pn);
                printf("Enter your new password:\t");
                scanf("%s", usr.password);
                usr.balance = 0;

                // Create a filename based on the phone number
                strcpy(filename, usr.pn);
                fp = fopen(strcat(filename, ".dat"), "wb"); // <-- FIX: Use "wb" for write binary

                if (fp == NULL) {
                    printf("\n\nError creating account. Please try again.");
                    break;
                }

                // Write the user struct to the file and check for success
                if (fwrite(&usr, sizeof(struct user), 1, fp) == 1) {
                    printf("\n\nAccount successfully created.");
                } else {
                    printf("\n\nSomething went wrong. Please try again!");
                }
                fclose(fp);
                break;

            case 2: // Login to an existing account
                system(CLEAR_SCREEN);
                printf("\nEnter your phone number:\t");
                scanf("%s", phone);
                printf("Enter your password:\t");
                scanf("%s", pword);

                // Construct filename and open in read mode
                strcpy(filename, phone);
                fp = fopen(strcat(filename, ".dat"), "rb"); // <-- FIX: Use "rb" for read binary

                if (fp == NULL) {
                    printf("\n\nAccount not registered with this phone number.");
                } else {
                    fread(&usr1, sizeof(struct user), 1, fp);
                    fclose(fp);

                    // Check if the password matches
                    if (strcmp(pword, usr1.password) == 0) {
                        printf("\n\nLogin successful!");
                        printf("\nWelcome, %s", usr1.ac);
                        
                        // Loop for logged-in user actions
                        while (1) {
                            printf("\n\n1. Check Balance");
                            printf("\n2. Deposit");
                            printf("\n3. Withdraw");
                            printf("\n4. Logout");
                            printf("\n\nEnter your choice: ");
                            scanf("%d", &choice);

                            switch (choice) {
                                case 1: // Check balance
                                    printf("\nYour current balance is Rs. %.2f", usr1.balance);
                                    break;

                                case 2: // Deposit money
                                    printf("\nEnter amount to deposit: ");
                                    scanf("%f", &amount);
                                    usr1.balance += amount;

                                    fp = fopen(filename, "wb"); // <-- FIX: Use "wb" to update the file
                                    fwrite(&usr1, sizeof(struct user), 1, fp);
                                    fclose(fp);

                                    printf("\nSuccessfully deposited Rs. %.2f", amount);
                                    printf("\nYour new balance is Rs. %.2f", usr1.balance);
                                    break;

                                case 3: // Withdraw money
                                    printf("\nEnter amount to withdraw: ");
                                    scanf("%f", &amount);

                                    if (amount > usr1.balance) {
                                        printf("\nInsufficient balance.");
                                    } else {
                                        usr1.balance -= amount;
                                        fp = fopen(filename, "wb"); // <-- FIX: Use "wb" to update the file
                                        fwrite(&usr1, sizeof(struct user), 1, fp);
                                        fclose(fp);

                                        printf("\nSuccessfully withdrew Rs. %.2f", amount);
                                        printf("\nYour new balance is Rs. %.2f", usr1.balance);
                                    }
                                    break;
                                
                                case 4: // Logout
                                    goto end_login_loop; // Exit the nested while loop

                                default:
                                    printf("\nInvalid option.");
                                    break;
                            }
                        }
                        end_login_loop:; // Label to jump to upon logout

                    } else {
                        printf("\nInvalid password.");
                    }
                }
                break;

            case 3: // Exit the program
                printf("\nThank you for using our service.\n");
                exit(0);

            default:
                printf("\nInvalid option. Please try again.");
                break;
        }

        printf("\n\nPress any key to continue...");
        // Use two getchar() calls to reliably wait for a key press
        // The first one consumes any leftover newline character from scanf
        getchar(); 
        getchar();
    }

    return 0;
}