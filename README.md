# Bank System V3 (C++)

**Console-based Bank Management System in C++**  
This project is an enhanced version of previous C++ bank systems, now featuring multi-user support and access control.

---

## Features

### Client Management
- Add new clients
- Update existing clients
- Delete clients
- Find clients by account number

### Transactions Menu
- Deposit money
- Withdraw money (with balance validation)
- Show total balances of all clients

### User Management & Permissions
- Add new users
- Update user information
- Delete users (except admin)
- Find users
- Assign custom permissions for menu access

### File-Based Storage
- All client data is stored in `Clients.txt`
- All user data is stored in `Users.txt`
- Automatic loading and saving of client and user data

---

## Purpose
This project is designed to practice and improve skills in:
- C++ programming
- Object management
- File handling
- Console UI design
- User access control

---

## How to Run
1. Clone or download the repository.
2. Make sure `Clients.txt` and `Users.txt` exist in the same folder as the executable.
3. Compile the project using a C++ compiler (e.g., g++, Visual Studio).
4. Run the executable and log in using a valid username and password.
5. Navigate through the Main Menu according to your permissions.

---

## Sample Main Menu

[1] Show Client List
[2] Add New Client
[3] Delete Client
[4] Update Client Info
[5] Find Client
[6] Transactions
[7] Manage Users
[8] Logout

### Transactions Menu:

[1] Deposit
[2] Withdraw
[3] Total Balances
[4] Main Menu


### Manage Users Menu:

[1] List Users
[2] Add New User
[3] Delete User
[4] Update User
[5] Find User
[6] Main Menu

---

## File Format

**Clients.txt**  

AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance

**Example:**  

A150#//#1234#//#Abdulrahman Ramadan#//#01128663647#//#111.000000

**Users.txt**  

UserName#//#Password#//#Permissions

Admin#//#1234#//#-1

Permissions are stored as integers representing access rights.

---

## Author
**Abdulrahman Ramadan** – Third full C++ project with enhanced user management, permissions, and file handling.
