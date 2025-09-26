# AddressBook
C-based Contact Address Book enabling users to create, view, search, edit, and delete contacts with name, phone, and email. Features sorting, input validation, duplicate prevention, and file-based storage for data persistence. Efficient and user-friendly command-line utility.

A C-based command-line program to manage address book contacts efficiently. Supports creating, searching, editing, deleting contacts, and persistent data storage in a file.

Features
Add new contacts with name, phone, and email.

Search contacts by name, phone, or email.

Edit contact information and prevent duplicates.

Delete contacts securely with confirmation prompts.

List contacts, sorted by name, phone, or email.

Robust input validation to ensure correct format.

All contacts saved and loaded from contacts.txt.

File Structure
main.c: Entry point, menu handling.

contact.c, contact.h: Core contact operations and data structures.

functions.c, function.h: Validation and utility functions.

file.c, file.h: File save/load routines.

contacts.txt: Data file storing contacts persistently.

Usage Instructions
Compile:
gcc main.c contact.c functions.c file.c -o contact_manager

Run:
./contact_manager
Menu Options:

1: Create contact

2: Search contact

3: Edit contact

4: Delete contact

5: List contacts (with sort options)

6: Save contacts

7: Exit

Input Validation
Names: Only alphabets and spaces.

Phone: Exactly 10 digits, no duplicates.

Email: Valid format, no duplicate emails.

Data Persistence
Contacts are saved in contacts.txt for use across multiple sessions.

License
This project is open-source and distributed under the MIT License.
