#include "walkers.h"

void initialize_walkers(Walker *walkers, unsigned int num_walkers, float eat_rate) {
    for(unsigned int i = 0; i < num_walkers; i++) {
        (walkers+i)->eat_per_step = eat_rate;
        (walkers+i)->is_dead = 0;
        (walkers+i)->trap_remaining = 0;
        (walkers+i)->is_trapped = 0;
        (walkers+i)->path = NULL;
    }
}

// just a default free-linked-list function
void free_path(Step *path) {
    Step *node = path,
         *temp = NULL;

    while(node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }

    path = NULL;
}

void kill_all_walkers(Walker *walkers, unsigned int num_walkers) {
    // we need to free the paths (linked lists) first
    for(unsigned int i = 0; i < num_walkers; i++) {
        free_path((walkers+i)->path);
    }

    // now we can free y'all
    free(walkers);
}
