#ifndef SCAN_H
#define SCAN_H

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

#endif
