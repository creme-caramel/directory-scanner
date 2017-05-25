#ifndef DB_H
#define DB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

void insertdb(sqlite3 *db, int gr_a, const char *temp, const char *gr_r, const char *gr_c, const mutations *m, const mutations *hm)
{
	char *sql;
	sql = malloc(BUFF);
	strcpy(sql, "insert into my_table values (null,");

	FILE *f = fopen(temp, "r");
	fseek(f, 0, SEEK_SET);
	char *buf;
	size_t sz = 0;
	while (!feof(f))
		while (getline(&buf, &sz, f) != -1) {
			strcat(sql, "\'");
			strcat(sql, buf);
			sql[strlen(sql)-1] = '\'';
			strcat(sql, ",");
		}
	fclose(f);

	char arr[ gr_a > 0 ? (int)log10(gr_a) + 2 : 2];
	sprintf(arr, "%d", gr_a);
	strcat(sql, arr);
	strcat(sql, ",");
	strcat(sql, gr_r);
	strcat(sql, ",");
	strcat(sql, gr_c);
	strcat(sql, ",");

	int i;
	for(i = 0; i < MUTNUM; i++) {
		int num = *(((int *)m) + i);
		char arr[ num > 0 ? (int)log10(num) + 2 : 2];
		sprintf(arr, "%d", num);
		strcat(sql, arr);
		strcat(sql, ",");
	}
	for(i = 0; i < MUTNUM; i++) {
		int num = *(((int *)hm) + i);
		char arr[ num > 0 ? (int)log10(num) + 2 : 2];
		sprintf(arr, "%d", num);
		strcat(sql, arr);
		if(i < MUTNUM - 1)
			strcat(sql, ",");
	}
	strcat(sql, ");");
	//printf("%s\n", sql);

	if (exec(db, sql, "insert") != SQLITE_OK)
		printf("failed to insert into db table\n");
	free(sql);
}

#endif
