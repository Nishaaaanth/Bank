#ifndef DATABASE_HEADER
#define DATABASE_HEADER

void connect_to_database();
int database_execution(char* , int[], int, char[]);
static int callback(void*, int, char**, char**);

#endif
