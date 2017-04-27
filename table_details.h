#ifndef TABLE_DETAILS_H
#define TABLE_DETAILS_H

#include <stdio.h>
#include <string.h>

#define TABLE_SQL_SIZE 1500
#define UPPER_POS 280
#define LOWER_POS 16559

void create_table(char *table)
{
	strcpy(table, "create table if not exists my_table (");
	strcat(table, "id integer primary key autoincrement,"); 
	strcat(table, "Run text,");
	strcat(table, "Filtered text default 'No',");
	strcat(table, "lane integer,"); 
	strcat(table, "mid integer,"); 
	strcat(table, "number_of_groups_analyzed integer default 0,"); 
	strcat(table, "number_of_raw_groups integer default 0,"); 
	strcat(table, "number_of_contaminations integer default 0,"); 
	strcat(table, "a_to__ integer default 0,"); 
	strcat(table, "a_to_c integer default 0,"); 
	strcat(table, "a_to_g integer default 0,"); 
	strcat(table, "a_to_t integer default 0,"); 
	strcat(table, "c_to_a integer default 0,"); 
	strcat(table, "c_to__ integer default 0,"); 
	strcat(table, "c_to_g integer default 0,"); 
	strcat(table, "c_to_t integer default 0,"); 
	strcat(table, "g_to_a integer default 0,"); 
	strcat(table, "g_to_c integer default 0,"); 
	strcat(table, "g_to__ integer default 0,"); 
	strcat(table, "g_to_t integer default 0,"); 
	strcat(table, "t_to_a integer default 0,"); 
	strcat(table, "t_to_c integer default 0,"); 
	strcat(table, "t_to_g integer default 0,"); 
	strcat(table, "t_to__ integer default 0,"); 
	strcat(table, "__to_a integer default 0,"); 
	strcat(table, "__to_c integer default 0,"); 
	strcat(table, "__to_g integer default 0,"); 
	strcat(table, "__to_t integer default 0,"); 
	strcat(table, "other integer default 0,"); 
	strcat(table, "hetero_a_to__ integer default 0,"); 
	strcat(table, "hetero_a_to_c integer default 0,"); 
	strcat(table, "hetero_a_to_g integer default 0,"); 
	strcat(table, "hetero_a_to_t integer default 0,"); 
	strcat(table, "hetero_c_to_a integer default 0,"); 
	strcat(table, "hetero_c_to__ integer default 0,"); 
	strcat(table, "hetero_c_to_g integer default 0,"); 
	strcat(table, "hetero_c_to_t integer default 0,"); 
	strcat(table, "hetero_g_to_a integer default 0,"); 
	strcat(table, "hetero_g_to_c integer default 0,"); 
	strcat(table, "hetero_g_to__ integer default 0,"); 
	strcat(table, "hetero_g_to_t integer default 0,"); 
	strcat(table, "hetero_t_to_a integer default 0,"); 
	strcat(table, "hetero_t_to_c integer default 0,"); 
	strcat(table, "hetero_t_to_g integer default 0,"); 
	strcat(table, "hetero_t_to__ integer default 0,"); 
	strcat(table, "hetero___to_a integer default 0,"); 
	strcat(table, "hetero___to_c integer default 0,"); 
	strcat(table, "hetero___to_g integer default 0,"); 
	strcat(table, "hetero___to_t integer default 0,"); 
	strcat(table, "hetero_other integer default 0)");
}

typedef struct cols {
	unsigned int filtered;
	unsigned int lane;
	unsigned int mid;
	unsigned int num_groups_analyzed;
	unsigned int num_groups_raw;
	unsigned int num_of_contaminations;
	unsigned int a_to__;
	unsigned int a_to_c;
	unsigned int a_to_g;
	unsigned int a_to_t;
	unsigned int c_to_a;
	unsigned int c_to__;
	unsigned int c_to_g;
	unsigned int c_to_t;
	unsigned int g_to_a;
	unsigned int g_to_c;
	unsigned int g_to__;
	unsigned int g_to_t;
	unsigned int t_to_a;
	unsigned int t_to_c;
	unsigned int t_to_g;
	unsigned int t_to__;
	unsigned int __to_a;
	unsigned int __to_c;
	unsigned int __to_g;
	unsigned int __to_t;
	unsigned int other;
	unsigned int hetero_a_to__;
	unsigned int hetero_a_to_c;
	unsigned int hetero_a_to_g;
	unsigned int hetero_a_to_t;
	unsigned int hetero_c_to_a;
	unsigned int hetero_c_to__;
	unsigned int hetero_c_to_g;
	unsigned int hetero_c_to_t;
	unsigned int hetero_g_to_a;
	unsigned int hetero_g_to_c;
	unsigned int hetero_g_to__;
	unsigned int hetero_g_to_t;
	unsigned int hetero_t_to_a;
	unsigned int hetero_t_to_c;
	unsigned int hetero_t_to_g;
	unsigned int hetero_t_to__;
	unsigned int hetero___to_a;
	unsigned int hetero___to_c;
	unsigned int hetero___to_g;
	unsigned int hetero___to_t;
	unsigned int hetero_other;
} cols;

#endif
