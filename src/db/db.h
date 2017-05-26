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

typedef struct mutations {
	int g_to__; // offset 0
	int g_to_a; // offset 1
	int g_to_c; // offset 2
	int g_to_t; // offset 3
	int t_to__; // offset 4
	int t_to_a; // offset 5
	int t_to_c; // offset 6
	int t_to_g; // offset 7
	int c_to__; // offset 8
	int c_to_a; // offset 9
	int c_to_t; // offset 10
	int c_to_g; // offset 11
	int a_to__; // offset 12
	int a_to_t; // offset 13
	int a_to_c; // offset 14
	int a_to_g; // offset 15
	int __to_t; // offset 16
	int __to_a; // offset 17
	int __to_c; // offset 18
	int __to_g; // offset 19
	int other_; // offset 20
} mutations; 

void add(mutations *ptr, int offset, int val)
{
	*(((int *)ptr) + offset) += val;
}


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
	sql = (char *)malloc(BUFF);
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

	void *inc = (void *)"insert";
	if (exec(db, sql, inc) != SQLITE_OK)
		printf("failed to insert into db table\n");
	free(sql);
}

#endif
