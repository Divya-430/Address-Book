/* Name        : K.Divya
   Date        : 13/08/2024
   Description : Address Book
*/
#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Add contact\n");
        printf("2. Edit contact\n");
        printf("3. Search contact\n");
        printf("4. Delete contact\n");
        printf("5. Display contacts\n");
        printf("6. Save contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) 
        {
            case 1:
            /* Function call to add contact */
                Add_Contact(&addressBook);
                break;
            case 2:
            /* Function call to edit contact */
                editContact(&addressBook);
                break;
            case 3:
            /* Function call to search contact */
                searchContact(&addressBook);
                break;
            case 4:
            /* Function call to delete contact */
                deleteContact(&addressBook);
                break;
            case 5:
            /* Function call to display contacts */
                Display_Contacts(&addressBook);
                break;
            case 6:
            /* Function call to save contacts to file */
                saveContactsToFile(&addressBook);
                break;
            case 7:
                 printf("Saving and Exiting...\n");
                 break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
       return 0;
}
