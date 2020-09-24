#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "definitions.h"
#include "ran2.h"

void create_map(Site *map, unsigned int sites, unsigned int traps, unsigned int mu_time, float max_resources, long int seed);
void destruct_map(Site *map);

#endif // MAP_H
