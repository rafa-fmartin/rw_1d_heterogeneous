#ifndef GO_WALK_H
#define GO_WALK_H

#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "definitions.h"
#include "ran2.h"
#include "export.h"

void walk(Site *map, Walker *walkers, unsigned int sites, unsigned int num_walkers, unsigned int steps, long int seed, float max_resources, int is_independent, FILE *file);
void initial_positions(Site *map, Walker *walkers, unsigned int sites, unsigned int num_walkers, long int seed, int is_independent);
Step *new_step(Step *step_zero, Site site, unsigned int time);
Site search_site(Site *map, unsigned int sites, unsigned int position);

#endif // GO_WALK_H
