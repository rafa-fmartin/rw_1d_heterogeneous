#include "export.h"

void export_map(Site *map, unsigned int sites, FILE *file) {
    for(unsigned int i = 0; i < sites; i++) {
        fprintf(file, "%d ", (map+i)->occupied);
    }

    fprintf(file, "\n");
}

void export_walks(Walker *walkers, unsigned int num_walkers, unsigned int steps) {
    FILE *file;

    file = fopen("walks.dat", "w");

    for(unsigned int i = 0; i <= steps; i++) {
        fprintf(file, "%d ", i);
    }

    fprintf(file, "\n");

    for(unsigned int i = 0; i < num_walkers; i++) {
        Step *aux = (walkers+i)->path;
        for(unsigned int j = 0; j <= steps; j++) {
            if(aux != NULL) {
                fprintf(file, "%ld ", aux->site);
                aux = aux->next;
            } else {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void export_properties(float *g, unsigned int num_walkers) {
    FILE *file;

    file = fopen("properties.dat", "w");

    fprintf(file, "# PROPERTIES\n");
    fprintf(file, "#| g |\n");
    for(unsigned int i = 0; i < num_walkers; i++) {
        fprintf(file, "%f\n", *(g+i));
    }

    fclose(file);
}
