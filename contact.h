#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void Add_Contact(AddressBook *addressBook);

void phone_number_validation(char phone1[], AddressBook *addressBook);

void email_validation(char str[], AddressBook *addressBook);

void searchfunc(int choice, AddressBook *addressBook);

void editfunc(int ch,int i,AddressBook *addressBook);

void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void Display_Contacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
