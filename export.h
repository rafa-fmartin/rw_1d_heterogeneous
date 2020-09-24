#ifndef EXPORT_H
#define EXPORT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "definitions.h"

void export_map(Site *map, unsigned int sites, FILE *file);
void export_walks(Walker *walkers, unsigned int num_walkers, unsigned int steps);
void export_statistics(float *average, float *variance, unsigned int steps);
void export_properties(float *g, unsigned int num_walkers);

#endif // EXPORT_H
