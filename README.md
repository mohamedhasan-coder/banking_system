# Simple Command-Line Banking System in C

This is a basic console-based banking application written in C. It allows users to register for an account, log in, check their balance, and perform deposit and withdrawal operations. All user data is stored locally in individual binary files.

---

## Features

-   **User Account Registration**: Create a new user account with an account number, phone number, and password.
-   **User Login**: Securely log in using a phone number and password.
-   **Account Management**:
    -   Check current account balance.
    -   Deposit funds into the account.
    -   Withdraw funds, with a check for insufficient balance.
-   **Data Persistence**: Each user's account details are saved to a separate binary file (`.dat`), ensuring data is preserved between sessions.

---

## How It Works

The application uses a C `struct` to manage user data in memory. When a user registers or updates their account, this `struct` is written directly to a binary file named after the user's phone number (e.g., `1234567890.dat`). Using binary mode (`"wb"` for writing, `"rb"` for reading) prevents data corruption that can occur in text mode, ensuring data integrity.

---

## Prerequisites

To compile and run this project, you will need:
-   A C compiler, such as **GCC** (GNU Compiler Collection).

---

## How to Compile and Run

1.  **Save the Code**: Save the provided source code into a file named `main.c`.

2.  **Open a Terminal**: Navigate to the directory where you saved `main.c`.

3.  **Compile the Program**: Run the following command to compile the code. This will create an executable file named `banking_app`.
    ```bash
    gcc main.c -o banking_app
    ```

4.  **Run the Application**: Execute the compiled program with the following command:
    ```bash
    ./banking_app
    ```
    On Windows, you might just run:
    ```bash
    banking_app.exe
    ```

---

## Usage

Once the application is running, you will be presented with the main menu:

What do you want to do?

Register an Account

Login to an Account

Exit

Enter your choice:


-   **Register**: Choose `1` to create a new account. You will be prompted to enter an account number, phone number, and password.
-   **Login**: Choose `2` to log in. You will need to provide the phone number and password associated with your account.
-   **Post-Login Menu**: After a successful login, you can check your balance, deposit, or withdraw funds. All changes are saved instantly.
-   **Exit**: Choose `3` to safely exit the application.