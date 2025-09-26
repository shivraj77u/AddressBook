#ifndef FUNCTION_H
#define FUNCTION_H

int validate(char *name);
int validphone(char *number);
int checkphone(AddressBook *addressBook, char *number);
int validmail(char *mail);
int checkmail(AddressBook *addressBook, char *mail);
void print(AddressBook *addressBook);

#endif
