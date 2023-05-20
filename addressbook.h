/*
 ============================================================================
 Name        : OMorenoAddressBook
 Author      : Orion Moreno
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#ifndef ADDRESSBOOK_H_
#define ADDRESSBOOK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contact {
	char last_name[255];
	char first_name[255];
	char email[255];
	char phone_number[20];
	struct contact *pNext;
	struct contact *pPrev;
} Contact;
typedef struct {
	Contact *pHead;
} AddressBook;

void insert(AddressBook *newList, Contact *newContact, int index);
void delete(AddressBook *newList, int index);
void getContact(AddressBook *newList, int index);
void getField(AddressBook *newList, int index, char field[255]);
int numContacts(AddressBook *newList);
void loadFile(AddressBook *newList, char loadFile[BUFSIZ]);
void saveToFile(AddressBook *newList, char saveFile[BUFSIZ]);
void editContact(AddressBook *newList, int index, char field[255],
		char newInfo[255]);
void sortContacts(AddressBook *newList);
int compare(Contact *cur);
void swap(Contact *cur, AddressBook *newList);

Contact* createContact(char info[255]);

#endif /* ADDRESSBOOK_H_ */
