#include "go_walk.h"

void walk(Site *map, Walker *walkers, unsigned int sites, unsigned int num_walkers, unsigned int steps, long int seed, float max_resources, int is_independent, FILE *file) {
    Step *current_s = NULL;
    unsigned int current = 0;
    float random = 0;

    // down...set...
    initial_positions(map, walkers, sites, num_walkers, seed, is_independent);

    Site *initial_map = map;

    // hut!
    if(is_independent) {
        for(unsigned int j = 0; j < num_walkers; j++) {
            map = initial_map;
            for(unsigned int i = 1; i <= steps; i++) {
                // checking if the walkers is still alive
                if(!((walkers+j)->is_dead)) {
                    current_s = (walkers+j)->path;
                    while(current_s->next != NULL) {
                        current_s = current_s->next;
                    }
                    current = current_s->site;

                    // if this site is a trap, refresh the is_trapped information
                    if((map+current)->time_trapping) {
                        if((walkers+j)->is_trapped == 0) {
                            (walkers+j)->is_trapped = 1;
                            (walkers+j)->trap_remaining = (map+current)->time_trapping;
                        } else {
                            if((walkers+j)->trap_remaining == 1) {
                                (walkers+j)->is_trapped = 0;
                            } else {
                                (walkers+j)->trap_remaining = (walkers+j)->trap_remaining - 1;
                            }
                        }
                    }

                    // if the walker isn't trapped
                    if(!((walkers+j)->is_trapped)) {
                        // "i'm gonna leave, bye bye friends"
                        ((map+current)->occupied)--;

                        // let's choose a side
                        random = ran2(&seed);
                        if(random < 0.5) { // go to left
                            if(current == 0) current = sites-1;
                            else current = current-1;
                        } else { // go to right
                            if(current == (sites-1)) current = 0;
                            else current = current+1;
                        }
                    }

                    // new step
                    (walkers+j)->path = new_step((walkers+j)->path, *(map+current), i);
                    if(!((walkers+j)->is_trapped)) ((map+current)->occupied)++;
                    // check the resources dynamics
                    if(max_resources) {
                        // resource consumption
                        if(((map+current)->resources - (walkers+j)->eat_per_step) >= 0) { // eat and that's ok
                            (map+current)->resources = (map+current)->resources - (walkers+j)->eat_per_step;
                        } else { // there's no enough food, walker dying
                            (map+current)->resources = 0;
                            (walkers+j)->is_dead = 1;
                        }
                    }
                }
                export_map(map, sites, file);
            }
        }
    } else {
        for(unsigned int i = 1; i <= steps; i++) {
            for(unsigned int j = 0; j < num_walkers; j++) {
                // checking if the walker is still alive
                if(!((walkers+j)->is_dead)) {
                    // looking for the last step
                    current_s = (walkers+j)->path;
                    while(current_s->next != NULL) {
                        current_s = current_s->next;
                    }
                    current = current_s->site;

                    // if this site is a trap, refresh the is_trapped information
                    if((map+current)->time_trapping) {
                        if((walkers+j)->is_trapped == 0) {
                            (walkers+j)->is_trapped = 1;
                            (walkers+j)->trap_remaining = (map+current)->time_trapping;
                        } else {
                            if((walkers+j)->trap_remaining == 1) {
                                (walkers+j)->is_trapped = 0;
                            } else {
                                (walkers+j)->trap_remaining = (walkers+j)->trap_remaining - 1;
                            }
                        }
                    }

                    // if the walker isn't trapped
                    if(!((walkers+j)->is_trapped)) {
                        // "i'm gonna leave, bye bye previous location"
                        (map+current)->occupied = 0;

                        // let's choose a side
                        random = ran2(&seed);
                        if(random < 0.5) { // go to left
                            if(current == 0) current = sites-1;
                            else current = current - 1;
                        } else { // go to right
                            if(current == (sites-1)) current = 0;
                            else current = current + 1;
                        }

                        // if the destination is occupied, back to the previous location
                        if((map+current)->occupied) {
                            current = (walkers+j)->path->site;
                        }
                    }

                    // new step
                    (walkers+j)->path = new_step((walkers+j)->path, *(map+current), i);
                    // check the (in)dependence of walkers
                    (map+current)->occupied = 1;
                    // check the resources dynamics
                    if(max_resources) {
                        // resource consumption
                        if(((map+current)->resources - (walkers+j)->eat_per_step) >= 0) { // eat and that's ok
                            (map+current)->resources = (map+current)->resources - (walkers+j)->eat_per_step;
                        } else { // there's no enough food, walker dying
                            (map+current)->resources = 0;
                            (walkers+j)->is_dead = 1;
                        }
                    }
                }
            }
            export_map(map, sites, file);
        }
    }
/*
    for(unsigned int i = 1; i <= steps; i++) {
        for(unsigned int j = 0; j < num_walkers; j++) {
            // checking if the walker is still alive
            if(!((walkers+j)->is_dead)) {
                // looking for the last step
                current_s = (walkers+j)->path;
                while(current_s->next != NULL) {
                    current_s = current_s->next;
                }
                current = current_s->site;

                // if this site is a trap, refresh the is_trapped information
                if((map+current)->time_trapping) {
                    if((walkers+j)->is_trapped == 0) {
                        (walkers+j)->is_trapped = 1;
                        (walkers+j)->trap_remaining = (map+current)->time_trapping;
                    } else {
                        if((walkers+j)->trap_remaining == 1) {
                            (walkers+j)->is_trapped = 0;
                        } else {
                            (walkers+j)->trap_remaining = (walkers+j)->trap_remaining - 1;
                        }
                    }
                }

                // if the walker isn't trapped
                if(!((walkers+j)->is_trapped)) {
                    // check the (in)dependence of walkers
                    if(is_independent) {
                        // "i'm gonna leave, bye bye friends"
                        ((map+current)->occupied)--;

                        // let's choose a side
                        random = ran2(&seed);
                        if(random < 0.5) { // go to left
                            if(current == 0) current = sites-1;
                            else current = current - 1;
                        } else { // go to right
                            if(current == (sites-1)) current = 0;
                            else current = current + 1;
                        }
                    } else {
                        // "i'm gonna leave, bye bye previous location"
                        (map+current)->occupied = 0;

                        // let's choose a side
                        random = ran2(&seed);
                        if(random < 0.5) { // go to left
                            if(current == 0) current = sites-1;
                            else current = current - 1;
                        } else { // go to right
                            if(current == (sites-1)) current = 0;
                            else current = current + 1;
                        }

                        // if the destination is occupied, back to the previous location
                        if((map+current)->occupied) {
                            current = (walkers+j)->path->site;
                        }
                    }
                }

                // new step
                (walkers+j)->path = new_step((walkers+j)->path, *(map+current), i);
                // check the (in)dependence of walkers
                if(is_independent) {
                    ((map+current)->occupied)++;
                } else {
                    (map+current)->occupied = 1;
                }
                // check the resources dynamics
                if(max_resources) {
                    // resource consumption
                    if(((map+current)->resources - (walkers+j)->eat_per_step) >= 0) { // eat and that's ok
                        (map+current)->resources = (map+current)->resources - (walkers+j)->eat_per_step;
                    } else { // there's no enough food, walker dying
                        (map+current)->resources = 0;
                        (walkers+j)->is_dead = 1;
                    }
                }
            }
        }
    }
*/
}

void initial_positions(Site *map, Walker *walkers, unsigned int sites, unsigned int num_walkers, long int seed, int is_independent) {
    unsigned int random;
    const gsl_rng_type *T;
    gsl_rng *r;

    // initializing gsl setup
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    gsl_rng_set(r, seed+1);

    // time to choose
    for(unsigned int i = 0; i < num_walkers; i++) {
        // checking the (in)dependence of walkers
        if(is_independent) {
            //random = (unsigned int) gsl_rng_uniform_int(r, sites);
            //((map+random)->occupied)++;
            (walkers+i)->path = new_step((walkers+i)->path, *(map+i), 0);
        } else {
            // looking for a random unoccupied site
            do {
                random = (unsigned int) gsl_rng_uniform_int(r, sites);
            } while((map+random)->occupied);

            // now that random site is occupied by i-th walker
            (map+random)->occupied = 1;
            // initial position for the (i+1)th walker
            (walkers+i)->path = new_step((walkers+i)->path, *(map+random), 0);
        }
    }

    // don't forget to free the memory
    gsl_rng_free(r);
}

Step *new_step(Step *step_zero, Site site, unsigned int time) {
    if(step_zero == NULL) {
        Step *new = malloc(sizeof(Step));

        new->time = time;
        new->site = site.position;
        new->next = NULL;

        return new;
    }

    step_zero->next = new_step(step_zero->next, site, time);
    return step_zero;
}
