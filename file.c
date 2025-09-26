#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

// Save contacts to text file
void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts.txt", "w");
    if (fp == NULL) {
        printf("❌ Error: Could not open file to save contacts.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
    printf("💾 Contacts saved successfully to contacts.txt!\n");
}

// Load contacts from text file
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts.txt", "r");
    if (fp == NULL) {
        printf("⚠ No saved contacts found. Starting fresh.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, "\n");

        if (name && phone && email) {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);
            strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
            strcpy(addressBook->contacts[addressBook->contactCount].email, email);
            addressBook->contactCount++;
        }
    }

    fclose(fp);
    printf("📂 Contacts loaded successfully from contacts.txt!\n");
}
