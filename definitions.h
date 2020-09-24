#ifndef DEFINITIONS_H
#define DEFINITIONS_H

typedef struct Site Site;
typedef struct Walker Walker;
typedef struct Step Step;

struct Site {
    unsigned int position;
    int occupied;
    unsigned int time_trapping;
    float resources;
};

struct Walker {
    float eat_per_step;
    int is_dead;
    unsigned int trap_remaining;
    int is_trapped;
    Step *path;
};

struct Step {
    unsigned int time;
    long int site;
    Step *next;
};

#endif // DEFINITIONS_H
