#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

void addContact();
void viewContacts();
void searchContact();
void deleteContact();

int main() {
    int choice;

    while(1) {
        printf("\n===== ADDRESS BOOK =====\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}

void addContact() {
    FILE *fp;
    struct Contact c;

    fp = fopen("contacts.txt", "a");

    printf("Enter Name: ");
    scanf(" %[^\n]", c.name);

    printf("Enter Phone: ");
    scanf("%s", c.phone);

    printf("Enter Email: ");
    scanf("%s", c.email);

    fprintf(fp, "%s %s %s\n", c.name, c.phone, c.email);

    fclose(fp);

    printf("Contact Added Successfully!\n");
}

void viewContacts() {
    FILE *fp;
    struct Contact c;

    fp = fopen("contacts.txt", "r");

    if(fp == NULL) {
        printf("No contacts found.\n");
        return;
    }

    printf("\n--- Contact List ---\n");

    while(fscanf(fp,"%s %s %s",c.name,c.phone,c.email)!=EOF) {
        printf("Name : %s\n", c.name);
        printf("Phone: %s\n", c.phone);
        printf("Email: %s\n\n", c.email);
    }

    fclose(fp);
}

void searchContact() {
    FILE *fp;
    struct Contact c;
    char search[50];
    int found = 0;

    fp = fopen("contacts.txt","r");

    printf("Enter name to search: ");
    scanf("%s", search);

    while(fscanf(fp,"%s %s %s",c.name,c.phone,c.email)!=EOF) {
        if(strcmp(search,c.name)==0) {
            printf("\nContact Found\n");
            printf("Name : %s\n", c.name);
            printf("Phone: %s\n", c.phone);
            printf("Email: %s\n", c.email);
            found = 1;
        }
    }

    if(!found)
        printf("Contact not found.\n");

    fclose(fp);
}

void deleteContact() {
    FILE *fp, *temp;
    struct Contact c;
    char name[50];
    int found = 0;

    fp = fopen("contacts.txt","r");
    temp = fopen("temp.txt","w");

    printf("Enter name to delete: ");
    scanf("%s", name);

    while(fscanf(fp,"%s %s %s",c.name,c.phone,c.email)!=EOF) {
        if(strcmp(name,c.name)!=0) {
            fprintf(temp,"%s %s %s\n",c.name,c.phone,c.email);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("contacts.txt");
    rename("temp.txt","contacts.txt");

    if(found)
        printf("Contact deleted successfully.\n");
    else
        printf("Contact not found.\n");
}