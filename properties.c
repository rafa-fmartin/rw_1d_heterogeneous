#include "properties.h"

void calc_average(Walker *walkers, unsigned int num_walkers, unsigned int steps, float *average) {
    for(unsigned int i = 0; i <= steps; i++) {
        Step *current_s;
        unsigned int current,
                     sum = 0;

        for(unsigned int j = 0; j < num_walkers; j++) {
            if(!((walkers+j)->is_dead)) {
                unsigned int k = 0;
                current_s = (walkers+j)->path;
                while(k < i) {
                    current_s = current_s->next;
                    k++;
                }
            } else {
                unsigned int k = 0;
                current_s = (walkers+j)->path;
                while(k < i && current_s != NULL) {
                    current_s = current_s->next;
                    k++;
                }
            }
            //current = current_s->site - zero;
            if(current_s != NULL) current = current_s->site;
            else current = 0;
            sum += current;
        }

        *(average+i) = ((float)(sum))/num_walkers;
    }
}

void calc_variance(Walker *walkers, unsigned int num_walkers, unsigned int steps, float *average, float *variance) {
    for(unsigned int i = 0; i <= steps; i++) {
        Step *current_s;
        unsigned int current,
                     sum = 0;

        for(unsigned int j = 0; j < num_walkers; j++) {
            if(!((walkers+j)->is_dead)) {
                unsigned int k = 0;
                current_s = (walkers+j)->path;
                while(k < i) {
                    current_s = current_s->next;
                    k++;
                }
            } else {
                unsigned int k = 0;
                current_s = (walkers+j)->path;
                while(k < i && current_s != NULL) {
                    current_s = current_s->next;
                    k++;
                }
            }
            //current = current_s->site - zero;
            if(current_s != NULL) current = current_s->site;
            else current = 0;
            sum += pow(current, 2);
        }
        *(variance+i) = ((float)(sum))/num_walkers - pow(*(average+i), 2);
    }
}

void calc_G(float *g, Walker *walkers, unsigned int num_walkers, unsigned int sites) {
    for(unsigned int i = 0; i < num_walkers; i++) {
        unsigned int counter = 0;
        Step *distinct = copyList((walkers+i)->path);
        distinct = distinct_sites(distinct);

        for(Step *p = distinct; p != NULL; p = p->next) {
            counter++;
        }

        free(distinct);

        *(g+i) = ((float)counter)/sites;
    }
}

Step* copyList(Step* path) {
	Step* current = path;	// used to iterate over original list
	Step* newList = NULL; // head of the new list
	Step* tail = NULL;	// point to last node in new list

	while (current != NULL) {
		// special case for the first new Node
		if (newList == NULL) {
			newList = malloc(sizeof(Step));
			newList->site = current->site;
			newList->next = NULL;
			tail = newList;
		} else {
			tail->next = malloc(sizeof(Step));
			tail = tail->next;
			tail->site = current->site;
			tail->next = NULL;
		}
		current = current->next;
	}

	return newList;
}

Step* distinct_sites(Step *path) {
    if(path == NULL || path->next == NULL) return path;

    if(path->site == path->next->site) {
        Step *temp = path->next;
        path->next = temp->next;
        free(temp);
        return distinct_sites(path);
    }

    path->next = distinct_sites(path->next);

    return path;
}

void kill_properties(float *average, float *variance, float *g) {

    free(average);
    free(variance);
    free(g);
}
