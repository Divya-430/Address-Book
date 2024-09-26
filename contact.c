/* Name        : K.Divya
   Date        : 13/08/2024
   Description : Address Book
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

/*  Function defination for validation of mobile number */
void phone_number_validation(char phone1[], AddressBook *addressBook)
{
    if (strlen(phone1) == 10)
    {
        for (int i = 0; phone1[i] != '\0'; i++)
        {
            /*-- Validation 2 - Phone number should be b/w 0 to 9 digits --*/
            if (phone1[i] >= '0' && phone1[i] <= '9')
            {
                continue;
            }
            else
            {
                printf("Invalid number\n");
                printf("Enter the mobile number: ");
                scanf("%s", phone1);
                phone_number_validation(phone1, addressBook);
            }
        }
        /* validation 3 : for number already existed or not */
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, phone1) == 0)
            {
                printf("Phone number already existed\n");
                printf("Enter the mobile number: ");
                scanf("%s", phone1);
                phone_number_validation(phone1, addressBook);
            }
        }
    }
    else
    {
        printf("Invalid number\n");
        printf("Enter the mobile number: ");
        scanf("%s", phone1);
        phone_number_validation(phone1, addressBook);
    }
}

/*  Function defination for validation of mobile number */
void email_validation(char str[], AddressBook *addressBook)
{
    int flag = 0;
    char str2[5] = ".com";
    /* validation 1: if @ symbol present or not */
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '@')
        {
            flag++;
            break;
        }
    }
    /* validation 2: if .com is present in the email or not  */
    if (strstr(str, str2))
    {
        flag++;
    }

    if (flag == 2)
    {

        strcpy(addressBook->contacts[addressBook->contactCount].email, str);
    }
    else
    {
        printf("Invalid email\n");
        printf("Enter a valid email: ");
        scanf("%s", str);
        getchar();
        email_validation(str, addressBook);
    }
}

/* function defination for edit function */
void editfunc(int ch, int i, AddressBook *addressBook)
{
    switch (ch)
    {
    case 1:
        char name3[50];
        printf("Enter new name: ");
        scanf("%[^\n]", name3);
        getchar();
        strcpy(addressBook->contacts[i].name, name3);
        break;
    case 2:
        char phone2[50];
        printf("Enter new Mobile Number:");
        scanf("%[^\n]", phone2);
        getchar();
        phone_number_validation(phone2, addressBook);
        strcpy(addressBook->contacts[i].phone, phone2);
        break;
    case 3:
        char email2[50];
        printf("Enter new Email ID:");
        scanf("%[^\n]", email2);
        getchar();
        email_validation(email2, addressBook);
        strcpy(addressBook->contacts[i].email, email2);
        break;
    default:
        printf("Invalid choice");
    }
}

/* Function defination for displaying contacts */
void Display_Contacts(AddressBook *addressBook)
{
    printf("Name\t\t\tMobile Number\t\t\tEmail Id\n");
    for (int i = 0; i < addressBook->contactCount; ++i)
    {
        printf("%-20s\t", addressBook->contacts[i].name);
        printf("%-20s\t", addressBook->contacts[i].phone);
        printf("%-20s\t", addressBook->contacts[i].email);
        printf("\n");
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

/* Function defination for adding contacts */
void Add_Contact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */

    /* Read the contact name from user*/
    char ptr[50];
    printf("Enter the name: ");
    scanf("%[^\n]", ptr);
    getchar();

    /*read phone number from user*/
    char phone1[11];
    printf("Enter the mobile number: ");
    scanf("%s", phone1);
    /* Function call for validation of mobile number */
    phone_number_validation(phone1, addressBook);

    /*Read a gmail ID from user*/
    char str[50];
    printf("Enter the Email ID: ");
    scanf("%s", str);
    /* Function call for validation of email */
    email_validation(str, addressBook);

    /* storing name, phone and email after validation */
    strcpy(addressBook->contacts[addressBook->contactCount].name, ptr);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone1);
    addressBook->contacts[addressBook->contactCount++];
    printf("Contact Addedd succesfully.......");
}

/* Function definition for search contacts */
void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
    int choice;

    printf("Enter search choice\n1.name\n2.phone\n3.email\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        /* logic for search by name*/
        char name1[50];
        printf("Enter a name to search: ");
        getchar();
        scanf("%[^\n]", name1);
        int i;
        int flag1 = 0;
        printf("Name\t\t\tMobile Number\t\t\tEmail Id\n");
        for (i = 0; i < addressBook->contactCount; ++i)
        {
            if (strcmp(addressBook->contacts[i].name, name1) == 0)
            {
                flag1 = 1;
                printf("%-20s", addressBook->contacts[i].name);
                printf("%-20s", addressBook->contacts[i].phone);
                printf("%-20s", addressBook->contacts[i].email);
                printf("\n");
            }
        }
        if (flag1 == 0)
        {
            printf("Contact with the entered name NOT FOUND");
            return;
        }
        break;
    case 2:
        /* logic to  search by phone*/
        char phone2[10];
        printf("Enter a Contact number to search: ");
        scanf("%s", phone2);
        int j;
        int flag2 = 0;
        for (j = 0; j < addressBook->contactCount; ++j)
        {
            if (strcmp(addressBook->contacts[j].phone, phone2) == 0)
            {
                flag2 = 1;
                break;
            }
        }
        if (flag2 == 1)
        {
            printf("Name\t\t\tMobile Number\t\t\tEmail Id\n");
            printf("%-20s", addressBook->contacts[j].name);
            printf("%-20s", addressBook->contacts[j].phone);
            printf("%-20s", addressBook->contacts[j].email);
        }
        else
        {
            printf("Contact with the entered name NOT FOUND");
            return;
        }
        break;
    case 3:
        /* logic for search by email*/
        char email1[50];
        printf("Enter an email to search: ");
        scanf("%s", email1);
        int flag3 = 0;
        int k;
        printf("Name\t\t\tMobile Number\t\t\tEmail Id\n");
        for (k = 0; k < addressBook->contactCount; ++k)
        {
            if (strcmp(addressBook->contacts[k].email, email1) == 0)
            {
                flag3 = 1;
                // break;
                printf("%-20s", addressBook->contacts[k].name);
                printf("%-20s", addressBook->contacts[k].phone);
                printf("%-20s\n", addressBook->contacts[k].email);
            }
        }
        if (flag3 == 0)
        {
            printf("Contact with the entered name NOT FOUND");
            return;
        }
        break;
    default:
        printf("Invalid choice\n");
    }
    return;
}

/* Function definition for edit function */
void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */

    /* first search the contact, if it is found then edit*/
    int choice1;
    printf("1.name\n2.phone\n3.email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice1);
    getchar();
    switch (choice1)
    {
    case 1:
        /* logic to  search by name*/
        char name2[50];
        printf("Enter a name to search:");
        scanf("%[^\n]", name2);
        getchar();
        int flag4 = 0;
        int flag_1 = 0;
        int i;
        int arr[11];
        int index = 0;
        char phone_no[10];
        for (i = 0; i < addressBook->contactCount; ++i)
        {
            if (strcmp(addressBook->contacts[i].name, name2) == 0)
            {
                flag4 = 1;
                // break;
                arr[index] = i;
                index++;
                printf("%-20s", addressBook->contacts[i].name);
                printf("%-20s", addressBook->contacts[i].phone);
                printf("%-20s", addressBook->contacts[i].email);
                printf("\n");
            }
        }
        int a;
        if (index > 1)
        {
            printf("There are Duplicate names, Search with a Contact number");
            scanf("%s", phone_no);
            getchar();
            for (a = 0; a < index; ++a)
            {
                if (strcmp(addressBook->contacts[arr[a]].phone, phone_no) == 0)
                {
                    flag_1 = 1;
                    break;
                }
            }
        }
        if (flag4 && flag_1)
        {
            int ch;
            printf("1.name\n2.phone\n3.email\n");
            printf("Enter choice to edit:");
            scanf("%d", &ch);
            getchar();
            switch (ch)
            {
            case 1:
                char name3[50];
                printf("Enter new name: ");
                scanf("%[^\n]", name3);
                getchar();
                strcpy(addressBook->contacts[arr[a]].name, name3);
                break;
            case 2:
                char phone2[50];
                printf("Enter new Mobile Number:");
                scanf("%[^\n]", phone2);
                getchar();
                phone_number_validation(phone2, addressBook);
                strcpy(addressBook->contacts[arr[a]].phone, phone2);
                break;
            case 3:
                char email2[50];
                printf("Enter new Email ID:");
                scanf("%[^\n]", email2);
                getchar();
                email_validation(email2, addressBook);
                strcpy(addressBook->contacts[arr[a]].email, email2);
                break;
            default:
                printf("Invalid choice");
            }
        }
        else if (flag4 == 1)
        {
            int ch;
            printf("1.name\n2.phone\n3.email\n");
            printf("Enter choice to edit:");
            scanf("%d", &ch);
            getchar();
            editfunc(ch, arr[0], addressBook);
        }
        else
        {
            printf("Contact with the entered name NOT FOUND");
            return;
        }
        break;
    case 2:

        /* logic to  search by phone*/
        char phone3[10];
        printf("Enter a Contact number to search:");
        scanf("%s", phone3);
        getchar();
        int flag5 = 0;
        int j;
        for (j = 0; j < addressBook->contactCount; ++j)
        {
            if (strcmp(addressBook->contacts[j].phone, phone3) == 0)
            {
                flag5 = 1;
                break;
            }
        }
        if (flag5 == 1)
        {
            int ch;
            printf("Enter your choice to edit\n");
            printf("1.name\n2.phone\n3.email\n");
            scanf("%d", &ch);
            getchar();
            editfunc(ch, j, addressBook);
        }
        else
        {
            printf("Contact with the entered phone number NOT FOUND");
            return;
        }
        break;
    case 3:
        /* logic to  search by email*/
        char email2[50];
        printf("Enter an email to search: ");
        scanf("%s", email2);
        getchar();
        int flag6 = 0;
        int arr2[11];
        int index2 = 0, k;
        for (k = 0; k < addressBook->contactCount; ++k)
        {
            if (strcmp(addressBook->contacts[k].email, email2) == 0)
            {

                flag6 = 1;
                // break;
                arr2[index2] = k;
                index2++;
                printf("%-20s", addressBook->contacts[k].name);
                printf("%-20s", addressBook->contacts[k].phone);
                printf("%-20s", addressBook->contacts[k].email);
                printf("\n");
            }
        }
        char phone_no3[11];
        int d, e, flag_3 = 0;
        if (index2 > 1)
        {
            printf("There are duplicate emails.. Search by contact number");
            scanf("%s", phone_no3);
            getchar();
            for (d = 0; d < index2; d++)
            {
                e = arr2[d];
                if (strcmp(addressBook->contacts[e].phone, phone_no3) == 0)
                {
                    flag_3 = 1;
                    break;
                }
            }
        }
        if (flag6 && flag_3)
        {
            int ch;
            printf("1.name\n2.phone\n3.email\n");
            printf("Enter your choice to edit :");
            scanf("%d", &ch);
            getchar();
            editfunc(ch, arr2[0], addressBook);
        }
        else if (flag6 == 1)
        {
            int ch;
            printf("1.name\n2.phone\n3.email\n");
            printf("Enter choice to edit:");
            scanf("%d", &ch);
            getchar();
            editfunc(ch, arr2[0], addressBook);
        }
        else
        {
            printf("Contact with the entered email NOT FOUND");
            return;
        }
        break;
    default:
        printf("Invalid choice");
        return;
    }
}

/* function definition for deleting contacts */
void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    int choice;
    printf("1.name\n2.phone\n3.email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
        /* logic for search by name*/
        char name1[50];
        printf("Enter a name to search: ");
        scanf("%[^\n]", name1);
        getchar();
        int flag7 = 0, i;
        int arr1[11];
        int index1 = 0;
        for (i = 0; i < addressBook->contactCount; ++i)
        {
            if (strcmp(addressBook->contacts[i].name, name1) == 0)
            {
                flag7 = 1;
                arr1[index1] = i;
                index1++;
                printf("%-20s", addressBook->contacts[i].name);
                printf("%-20s", addressBook->contacts[i].phone);
                printf("%-20s", addressBook->contacts[i].email);
                printf("\n");
            }
        }
        int b, c;
        int flag_2 = 0;
        char phone_no2[11];
        if (index1 > 1)
        {
            printf("There are duplicate names.. Search with contact number to delete: ");
            scanf("%s", phone_no2);
            getchar();
            for (b = 0; b < index1; ++b)
            {
                c = arr1[b];
                if (strcmp(addressBook->contacts[c].phone, phone_no2) == 0)
                {
                    flag_2 = 1;
                    break;
                }
            }
        }
        if (flag7 && flag_2)
        {
            for (int j = c; j < addressBook->contactCount; ++j)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            printf("Contact Deleted Successfully......");
        }
        else if (flag7 == 1)
        {
            for (int j = arr1[0]; j < addressBook->contactCount; ++j)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            printf("Contact Deleted Successfully......");
        }
        else
        {
            printf("Contact with the entered name NOT FOUND");
            return;
        }
        break;
    case 2:
        /* logic to  search by phone*/
        char phone2[10];
        printf("Enter a Contact number to search: ");
        scanf("%s", phone2);
        getchar();
        int flag8 = 0;
        int j;
        for (j = 0; j < addressBook->contactCount; ++j)
        {
            if (strcmp(addressBook->contacts[j].phone, phone2) == 0)
            {
                flag8 = 1;
                break;
            }
        }
        if (flag8 == 1)
        {
            for (int k = j; k < addressBook->contactCount; ++k)
            {
                addressBook->contacts[k] = addressBook->contacts[k + 1];
            }
            printf("Contact Deleted Successfully......");
        }
        else
        {
            printf("Contact with the entered phone number NOT FOUND");
            return;
        }
        break;
    case 3:
        /* logic for search by email*/
        char email1[50];
        printf("Enter an email to search: ");
        scanf("%s", email1);
        getchar();
        int flag9 = 0;
        int arr2[11];
        int index2 = 0, l;
        for (l = 0; l < addressBook->contactCount; ++l)
        {
            if (strcmp(addressBook->contacts[l].email, email1) == 0)
            {
                flag9 = 1;
                arr2[index2] = l;
                index2++;
                printf("%-20s", addressBook->contacts[l].name);
                printf("%-20s", addressBook->contacts[l].phone);
                printf("%-20s", addressBook->contacts[l].email);
                printf("\n");
            }
        }
        int d, e;
        int flag_3 = 0;
        char phone_no3[11];
        if (index2 > 1)
        {
            printf("There are duplicate emails.. Search with contact number to delete: ");
            scanf("%s", phone_no3);
            getchar();
            for (d = 0; d < index2; ++d)
            {
                e = arr2[d];
                if (strcmp(addressBook->contacts[e].phone, phone_no3) == 0)
                {
                    flag_3 = 1;
                    break;
                }
            }
        }
        if (flag9 && flag_3)
        {
            for (int j = e; j < addressBook->contactCount; ++j)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            printf("Contact Deleted Successfully......");
        }
        else if (flag9 == 1)
        {
            for (int j = arr2[0]; j < addressBook->contactCount; ++j)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            printf("Contact Deleted Successfully......");
        }
        else
        {
            printf("Contact with the entered email NOT FOUND");
            return;
        }
        break;
    default:
        printf("Invalid choice");
    }
    addressBook->contacts[addressBook->contactCount--];
    return;
}
