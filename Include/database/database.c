#include "database.h"
#include "../sqlite3/sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rc;
char *db_file = "../Database/bank.db";
char *zErrMsg;
sqlite3 *db;
char sql[100];

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

void connect_to_database() {
  rc = sqlite3_open(db_file, &db);

  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    exit(EXIT_FAILURE);
  } else {
    fprintf(stdout, "Opened database successfully\n");
  }
}

int database_execution(char *query, int variable[], int no_of_variables, char username[]) {

  switch (no_of_variables) {
  case 0:
    strcpy(sql, query);
  case 1:
    sprintf(sql, query, variable[0]);
    break;
  case 2:
    sprintf(sql, query, variable[0], variable[1]);
    break;
  case 3:
    sprintf(sql, query, variable[0], variable[1], variable[2]);
    break;
  case 4:
    sprintf(sql, query, variable[0], username, variable[2], variable[3]);
    break;
  }

rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

return rc;
}
