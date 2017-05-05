/*
 * Read output of a single lane+mid case
 */

#include "hash/muttype.h"
#include "db.h"
#include "tablestruct.h"
#include <stdlib.h>
#include <string.h>
#include <filter.h>

#define BUFF 256

int main(int argc, char **argv)
{
	FILE *f;
	int rc;
	sqlite3 *db;
	unsigned char c;
	mutations m, hm;
	mutation_stats stats;
	
	memset(&m, 0, sizeof(mutations));
	memset(&hm, 0, sizeof(mutations));
	memset(&stats, 0, sizeof(mutation_stats));

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

	char mutname[7]; // will look like 'g_to_c'
	int readnum = 0;
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
				if(c == ' ' || c == ':')
					c = '_';
				mutname[idx++] = c;
				c = fgetc(f);
			} while (c != ',');
			mutname[idx] = '\0';
			//printf("%s\n", header);
			readnum++; // done with mutation name
		}
		if(readnum) { // define next arr[X,X,X] if exists

			/*
			 * arr[0] = #group
			 * arr[1] = freq within the group
			 * arr[2] = total member in the group
			 */

			char *arr[3];
			int i_arr[3];
			int i;
			for(i = 0; i < 3; i++) {
				size_t idx = 0;
				arr[i] = malloc(1);
				do {
					arr[i][idx++] = c;
					arr[i] = realloc(arr[i], idx+1);
					c = fgetc(f);
					if(feof(f)) {
						break;
					}
				} while (c != ',' && c != '\n');
				arr[i][idx] = '\0';
				if(arr[i][0] == ',')
					memmove(arr[i], arr[i]+1, strlen(arr[i]+1) + 1);
				sscanf(arr[i], "%d", &i_arr[i]);
				free(arr[i]);
			}
			if(i_arr[2] >= 5) { // by definition of raw groups
				printf("%s\t%d %d %d", mutname, i_arr[0], i_arr[1], i_arr[2]);
				if(isfiltered()) { // assume true for now
					add(&m, get_offset(mutname), i_arr[1]);
					printf("\tadded to: %s (%d)", mutname, i_arr[1]);
				}
				printf("\n");
			}
			//printf("%c", c);
			if(c == '\n') {
				readnum--; // done with numbers
			}
		}
	} while(1);
	printf("%d %d\n", m.g_to_c, m.__to_g);

	char *str;
	str = malloc(BUFF);
	strcpy(str, "update my_table set ");
	strcat(str, "g_to_c = ");
	strcat(str, (const char *)toarr(m.g_to_c));
	strcat(str, " where ID=");
	strcat(str, argv[3]);
	rc = db_exec(db, str, "update");
	free(str);

	fclose(f);
	sqlite3_close(db);
	return 0;
}

