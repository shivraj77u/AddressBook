#include <stdio.h>
#include "contact.h"
#include "function.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;
    addressBook.contactCount = 0;

    // Load saved contacts at startup
    loadContactsFromFile(&addressBook);

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5: {
                int sortChoice;
                printf("Sort by: 1. Name  2. Phone  3. Email\n");
                printf("Enter choice: ");
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            }
            case 6:
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("💾 Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
    return 0;
}
