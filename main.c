#include "Include/main.h"
#include "Include/database/database.h"
#include "Include/transaction/transaction.c"

int main() {
  int option = response("Hello, What do you want to do today?", "Transaction",
                        "Create an Account", "Exit");
  switch (option) {
  case 1:
    transaction();
    break;
  case 2:
    create_account();
    break;
  case 3:
    printf("Thanks for coming!\n");
    break;
  }
  return 0;
}

void transaction() {
  bool valid_user = validate();
  if (!valid_user)
    return;

  int option =
      response("What would you like to do", "Withdraw", "Deposit", "Balance");

  switch (option) {
  case 1:
    withdrawal();
  case 2:
    deposit();
  case 3:
    printf("%d", balance());
  }
}

void withdrawal() {
  int curr_balance = balance();

  printf("Enter the amount to withdraw (100, 200, 500 denomination): ");
  scanf("%d", &amount);

  if (!denomination(amount))
    return;

  if (!valid_transaction(amount, curr_balance))
    return;

  connect_to_database();
  query = "UPDATE user SET balance = %d WHERE account_id = %d";
  variable[0] = curr_balance - amount;
  variable[1] = account_id;
  no_of_variables = 2;

  database_execution(query, variable, no_of_variables, username);

  printf("%d", balance());
}

void deposit() {
  int curr_balance = balance();
  printf("Enter the amount to deposit (100, 200, 500 denomination): ");
  scanf("%d", &amount);
  putchar('\n');

  if (!denomination(amount))
    return;

  connect_to_database();
  query = "UPDATE user SET balance = %d WHERE account_id = %d";
  variable[0] = curr_balance + amount;
  variable[1] = account_id;
  no_of_variables = 2;

  database_execution(query, variable, no_of_variables, username);

  printf("%d", balance());
}

int balance() {
  connect_to_database();
  query = "SELECT balance FROM users WHERE account_id = %d";
  variable[0] = account_id;
  no_of_variables = 1;
  int balance = database_execution(query, variable, no_of_variables, username);

  return balance;
}

void create_account() {
  printf("Please provide your username: ");
  scanf("%s", username);
  putchar('\n');

  printf("Please provide the account ID (Password): ");
  scanf("%d", &account_id);
  putchar('\n');
  getchar();

  connect_to_database();
  query = "SELECT count(*) FROM users";
  no_of_variables = 0;
  int account_no =
      database_execution(query, variable, no_of_variables, username) + 1;

  connect_to_database();
  query = "INSERT INTO user (account_id, username, cred_id, balance) VALUES ";
  no_of_variables = 4;
  variable[0] = account_no;
  variable[2] = account_id;
  variable[3] = amount = 10000;

  database_execution(query, variable, no_of_variables, username);

  printf("account no is : %d\n", account_no);
}
