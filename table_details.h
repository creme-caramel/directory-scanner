#ifndef TABLE_DETAILS_H
#define TABLE_DETAILS_H

#include <stdio.h>
#include <string.h>

#define TABLE_SQL_SIZE 1500
#define UPPER_POS 280
#define LOWER_POS 16559
#define DEFAULT_CUTOFF_GROUPNUM 5
#define DEFAULT_CUTOFF_FREQ 0.75

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
