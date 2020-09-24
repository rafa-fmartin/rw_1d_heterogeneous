#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "definitions.h"
#include "ran2.h"
#include "map.h"
#include "walkers.h"
#include "go_walk.h"
#include "properties.h"
#include "export.h"

int main() {
    long int seed = 0;
    int is_independent = 0;
    unsigned int sites = 0,
                 traps = 0,
                 mu_time = 0,
                 num_walkers = 0,
                 steps = 0;
    float max_resources = 0.0,
          eat_rate = 0.0,
          *average = NULL,
          *variance = NULL,
          *g = NULL;
    Site *map = NULL;
    Walker *walkers = NULL;
    FILE *initial_data,
         *mapfile;

    initial_data = fopen("data.dat", "r");
    mapfile = fopen("tapestry_map.dat", "w");

    fscanf(initial_data, "%u %u %u %u %u %f %f %d", &sites, &traps, &num_walkers, &steps, &mu_time, &max_resources, &eat_rate, &is_independent);

    // initialize ran2
    seed = -(time(NULL));
    ran2(&seed);

    average = malloc((steps+1) * sizeof(float));
    variance = malloc((steps+1) * sizeof(float));
    g = malloc(num_walkers * sizeof(float));
    map = malloc(sites * sizeof(Site));
    walkers = malloc(num_walkers * sizeof(Walker));

    if(average == NULL || variance == NULL || g == NULL || map == NULL || walkers == NULL) {
        return 1;
    }

    create_map(map, sites, traps, mu_time, max_resources, seed);

    initialize_walkers(walkers, num_walkers, eat_rate);
    walk(map, walkers, sites, num_walkers, steps, seed, max_resources, is_independent, mapfile);

    calc_average(walkers, num_walkers, steps, average);
    calc_variance(walkers, num_walkers, steps, average, variance);
    calc_G(g, walkers, num_walkers, sites);

    //export_map(map, sites, mapfile);
    export_walks(walkers, num_walkers, steps);
    export_properties(g, num_walkers);

    // free. your. mind.
    fclose(initial_data);
    fclose(mapfile);
    destruct_map(map);
    kill_all_walkers(walkers, num_walkers);
    kill_properties(average, variance, g);

    return 0;
}
