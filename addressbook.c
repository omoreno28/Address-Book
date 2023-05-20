/*
 ============================================================================
 Name        : OMorenoAddressBook
 Author      : Orion Moreno
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "addressbook.h"

void insert(AddressBook *newList, Contact *newContact, int index) {
	Contact *cur = newList->pHead;
	Contact *prev = NULL;
	if (newContact) {	// Checking if newContact was successfully created
		if (cur == NULL) {	// Inserting to blank list
			newContact->pNext = cur;
			newList->pHead = newContact;
			newContact->pPrev = NULL;
		} else {
			for (int i = 0; i < index && cur; i++) { // Cur is where we want to insert
				prev = cur;
				cur = cur->pNext;
			}
			if (cur == NULL) {	// Inserting at end of list
				prev->pNext = newContact;
				newContact->pPrev = prev;
				newContact->pNext = NULL;
			} else {
				if (cur->pPrev == NULL) {	// Inserting at beginning of list
					newList->pHead = newContact;
					cur->pPrev = newContact;
					newContact->pNext = cur;
					newContact->pPrev = NULL;
				} else {	// Inserting in middle of list
					prev->pNext = newContact;
					newContact->pPrev = prev;
					newContact->pNext = cur;
					cur->pPrev = newContact;
				}
			}
		}
	}
}

void delete(AddressBook *newList, int index) {
	if (index <= numContacts(newList) - 1) {	// Checks if index is valid
		Contact *cur = newList->pHead;
		if (numContacts(newList) == 1) {	// Just one contact in list
			free(newList->pHead);
			newList->pHead = NULL;
			return;
		}
		for (int i = 0; i < index; i++) {	// Finds the contact at the index
			cur = cur->pNext;
		}
		if (cur->pNext == NULL) {	// End of list
			cur->pPrev->pNext = NULL;
		} else if (cur->pPrev == NULL) {	// Start of list
			newList->pHead = cur->pNext;	// Resets head
			newList->pHead->pPrev = NULL;
		} else {
			Contact *temp = cur->pPrev;
			temp->pNext = cur->pNext;
			cur->pNext->pPrev = temp;
		}
		free(cur);
		cur = NULL;
		return;
	}
}

void getContact(AddressBook *newList, int index) {
	if (index <= numContacts(newList) - 1) {	// Checks if index is valid
		Contact *cur = newList->pHead;
		if (cur != NULL) {
			for (int i = 0; i < index; i++) {// Finds the contact at the index
				cur = cur->pNext;
			}
			printf("%s,%s,%s,%s\n", cur->last_name, cur->first_name, cur->email,
					cur->phone_number);

		}
	}
}
void getField(AddressBook *newList, int index, char field[255]) {
	if (index <= numContacts(newList) - 1) {	// Checks if index is valid
		Contact *cur = newList->pHead;
		for (int i = 0; i < index; i++) {	// Finds the contact at the index
			cur = cur->pNext;
		}
		if (strcmp(field, "firstName") == 0) {
			printf("%s\n", cur->first_name);
		} else if (strcmp(field, "lastName") == 0) {
			printf("%s\n", cur->last_name);
		} else if (strcmp(field, "email") == 0) {
			printf("%s\n", cur->email);
		} else if (strcmp(field, "phoneNumber") == 0) {
			printf("%s\n", cur->phone_number);
		}
	}
}

int numContacts(AddressBook *newList) {
	Contact *cur = newList->pHead;
	if (cur) {	// Return 0 if empty list
		int count = 1;
		while (cur->pNext) {
			cur = cur->pNext;
			count++;
		}
		return count;
	}
	return 0;
}

void loadFile(AddressBook *newList, char file[BUFSIZ]) {
	FILE *pIn = fopen(file, "r");
	char info[255];
	int index = numContacts(newList);
	fgets(info, 255, pIn);
	while (fgets(info, 255, pIn)) {
		int length = strlen(info) - 1;
		while (isspace(info[length])) {
			info[length] = '\0';
			length--;
		}
		insert(newList, createContact(info), index);
		index++;
	}
	fclose(pIn);
}

void saveToFile(AddressBook *newList, char file[BUFSIZ]) {
	Contact *cur = newList->pHead;
	FILE *pOut = fopen(file, "w");
	fprintf(pOut, "lastName,firstName,email,phoneNumber\n");
	while (cur) {
		fprintf(pOut, "%s,%s,%s,%s\n", cur->last_name, cur->first_name,
				cur->email, cur->phone_number);
		cur = cur->pNext;
	}
	fclose(pOut);
}

void editContact(AddressBook *newList, int index, char field[255],
		char newInfo[255]) {
	if (index <= numContacts(newList) - 1) {	// Checks if index is valid
		Contact *cur = newList->pHead;
		for (int i = 0; i < index; i++) {	// Finds the contact at the index
			cur = cur->pNext;
		}
		if (strcmp(field, "firstName") == 0) {
			strcpy(cur->first_name, newInfo);
		} else if (strcmp(field, "lastName") == 0) {
			strcpy(cur->last_name, newInfo);
		} else if (strcmp(field, "email") == 0) {
			strcpy(cur->email, newInfo);
		} else if (strcmp(field, "phoneNumber") == 0) {
			strcpy(cur->phone_number, newInfo);
		}
	}
}

void sortContacts(AddressBook *newList) {
	if (numContacts(newList) <= 1) { // Do nothing if empty or list with 1 contact
		return;
	}
	Contact *cur = newList->pHead->pNext;
	for (int i = 1; i < numContacts(newList) && cur; i++) {
		// Checks if we're at the beginning of list
		// If not, then checks if cur and cur's previous are in alphabetical order
		while (cur->pPrev && compare(cur) < 0) {
			// Swaps cur and cur's previous, meaning cur has moved up in the list
			swap(cur, newList);
		} // Continues to compare, via insertion sort, until cur's previous is lexicographically smaller, or we reach the head of the list
		cur = newList->pHead;
		for (int j = 0; j <= i; j++){
			cur = cur->pNext;
		}
	}
}
int compare(Contact *cur) {
	int cmp = strcmp(cur->last_name, cur->pPrev->last_name);
	if (cmp != 0) {
		return cmp;
	} // If we're passed this function, it means they were the same last name
	cmp = strcmp(cur->first_name, cur->pPrev->first_name);
	if (cmp != 0) {
		return cmp;
	} // Passed this one means first name's were the same
	cmp = strcmp(cur->email, cur->pPrev->email);
	if (cmp != 0) {
		return cmp;
	} // Passed this one means email's were the same
	cmp = strcmp(cur->phone_number, cur->phone_number);
	return cmp; // If 0, they have the same contact info
}
void swap(Contact *cur, AddressBook *newList) {
	Contact *prev = cur->pPrev;
	Contact *prevPrev;
	Contact *next;
	if (cur->pPrev->pPrev == NULL) { // Start of list
		next = cur->pNext;
		// Moves prev in place of cur, and sets pointers
		prev->pPrev = cur;
		prev->pNext = next;
		next->pPrev = prev;
		cur->pNext = prev;
		cur->pPrev = NULL;
		newList->pHead = cur;
	} else if (cur->pNext == NULL) { // End of list
		// Moves prev in place of cur, and sets pointers
		prevPrev = prev->pPrev;
		cur->pPrev = prevPrev;
		prevPrev->pNext = cur;
		cur->pNext = prev;
		prev->pPrev = cur;
		prev->pNext = NULL;
	} else {
		prevPrev = prev->pPrev;
		next = cur->pNext;
		// Updates pointers for moving cur up through the list
		cur->pPrev = prevPrev;
		prevPrev->pNext = cur;
		// Updates pointers between cur and prev
		cur->pNext = prev;
		prev->pPrev = cur;
		// Updates pointers for moving prev down the list
		prev->pNext = next;
		next->pPrev = prev;
	}
}

Contact* createContact(char info[255]) {
	Contact *newContact = (Contact*) malloc(sizeof(Contact));
	newContact->pPrev = NULL;
	newContact->pNext = NULL;
	char *pStart = info;
	char *pEnd;
	for (int i = 0; (i <= 3) || (*pEnd != '\0'); i++) {
		pEnd = pStart;
		while (*pEnd != ',') {
			pEnd++;
			if (*pEnd == '\0') {
				break;
			}
		}
		switch (i) {
		case 0:
			memset(newContact->last_name, '\0', 255); // memset() assure there is no garbage data in memory
			strncpy(newContact->last_name, pStart, pEnd - pStart);
			break;
		case 1:
			memset(newContact->first_name, '\0', 255);
			strncpy(newContact->first_name, pStart, pEnd - pStart);
			break;
		case 2:
			memset(newContact->email, '\0', 255);
			strncpy(newContact->email, pStart, pEnd - pStart);
			break;
		case 3:
			strncpy(newContact->phone_number, pStart, pEnd - pStart);
			break;
		default:
			break;
		}
		pStart = pEnd + 1;
	}
	return newContact;
}
