#ifndef SCAN_H
#define SCAN_H

#include <string.h>

typedef struct mutation_stats {
	int filtered;
	int number_of_groups_analyzed;
	int number_of_contaminations;
} mutation_stats;

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

void makenamearr(char *arr[])
{
	strcpy(*(arr++), "g to :");
	strcpy(*(arr++), "g to a");
	strcpy(*(arr++), "g to c");
	strcpy(*(arr++), "g to t");
	strcpy(*(arr++), "t to :");
	strcpy(*(arr++), "t to a");
	strcpy(*(arr++), "t to c");
	strcpy(*(arr++), "t to g");
	strcpy(*(arr++), "c to :");
	strcpy(*(arr++), "c to a");
	strcpy(*(arr++), "c to t");
	strcpy(*(arr++), "c to g");
	strcpy(*(arr++), "a to :");
	strcpy(*(arr++), "a to t");
	strcpy(*(arr++), "a to c");
	strcpy(*(arr++), "a to g");
	strcpy(*(arr++), ": to t");
	strcpy(*(arr++), ": to a");
	strcpy(*(arr++), ": to c");
	strcpy(*(arr++), ": to g");
	strcpy(*(arr), "other");
}

#endif
