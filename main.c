#include "table_details.h"
#include "db.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	int rc;
	char *sql;
	sqlite3 *db;

	rc = sqlite3_open(argv[1], &db);
	if(rc) {
		fprintf(stderr, "sqlite err: %s\n", sqlite3_errmsg(db));
		return 0;
	} else {
		fprintf(stdout, "db opened.\n");
	}

	sql = malloc(TABLE_SQL_SIZE);
	create_table(sql);
	rc = db_exec(db, sql, 0);
	free(sql);

	FILE *f;
	f = fopen("testfiles/groupsizes.txt", "r");
	if(f == NULL) {
		perror("can't open file\n");
		return -1;
	}
	fseek(f, 0, SEEK_SET);

	unsigned char c;
	do {
		c = fgetc(f);
		if(feof(f)) {
			break;
		}
		printf("%c", c);
	} while(1);

/*
	char *buf;
	size_t sz = 0;
	while (!feof(f))
		while (getline(&buf, &sz, f) != -1)
			printf("%s", buf);
*/

	fclose(f);

	sql =
		"insert into my_table (Run, Filtered, lane, mid, c_to_g) " \
		"values (date('now'), 'No', 1, 15, 3);";
	rc = db_exec(db, sql, 0);

	sql =
		"update my_table set lane = 2345 where ID=1; ";
	rc = db_exec(db, sql, "hey");

	sql =
		"select * from my_table";
	rc = db_exec(db, sql, "hey");

	sqlite3_close(db);
	return 0;
}
