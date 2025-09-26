#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "function.h"

// Validate name (alphabets and spaces only)
int validate(char *name1) {
    int i = 0;
    while (name1[i]) {
        if (isalpha(name1[i]) || name1[i] == ' ')
            i++;
        else
            return 0;
    }
    return 1;
}

// Validate phone number (10 digits)
int validphone(char *number) {
    if (strlen(number) != 10) return 0;
    for (int i = 0; number[i]; i++) {
        if (!isdigit(number[i])) return 0;
    }
    return 1;
}

// Check duplicate phone number
int checkphone(AddressBook *addressBook, char *number) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, number) == 0)
            return 0;
    }
    return 1;
}

// Validate email
int validmail(char *mail) {
    int len = strlen(mail);
    if (len <= 5) return 0;

    // must contain exactly one '@'
    char *at = strchr(mail, '@');
    if (!at) return 0;                  
    if (strchr(at + 1, '@')) return 0; 
    if (at == mail) return 0;           // cannot start with @

    // domain cannot start with '.'
    if (*(at + 1) == '.') return 0;

    // email cannot start with '.'
    if (mail[0] == '.') return 0;

    // must contain at least one '.'
    char *dot = strrchr(mail, '.');
    if (!dot) return 0;
    if (dot < at) return 0;             // dot must be after @
    if (*(dot + 1) == '\0') return 0;   // cannot end with .

    // check for multiple consecutive dots
    for (int i = 0; i < len - 1; i++) {
        if (mail[i] == '.' && mail[i + 1] == '.')
            return 0;  // ".." not allowed
    }

    // check duplicate ".com.com", ".in.in", ".xyz.xyz"
    for (int i = 0; i < len - 1; i++) {
        if (mail[i] == '.' && mail[i+1] != '\0') {
            char *nextdot = strchr(mail + i + 1, '.');
            if (nextdot && strncmp(mail + i, nextdot, strlen(nextdot)) == 0)
                return 0; 
        }
    }

    // allowed characters: lowercase, digits, '@', '.', '_', '-'
    for (int i = 0; i < len; i++) {
        char c = mail[i];
        if (!(islower(c) || isdigit(c) || c == '@' || c == '.' || c == '_' || c == '-'))
            return 0;
    }

    return 1;  // valid
}


// Check duplicate email
int checkmail(AddressBook *addressBook, char *mail) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, mail) == 0)
            return 0;
    }
    return 1;
}

// Print all contacts
void print(AddressBook *addressBook) {
    printf("\n==============================================================\n");
    printf("                        📒 CONTACT LIST 📒                   \n");
    printf("==============================================================\n");

    if (addressBook->contactCount == 0) {
        printf("No contacts available.\n");
        printf("==============================================================\n\n");
        return;
    }

    printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%-5d %-20s %-15s %-30s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("==============================================================\n\n");
}
