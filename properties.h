#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <stdlib.h>
#include <math.h>
#include "definitions.h"

void calc_average(Walker *walkers, unsigned int num_walkers, unsigned int steps, float *average);
void calc_variance(Walker *walkers, unsigned int num_walkers, unsigned int steps, float *average, float *variance);
void calc_G(float *g, Walker *walkers, unsigned int num_walkers, unsigned int sites);
Step* copyList(Step *path);
Step* distinct_sites(Step *path);
void kill_properties(float *average, float *variance, float *g);

#endif // PROPERTIES_H
