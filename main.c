/*
 ============================================================================
 Name        : OMorenoAddressBook
 Author      : Orion Moreno
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "addressbook.h"

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char buffer[255], usrInput;
	AddressBook newList;
	newList.pHead = NULL;
	puts("Ready");
	do {
		fgets(buffer, 255, stdin);
		usrInput = buffer[0];
		int index = 0, length = 0;
		char newInfo[255] = "";
		char fileName[BUFSIZ] = "";
		char editInfo[255] = "";
		switch (usrInput) {
		case 'a':
			// Add a new contact
			index = atoi(fgets(buffer, 255, stdin));
			fgets(newInfo, 255, stdin);
			length = strlen(newInfo) - 1;
			newInfo[length] = '\0';
			insert(&newList, createContact(newInfo), index);
			break;
		case 'd':
			// Delete a contact
			index = atoi(fgets(buffer, 255, stdin));
			delete(&newList, index);
			break;
		case 'g':
			// Get a contact:
			index = atoi(fgets(buffer, 255, stdin));
			getContact(&newList, index);
			break;
		case 'f':
			// Get a field
			index = atoi(fgets(buffer, 255, stdin));
			fgets(newInfo, 255, stdin);
			length = strlen(newInfo) - 1;
			newInfo[length] = '\0';
			getField(&newList, index, newInfo);
			break;
		case 'n':
			// get number of contacts
			printf("%d\n", numContacts(&newList));
			break;
		case 'l':
			// load a file
			fgets(fileName, BUFSIZ, stdin);
			length = strlen(fileName) - 1;
			fileName[length] = '\0';
			loadFile(&newList, fileName);
			break;
		case 's':
			// save contacts to a files
			fgets(fileName, BUFSIZ, stdin);
			length = strlen(fileName) - 1;
			fileName[length] = '\0';
			saveToFile(&newList, fileName);
			break;
		case 'e':
			// Edit a contact
			index = atoi(fgets(buffer, 255, stdin));
			fgets(newInfo, 255, stdin);
			length = strlen(newInfo) - 1;
			newInfo[length] = '\0';
			fgets(editInfo, 255, stdin);
			length = strlen(editInfo) - 1;
			editInfo[length] = '\0';
			editContact(&newList, index, newInfo, editInfo);
			break;
		case 'o':
			sortContacts(&newList);
			break;
		}
	} while (usrInput != 'q');

	printf("Complete\n");
	return EXIT_SUCCESS;
}
