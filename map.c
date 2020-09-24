#include "map.h"

void create_map(Site *map, unsigned int sites, unsigned int traps, unsigned int mu_time, float max_resources, long int seed) {
    int random = 0;

    // idk wtf is this, but i saw it in the internet, must be true
    const gsl_rng_type *T;
    gsl_rng *r;

    // initialize gsl setup
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    gsl_rng_set(r, seed);

    // setup all sites
    // if max_resources equals to zero, there is no quality dynamics in this simulation
    if(max_resources == 0) {
        for(unsigned int i = 0; i < sites; i++) {
            (map+i)->position = i;
            (map+i)->occupied = 0;
            (map+i)->resources = 0;
            (map+i)->time_trapping = 0;
        }
    }
    else {
        for(unsigned int i = 0; i < sites; i++) {
            (map+i)->position = i;
            (map+i)->occupied = 0;
            (map+i)->resources = gsl_ran_flat(r, 0, max_resources);
            //(map+i)->resources = ran2(&seed);
            (map+i)->time_trapping = 0;
        }
    }

    // distribute the traps uniformly with time trapping following a Poisson Distribution
    for(unsigned int i = 0; i < traps; i++) {
        // pick up a random site that isn't a trap yet
        do{
            random = gsl_rng_uniform_int(r, sites);
        } while((map+random)->time_trapping != 0);

        // this while garantees that will be X traps with time trapping > 1 in the map
        do{
            (map+random)->time_trapping = gsl_ran_poisson(r, mu_time);
        } while((map+random)->time_trapping == 0);
    }

    gsl_rng_free(r);
}

void destruct_map(Site *map) {
    free(map);
}
