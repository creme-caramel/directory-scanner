#ifndef TABLESTRUCT_H
#define TABLESTRUCT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
	int other;  // offset 20
} mutations; 

void add(mutations *ptr, int offset, int val)
{
	*(((int *)ptr) + offset) += val;
}

char *toarr(int num)
{
	int n = (int)log10(num) + 1;
	char *arr = calloc(n+1, sizeof(char));
	snprintf(arr, sizeof(arr), "%d", num);
	return arr;
}

#endif
