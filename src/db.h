#ifndef DB_H
#define DB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sqlite3.h>

#define BUFF 1024
#define CALL "callback"
#define MUTNUM 21	// #elements in struct mutations
#define MUTNAMELEN 24	// like "g_to_c"

static char *errmsg = 0;

static int callback(void *data, int argc, char **argv, char **azcolname)
{
	int i;
	fprintf(stderr, "%s: ", (const char *)CALL);
	for(i = 0; i < argc; i++) {
		printf("%s:%s ", azcolname[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return SQLITE_OK;
}

static int exec(sqlite3 *db, char *sql, void *msg)
{
	int rc;
	rc = sqlite3_exec(db, sql, callback, msg, &errmsg);
	if(rc) {
		fprintf(stderr, "sqlite err: %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	return rc;
}

void updatedb(sqlite3 *db, const char *id, const mutations *m, const char *prefix)
{
	char *names[MUTNUM];
	char *sql;

	int i;
	for(i = 0; i < MUTNUM; i++) {
		names[i] = malloc(MUTNAMELEN);
	}
	makenamearr(names);

	sql = malloc(BUFF);
	strcpy(sql, "update my_table set ");
	for(i = 0; i < MUTNUM; i++) {
		int num = *(((int *)m) + i);
		char arr[ num > 0 ? (int)log10(num) + 2 : 2];
		sprintf(arr, "%d", num);
		strcat(sql, prefix);
		strcat(sql, names[i]);
		strcat(sql, " = ");
		strcat(sql, arr);
		if(i < MUTNUM - 1)
			strcat(sql, ", ");
		//printf("%s%s\t%s\n", prefix, names[i], arr);
	}
	strcat(sql, " where ID=");
	strcat(sql, id);
	if (exec(db, sql, "update") != SQLITE_OK)
		printf("failed to update db table\n");
	free(sql);

	for(i = 0; i < MUTNUM; i++) {
		free(names[i]);
	}
}

#endif
