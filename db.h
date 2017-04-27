#ifndef DB_H
#define DB_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

const char *dbfile = "table.db";
const char *call = "callback";
static char *errmsg = 0;

static int callback(void *data, int argc, char **argv, char **azcolname)
{
	int i;
	fprintf(stderr, "%s: ", (const char *)call);
	for(i = 0; i < argc; i++) {
		printf("%s:%s ", azcolname[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}


int db_exec(sqlite3 *db, char *sql, void *msg)
{
	int rc;
	rc = sqlite3_exec(db, sql, callback, msg, &errmsg);
	if(rc) {
		fprintf(stderr, "sqlite err: %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	return rc;
}

#endif /* DB_H */
