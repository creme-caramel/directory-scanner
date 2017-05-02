#include "muttype.h"
#include "table_details.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>

#define BUFF 256

void add(mutations *ptr, int offset, int val)
{
	*(((int *)ptr) + offset) += val;
}

int main(int argc, char **argv)
{
	//char *str;
	//size_t str_i;
	FILE *f;
	int rc;
	sqlite3 *db;
	//cols vals;
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
				if(c == ' ' || c == ':')
					c = '_';
				header[idx++] = c;
				c = fgetc(f);
			} while (c != ',');
			header[idx] = '\0';
			//printf("%s\n", header);
			on++; // Skip headers
		}
		if(on) { // Define next [X,X,X] if any
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
			if(i_arr[2] >= 5) {



				printf("%s\t%d %d %d\n", header, i_arr[0], i_arr[1], i_arr[2]);
			}
			//printf("%c", c);
			if(c == '\n') {
				on--;
			}
		}
	} while(1);
	printf("\n");
	printf("%d %d %d %d\n", get_offset("__to_t"), get_offset("c_to_a"), get_offset("a_to_c"), get_offset("EEE"));


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

