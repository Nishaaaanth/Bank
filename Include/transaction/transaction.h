#include <stdbool.h>

#ifndef TRANSACTION_HEADER
#define TRANSACTION_HEADER

#define INIT 0
#define EXIT -1

int response(char*, char*, char*, char*);
bool validate();
bool denomination(int);
bool valid_transaction(int, int);

#endif
