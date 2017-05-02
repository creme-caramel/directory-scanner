#ifndef TABLE_DETAILS_H
#define TABLE_DETAILS_H

#include <stdio.h>
#include <string.h>

#define UPPER_POS 280
#define LOWER_POS 16559
#define DEFAULT_CUTOFF_GROUPNUM 5
#define DEFAULT_CUTOFF_FREQ 0.75

typedef struct mutations {
	int a_to__;
	int a_to_c;
	int a_to_g;
	int a_to_t;
	int c_to_a;
	int c_to__;
	int c_to_g;
	int c_to_t;
	int g_to_a;
	int g_to_c;
	int g_to__;
	int g_to_t;
	int t_to_a;
	int t_to_c;
	int t_to_g;
	int t_to__;
	int __to_a;
	int __to_c;
	int __to_g;
	int __to_t;
	int other;
} mutations; 

typedef struct mutation_stats {
	int filtered;
	int number_of_groups_analyzed;
	int number_of_contaminations;
} mutation_stats;

#endif
