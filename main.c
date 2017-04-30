#include "table_details.h"
#include "db.h"

int main(int argc, char **argv)
{
	int rc;
	char *sql;
	sqlite3 *db;

	rc = sqlite3_open(argv[4], &db);
	if(rc) {
		fprintf(stderr, "sqlite err: %s\n", sqlite3_errmsg(db));
		return 0;
	} else {
		fprintf(stdout, "db opened.\n");
	}

	FILE *f;
	f = fopen(argv[1], "r");
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
		//printf("%c", c);
	} while(1);

/*
	char *buf;
	size_t sz = 0;
	while (!feof(f))
		while (getline(&buf, &sz, f) != -1)
			printf("%s", buf);
*/


/*
	sql =
		"insert into my_table (Run, Filtered, lane, mid, c_to_g) " \
		"values (date('now'), 'No', 1, 15, 3);";
	rc = db_exec(db, sql, 0);

	sql =
		"update my_table set g_to_c = 2345 where ID=1; ";
	rc = db_exec(db, sql, "hey");

	sql =
		"select * from my_table"; // just for stdout
	rc = db_exec(db, sql, "hey");
*/
	fclose(f);
	sqlite3_close(db);
	return 0;
}
