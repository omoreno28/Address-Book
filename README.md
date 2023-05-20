# Address-Book
Written in C. The address book program receives commands from the standard input.  
The commands allow the user to add, edit, and delete contacts, as well as load or save contacts from/to a file. 
The user may also sort the contacts alphabetically.  
Each contact has a first name, last name, email address, and phone number.

Overview of Functionality:
  1. Prints "Ready\n" to the stdout.
  2. While the quit command has not been received:
    I) Receives a command from the standard input (no prompt) and executes the command.  
       Each command consists of a command code on one line, plus one or more parameters, each on a separate line.  
       Each command code is a single character.  The list of commands and associated parameters is given below:
      - Add a new contact:
        * Code:  a
        * First parameter: 0-based index where the new contact should be inserted.  0 would mean in front of the first contact in the list, 
          1 would mean in front of the second contact in the list, and so on.  This value will not be greater than the current number of contacts in the address book.
        * Second parameter: String containing a comma delimited list of contact property values.  The order is last_name, first_name, email, phone_number
      - Delete a contact:
        * Code: d
        * First parameter: 0-based index of the contact to delete.  
          NOTE: If the index is higher than the number of contacts - 1, do nothing.
      - Get a contact:
        * Code: g
        * First parameter: 0-based index of the contact
      - Get a field
        * Code: f
        * First parameter: 0-based index of the contact
        * Second parameter: Name of the field to get.  Valid values are firstName, lastName, email, phoneNumber.
        * Output to stdout: The value of the requested field, terminated with a \n.
      - Get the number of contacts in the list:
        * Code: n
        * Output to stdout: The number of contacts in the list, terminated with a \n.
      - Load a file:
        * Code: l
        * First parameter: path of the file to load.
        * NOTE: The file format is CSV.  There is one header line that describes the fields, then one contact per line thereafter.  
          The order of the contact information is the same as that of the second parameter of the add command.  
          If the address book is not empty, this command adds the loaded contacts at the end of the current list.
      - Save the contacts to a file:
        * Code: s
        * First parameter:  path of the file to save to.
        * NOTE: The file format is CSV, one contact per line.  If the file already exists, it is overwritten.
      - Edit a contact:
        * Code: e
        * First parameter:  0-based index of the contact that is to be changed.
        * Second parameter: Name of the field to edit.  Valid values are firstName, lastName, email, phoneNumber.
        * Third parameter: new value of the field.
      - Sort the contacts:
        * Code: o
        * NOTE: Sort order is ascending based on last name, then first name, then email, then phone number.
      - Quit program
        * Code: q
        * Output to stdout:  "Complete\n"

Assumptions:
  1. All fields of the contact will not exceed 255 characters
  2. Contact field values will not contain commas.




