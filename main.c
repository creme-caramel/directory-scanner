#include "table_details.h"
#include "db.h"
#include <stdlib.h>

int main()
{
	int rc;
	char *sql;
	sqlite3 *db;

	rc = sqlite3_open(dbfile, &db);
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
	char *buf;
	size_t sz = 0;
	f = fopen("testfiles/file2.txt", "r");
	fseek(f, 0, SEEK_SET);
	while (!feof(f))
		while (getline(&buf, &sz, f) != -1)
			printf("%s", buf);
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
