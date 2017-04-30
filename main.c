#include "table_details.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFF 256

int main(int argc, char **argv)
{
	char *str;
	size_t str_i;
	FILE *f;
	int rc;
	sqlite3 *db;
	cols vals;
	unsigned char c;

	// Reopen db
	rc = sqlite3_open(argv[1], &db);
	if(rc) {
		fprintf(stderr, "sqlite err: %s\n", sqlite3_errmsg(db));
		return -1;
	}

	// groupsizes.txt
	f = fopen(argv[2], "r");
	if(f == NULL) {
		perror("can't open file\n");
		return -1;
	}
	fseek(f, 0, SEEK_SET);
	int skip_punct = -6;
	int on = 0;
	if(!(str = malloc(1))) {
		fprintf(stderr, "oops can't malloc str\n");
		return -1;
	}
	vals.number_of_groups_analyzed = 0;		
	do {
		c = fgetc(f);
		if(feof(f)) {
			break;
		}
		if(c == ',') {
			skip_punct++;
			on++;
			str_i = 0;
		}
		else if(c == '\n') {
			on--;
			str[str_i] = '\0';
			vals.number_of_groups_analyzed += atoi(&str[1]);
			//printf("%s\n", &str[1]);
		}
		if(skip_punct > 0 && on) {
			str[str_i] = c;
			str_i++;
			if(!(str = realloc(str, 1))) {
				fprintf(stderr, "oops can't realloc str\n");
				return -1;
			}	
		}			
	} while(1);
	free(str);
	fclose(f);

	// output.txt
	f = fopen(argv[3], "r"); 
	if(f == NULL) {
		perror("can't open file\n");
		return -1;
	}
	fseek(f, 0, SEEK_SET);
	do {
		c = fgetc(f);
		if(feof(f)) {
			break;
		}
		//printf("%c", c);
	} while(1);
/*
	str = malloc(BUFF);
	strcpy(str, "update my_table set number_of_groups_analyzed = ");
	char temp[4];
	sprintf(temp, "%u", vals.number_of_groups_analyzed);
	strcat(str, temp);
	strcat(str, " where ID=");
	strcat(str, argv[4]);
	rc = db_exec(db, str, "update");
	free(str);
*/
	fclose(f);
	sqlite3_close(db);
	return 0;
}

