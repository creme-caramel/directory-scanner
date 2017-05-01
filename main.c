#include "table_details.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>

#define BUFF 256

int main(int argc, char **argv)
{
	//char *str;
	//size_t str_i;
	FILE *f;
	int rc;
	sqlite3 *db;
	//cols vals;
	unsigned char c;

	// Reopen db
	rc = sqlite3_open(argv[1], &db);
	if(rc) {
		fprintf(stderr, "sqlite err: %s\n", sqlite3_errmsg(db));
		return -1;
	}

	// output.txt
	f = fopen(argv[2], "r"); 
	if(f == NULL) {
		perror("can't open file\n");
		return -1;
	}
	fseek(f, 0, SEEK_SET);

	int on = 0;
	char header[7];
	do {
		c = fgetc(f);
		if(feof(f)) {
			break;
		}

		if(c == '.') {
			do {
				c = fgetc(f);
			} while (c != ',');
			c = fgetc(f);
			size_t idx = 0;
			do {
				header[idx++] = c;
				c = fgetc(f);
			} while (c != ',');
			header[idx] = '\0';
			//printf("%s\n", header);
			on++;
		}

		if(on) {
			char *arr[3];
			int i;
			for(i = 0; i < 3; i++) {
				size_t idx = 0;
				arr[i] = malloc(1);
				do {
					arr[i][idx] = c;
					idx++;
					arr[i] = realloc(arr[i], idx+1);
					c = fgetc(f);
					if(feof(f)) {
						break;
					}
				} while (c != ',' && c != '\n');
				arr[i][idx] = '\0';
				if(arr[i][0] == ',')
					memmove(arr[i], arr[i]+1, strlen(arr[i]+1) + 1);
			}
			printf("%s\t%s %s %s\n", header, arr[0], arr[1], arr[2]);
			free(arr[0]);
			free(arr[1]);
			free(arr[2]);
			//printf("%c", c);
			if(c == '\n') {
				on--;
			}
		}
	} while(1);
	printf("\n");
/*
	str = malloc(BUFF);
	strcpy(str, "update my_table set number_of_groups_analyzed = ");
	char temp[3];
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

