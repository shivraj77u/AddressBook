
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "function.h"


void listContacts(AddressBook *addressBook, int sortCriteria)
{
    printf("\n========================================\n");
    printf("   📋 LISTING CONTACTS 📋\n");
    printf("========================================\n");
    switch (sortCriteria)
    {
    case 1:
        printf("🔤 Sorting contacts by Name...\n");
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            for (int j = 0; j < addressBook->contactCount - i - 1; j++)
            {
                if ((strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name)) > 0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
        print(addressBook);
        break;
    case 2:
        printf("📞 Sorting contacts by Phone Number...\n");
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            for (int j = 0; j < addressBook->contactCount - i - 1; j++)
            {
                if ((strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone)) > 0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
        print(addressBook);
        break;
    case 3:
        printf("📧 Sorting contacts by Email...\n");
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            for (int j = 0; j < addressBook->contactCount - i - 1; j++)
            {
                if ((strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email)) > 0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
        print(addressBook);
        break;
    default:
        printf("⚠  Invalid sort criteria selected.\n");
        break;
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // printf("🔄 Initializing Address Book...\n");
}

void saveAndExit(AddressBook *addressBook)
{
    printf("💾 Saving contacts and exiting the program. Goodbye!\n");
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}

void createContact(AddressBook *addressBook)
{
    char name1[100];
    char number[20];
    char mail[100];
    printf("\n========================================\n");
    printf("   ➕ ADD NEW CONTACT ➕\n");
    printf("========================================\n");
    while (1)
    {
        printf("👤 Enter Name: ");
        scanf(" %[^\n]", name1);
        if (validate(name1) == 0)
        {
            printf("❌ Invalid name! Please enter a valid name.\n");
            continue;
        }
        else
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name1);
            break;
        }
    }

    while (1)
    {
        printf("📞 Enter Phone Number: ");
        scanf("%s", number);
        if ((validphone(number) == 0) || (checkphone(addressBook, number) == 0))
        {
            printf("❌ Invalid or duplicate phone number! Please try again.\n");
            continue;
        }
        else
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone, number);
            break;
        }
    }

    while (1)
    {
        printf("📧 Enter Email: ");
        scanf("%s", mail);
        if ((!validmail(mail)) || (!checkmail(addressBook, mail)))
        {
            printf("❌ Invalid or duplicate email! Please try again.\n");
            continue;
        }
        else
        {
            strcpy(addressBook->contacts[addressBook->contactCount].email, mail);
            break;
        }
    }

    addressBook->contactCount++;
    printf("✅ Contact added successfully!\n\n");
}

void searchContact(AddressBook *addressBook)
{
    int num;
    char name2[20];
    char number2[20];
    char mail2[30];
    printf("\n========================================\n");
    printf("   🔍 SEARCH CONTACT 🔍\n");
    printf("========================================\n");
    printf("Search by:\n");
    printf("  1️⃣  Name\n  2️⃣  Phone Number\n  3️⃣  Email\n");
    printf("➡  Enter your choice: ");
    scanf("%d", &num);
    switch (num)
    {
    case 1:
        int found = 0;
        while (1)
        {
            printf("Enter the name:");
            scanf(" %[^\n]", name2);

            if (validate(name2) == 0)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasestr(addressBook->contacts[i].name, name2))
            {
                if (!found) // print header only first time
                {
                    printf("\n==============================================================\n");
                    printf("                  📌 CONTACT(S) FOUND 📌\n");
                    printf("==============================================================\n");
                    printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
                    printf("--------------------------------------------------------------\n");
                    found = 1;
                }
                printf("%-5d %-20s %-15s %-30s\n",
                       i + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
            }
        }

        if (found)
            printf("==============================================================\n\n");
        else
            printf("Not found\n");
        break;

    case 2:
        found = 0;
        while (1)
        {
            printf("Enter the phone :");
            scanf(" %s", number2);
            if (validphone(number2) == 0)
            {
                continue;
            }
            else
            {
                break;
            }
        }

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, number2) == 0)
            {

                printf("\n==============================================================\n");
                printf("                  📌 CONTACT(S) FOUND 📌\n");
                printf("==============================================================\n");
                printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
                printf("--------------------------------------------------------------\n");
                printf("%-5d %-20s %-15s %-30s\n",
                       i + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                printf("==============================================================\n\n");
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("Not found\n");
        }
        break;

    case 3:
        found = 0;
        while (1)
        {
            printf("Enter the email :");
            scanf(" %s", mail2);
            if (validmail(mail2) == 0)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, mail2) == 0)
            {
                printf("\n==============================================================\n");
                printf("                  📌 CONTACT FOUND 📌\n");
                printf("==============================================================\n");
                printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
                printf("--------------------------------------------------------------\n");
                printf("%-5d %-20s %-15s %-30s\n",
                       i + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                printf("==============================================================\n\n");
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("Not found\n");
        }
        break;

    default:
        break;
    }
}

void editContact(AddressBook *addressBook)
{
    int num, num2, num3,num4,num5;
    char name3[20], number3[20], mail3[30];
    int j = 0, i = 0 , p = 0;
    int arr[50];
    int match;

    printf("\n========================================\n");
    printf("   ✏  EDIT CONTACT ✏\n");
    printf("========================================\n");
    printf("Find the contact by:\n");
    printf("  1️⃣  Name\n  2️⃣  Phone Number\n  3️⃣  Email\n");
    printf("➡  Enter your choice: ");
    scanf("%d", &num);

    switch (num)
    {
    case 1:
    {
        int k = 0, flag = 0;
        printf("🔎 Enter the name to search: ");
        scanf(" %[^\n]", name3);

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasestr(addressBook->contacts[i].name, name3))
            {
                arr[j++] = i;
                flag = 1;
                printf("\n%d. 👤 Name: %s\n   📞 Phone: %s\n   📧 Email: %s\n",
                       k + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                k++;
            }
        }

        if (flag == 0)
        {
            printf("❌ No contact found with that name.\n");
            return;
        }
        if (j > 1)
        {
            printf("👉 Multiple contacts found. Enter the number to edit: ");
            scanf("%d", &num2);
            if(num2 > j || num2 < 1){
                printf("❌ No contact found.\n");
                return ;
            }
            match = arr[num2 - 1];

        }
        else
        {
            match = arr[0];
        }
        printf("What do you want to edit?\n");
        printf("  1️⃣  Name\n  2️⃣  Phone\n  3️⃣  Email\n");
        printf("➡  Enter your choice: ");
        scanf("%d", &num3);

        switch (num3)
        {
        case 1:
            while (1)
            {
                printf("✏  Enter the new name: ");
                scanf(" %[^\n]", name3);
                if (validate(name3) == 0)
                {
                    printf("❌ Invalid name! Please try again.\n");
                    continue;
                }
                break;
            }
            strcpy(addressBook->contacts[match].name, name3);
            printf("✅ Name updated successfully!\n");
            break;

        case 2:
            while (1)
            {
                printf("✏  Enter the new phone number: ");
                scanf(" %s", number3);
                if (validphone(number3) == 0 || checkphone(addressBook, number3) == 0)
                {
                    printf("❌ Invalid or duplicate phone number! Please try again.\n");
                    continue;
                }
                break;
            }
            strcpy(addressBook->contacts[match].phone, number3);
            printf("✅ Phone number updated successfully!\n");
            break;

        case 3:
            while (1)
            {
                printf("✏  Enter the new email: ");
                scanf(" %s", mail3);
                if (validmail(mail3) == 0 || checkmail(addressBook, mail3) == 0)
                {
                    printf("❌ Invalid or duplicate email! Please try again.\n");
                    continue;
                }
                break;
            }
            strcpy(addressBook->contacts[match].email, mail3);
            printf("✅ Email updated successfully!\n");
            break;

        default:
            printf("❌ Invalid choice.\n");
            break;
        }
        break;
    }

       case 2:
    {
        int l = 0, flag = 0;
        printf("🔎 Enter the phone number to search: ");
        scanf(" %s", number3);

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasestr(addressBook->contacts[i].phone, number3))
            {
                arr[p++] = i;
                flag = 1;
                printf("\n%d. 👤 Name: %s\n   📞 Phone: %s\n   📧 Email: %s\n",
                       l + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                l++;
            }
        }

        if (flag == 0)
        {
            printf("❌ No contact found with that phone number.\n");
            return;
        }
        if (p > 1)
        {
            printf("👉 Multiple contacts found. Enter the number to edit: ");
            scanf("%d", &num2);
            if (num2 > p || num2 < 1)
            {
                printf("❌ No contact found.\n");
                return;
            }
            match = arr[num2 - 1];
        }
        else
        {
            match = arr[0];
        }

        printf("What do you want to edit?\n");
        printf("  1️⃣  Name\n  2️⃣  Phone\n  3️⃣  Email\n");
        printf("➡  Enter your choice: ");
        scanf("%d", &num3);

        switch (num3)
        {
        case 1:
            while (1)
            {
                printf("✏  Enter the new name: ");
                scanf(" %[^\n]", name3);
                if (validate(name3) == 0)
                {
                    printf("❌ Invalid name! Please try again.\n");
                    continue;
                }
                break;
            }
            strcpy(addressBook->contacts[match].name, name3);
            printf("✅ Name updated successfully!\n");
            break;

        case 2:
            while (1)
            {
                printf("✏  Enter the new phone number: ");
                scanf(" %s", number3);
                if (validphone(number3) == 0 || checkphone(addressBook, number3) == 0)
                {
                    printf("❌ Invalid or duplicate phone number! Please try again.\n");
                    continue;
                }
                break;
            }
            strcpy(addressBook->contacts[match].phone, number3);
            printf("✅ Phone number updated successfully!\n");
            break;

        case 3:
            while (1)
            {
                printf("✏  Enter the new email: ");
                scanf(" %s", mail3);
                if (validmail(mail3) == 0 || checkmail(addressBook, mail3) == 0)
                {
                    printf("❌ Invalid or duplicate email! Please try again.\n");
                    continue;
                }
                break;
            }
            strcpy(addressBook->contacts[match].email, mail3);
            printf("✅ Email updated successfully!\n");
            break;

        default:
            printf("❌ Invalid choice.\n");
            break;
        }
        break;
    }

    case 3:
    {
        int m = 0, flag = 0;
        printf("🔎 Enter the email to search: ");
        scanf(" %s", mail3);

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasestr(addressBook->contacts[i].email,mail3))
            {
                arr[m++] = i;
                flag = 1;
                printf("\n%d. 👤 Name: %s\n   📞 Phone: %s\n   📧 Email: %s\n",
                       m,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
            }
        }

        if (flag == 0)
        {
            printf("❌ No contact found with that email.\n");
            return;
        }
        if (m > 1)
        {
            int choice;
            printf("👉 Multiple contacts found. Enter the number to edit: ");
            scanf("%d",&num2);
            if (num2 > m || num2 < 1)
            {
                printf("❌ No contact found.\n");
                return;
            }
            match = arr[num2 - 1];
        }
        else
        {
            match = arr[0];
        }

        printf("What do you want to edit?\n");
        printf("  1️⃣  Name\n  2️⃣  Phone\n  3️⃣  Email\n");
        printf("➡  Enter your choice: ");
        scanf("%d", &num3);

        switch (num3)
        {
        case 1:
            while (1)
            {
                printf("✏  Enter the new name: ");
                scanf(" %[^\n]", name3);
                if (validate(name3) == 0)
                {
                    printf("❌ Invalid name! Please try again.\n");
                    continue;
                }
                break;
            }
            strcpy(addressBook->contacts[match].name, name3);
            printf("✅ Name updated successfully!\n");
            break;

        case 2:
            while (1)
            {
                printf("✏  Enter the new phone number: ");
                scanf(" %s", number3);
                if (validphone(number3) == 0 || checkphone(addressBook, number3) == 0)
                {
                    printf("❌ Invalid or duplicate phone number! Please try again.\n");
                    continue;
                }
                break;
            }
            strcpy(addressBook->contacts[match].phone, number3);
            printf("✅ Phone number updated successfully!\n");
            break;

        case 3:
            while (1)
            {
                printf("✏  Enter the new email: ");
                scanf(" %s", mail3);
                if (validmail(mail3) == 0 || checkmail(addressBook, mail3) == 0)
                {
                    printf("❌ Invalid or duplicate email! Please try again.\n");
                    continue;
                }
                break;
            }
            strcpy(addressBook->contacts[match].email, mail3);
            printf("✅ Email updated successfully!\n");
            break;

        default:
            printf("❌ Invalid choice.\n");
            break;
        }
        break;
    }

}
}

void deleteContact(AddressBook *addressBook)
{
    int num, num2;
    char name3[20], number3[20], mail3[30];
    int j = 0, i = 0;
    int arr[50];
    char ch;
    int match;

    printf("\n========================================\n");
    printf("   🗑  DELETE CONTACT 🗑\n");
    printf("========================================\n");
    printf("Find the contact by:\n");
    printf("  1️⃣  Name\n  2️⃣  Phone Number\n  3️⃣  Email\n");
    printf("➡  Enter your choice: ");
    scanf("%d", &num);

    switch (num)
    {
    case 1:
    {
        int k = 0, flag = 0;
        printf("🔎 Enter the name to search: ");
        scanf(" %[^\n]", name3);

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasestr(addressBook->contacts[i].name, name3))
            {
                arr[j++] = i;
                flag = 1;
                printf("\n%d. 👤 Name: %s\n   📞 Phone: %s\n   📧 Email: %s\n",
                       k + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                k++;
            }
        }

        if (flag == 0)
        {
            printf("❌ No contact found with that name.\n");
            return;
        }

        if (j > 1)
        {
            printf("👉 Multiple contacts found. Enter the number to delete: ");
            scanf("%d", &num2);
            match = arr[num2 - 1];
        }
        else
        {
            match = arr[0];
        }
        printf("⚠  Are you sure you want to delete this contact? (Y/N): ");
        scanf(" %c", &ch);
        if (ch == 'N' || ch == 'n')
        {
            printf("❎ Deletion cancelled.\n");
            return;
        }
        for (int i = match; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;
        printf("✅ Contact deleted successfully!\n");
        break;
    }

    case 2:
    {
        int index, flag = 0;
        printf("🔎 Enter the phone number to search: ");
        scanf(" %s", number3);

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, number3) == 0)
            {
                flag = 1;
                index = i;
            }
        }

        if (flag == 0)
        {
            printf("❌ No contact found with that phone number.\n");
            return;
        }

        printf("⚠  Are you sure you want to delete this contact? (Y/N): ");
        scanf(" %c", &ch);
        if (ch == 'N' || ch == 'n')
        {
            printf("❎ Deletion cancelled.\n");
            return;
        }
        for (int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;
        printf("✅ Contact deleted successfully!\n");
        break;
    }

    case 3:
    {
        int index, flag = 0;
        printf("🔎 Enter the email to search: ");
        scanf(" %s", mail3);

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, mail3) == 0)
            {
                flag = 1;
                index = i;
            }
        }

        if (flag == 0)
        {
            printf("❌ No contact found with that email.\n");
            return;
        }
        printf("⚠  Are you sure you want to delete this contact? (Y/N): ");
        scanf(" %c", &ch);
        if (ch == 'N' || ch == 'n')
        {
            printf("❎ Deletion cancelled.\n");
            return;
        }
        for (int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;
        printf("✅ Contact deleted successfully!\n");
        break;
    }

    default:
        break;
    }
}