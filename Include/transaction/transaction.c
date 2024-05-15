#include "transaction.h"
#include "../database/database.c"
#include <stdio.h>

char *query;
int variable[4];
int no_of_variables = 0;
char username[20];

int max_counter = 3;
int account_id = INIT;
int account_no = INIT;
int amount = INIT;

int response(char *header, char *opt1, char *opt2, char *opt3) {
  int counter = INIT;
  int option = EXIT;
  printf("%s\n"
         "1. %s\n"
         "2. %s\n"
         "3. %s\n",
         header, opt1, opt2, opt3);

  do {
    scanf("%d", &option);
    putchar('\n');
  } while ((++counter < max_counter) && (option != 1) && (option != 2) &&
           (option != 3));

  return option;
}

bool denomination(int amount) {
  if (amount % 100 || amount % 200 || amount % 500)
    return true;
  return false;
}

bool valid_transaction(int amount, int balance) {
    if(amount > balance) return false;
    return true;
}

bool validate() {
  printf("Enter your account number: ");
  scanf("%d", &account_no);
  putchar('\n');

  printf("Enter your account id: ");
  scanf("%d", &account_id);
  putchar('\n');

  connect_to_database();
  query = "SELECT user WHERE account_no = %d AND account_id = %d";
  variable[0] = account_no;
  variable[1] = account_id;
  no_of_variables = 2;

  bool response = database_execution(query, variable, no_of_variables, username);

  return response;
}
