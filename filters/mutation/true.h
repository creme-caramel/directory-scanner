#ifndef TRUE_H
#define TRUE_H

#define UPPER_POS 280
#define LOWER_POS 16559
#define DEFAULT_CUTOFF_FREQ 0.75

typedef int triple[3];

int istrue_mutation(const triple t)
{
	double div = (double)t[1] / (double)t[2];
	if((double)div >= (double)0.75)
		return 1; // true
	else
		return 0;
}

#endif 
