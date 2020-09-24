#ifndef WALKERS_H
#define WALKERS_H

#include <stdlib.h>
#include <time.h>
#include "definitions.h"

void initialize_walkers(Walker *walkers, unsigned int num_walkers, float eat_rate);
void down_set_hut(Step *initial, unsigned int sites);
void kill_all_walkers(Walker *walkers, unsigned int num_walkers);
void free_path(Step *path);

#endif // WALKERS_H
