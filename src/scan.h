#ifndef SCAN_H
#define SCAN_H

#include <string.h>

typedef struct mutation_stats {
	int filtered;
	int number_of_groups_analyzed;
	int number_of_contaminations;
} mutation_stats;

typedef struct mutations {
	int a_to__; // offset 0
	int a_to_c; // offset 1
	int a_to_g; // offset 2
	int a_to_t; // offset 3
	int c_to_a; // offset 4
	int c_to__; // offset 5
	int c_to_g; // offset 6
	int c_to_t; // offset 7
	int g_to_a; // offset 8
	int g_to_c; // offset 9
	int g_to__; // offset 10
	int g_to_t; // offset 11
	int t_to_a; // offset 12
	int t_to_c; // offset 13
	int t_to_g; // offset 14
	int t_to__; // offset 15
	int __to_a; // offset 16
	int __to_c; // offset 17
	int __to_g; // offset 18
	int __to_t; // offset 19
	int other_; // offset 20
} mutations; 

void add(mutations *ptr, int offset, int val)
{
	*(((int *)ptr) + offset) += val;
}

void makenamearr(char *arr[])
{
	strcpy(*(arr++), "a_to__");
	strcpy(*(arr++), "a_to_c");
	strcpy(*(arr++), "a_to_g");
	strcpy(*(arr++), "a_to_t");
	strcpy(*(arr++), "c_to_a");
	strcpy(*(arr++), "c_to__");
	strcpy(*(arr++), "c_to_g");
	strcpy(*(arr++), "c_to_t");
	strcpy(*(arr++), "g_to_a");
	strcpy(*(arr++), "g_to_c");
	strcpy(*(arr++), "g_to__");
	strcpy(*(arr++), "g_to_t");
	strcpy(*(arr++), "t_to_a");
	strcpy(*(arr++), "t_to_c");
	strcpy(*(arr++), "t_to_g");
	strcpy(*(arr++), "t_to__");
	strcpy(*(arr++), "__to_a");
	strcpy(*(arr++), "__to_c");
	strcpy(*(arr++), "__to_g");
	strcpy(*(arr++), "__to_t");
	strcpy(*(arr), "other_");
}

#endif
