/* Name        : K.Divya
   Date        : 13/08/2024
   Description : Address Book
*/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "file.h"

/* Function definition to save contacts*/
void saveContactsToFile(AddressBook *addressBook) 
{
    /* declaring a file pointer */
    FILE *fp;
    /* opening the file*/
    fp = fopen("contact.csv", "w");
    /*Checking if the file present or not */
    if(fp==NULL)
    {
        printf("File doesn't open");
        return;
    }
    fprintf(fp, "%c%d\n", '#',addressBook->contactCount);
    for(int i=0; i<addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

    }
    fclose(fp);
}

/* Function definition to load contacts*/
void loadContactsFromFile(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    /* declaring a file pointer */
    FILE *fp;
     /* opening the file*/
    fp = fopen("contact.csv", "r");
    /*Checking if the file present or not */
    if(fp==NULL)
    {
        printf("File doesn't open");
        return;
    }
    if(fgetc(fp) =='#')
    {
        ftell(fp);
    }
    char arr[5];
    fgets(arr,5,fp);
    int count = atoi(arr);
    for(int i=0; i<count; i++)
    {
        fscanf(fp, "%30[^,],%30[^,],%50[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    addressBook->contactCount = count;
    fclose(fp);
    
}
