# rw_1d_heterogeneous
Algorithms for simulations of one-dimensional random walks on a heterogeneous media.
============================================================================================================

Hello. Here, you'll be able to understand the code.

============================================================================================================

INSTALLING WHAT'S NECESSARY TO RUN

We need to install gsl. It is really good for some mathematical functions and statistics. Here, gsl provides some probabilites distributions.

Please, access https://www.gnu.org/software/gsl/doc/html/intro.html for details and install.

For tests, install valgrind in debian-based systems. Type on terminal: sudo apt install valgrind

============================================================================================================

RECIPES FOR TEST AND RUN

The *.sh files are recipes for testing in valgrind (try.sh), running the simulation (execute.sh), and cleaning the mess (*.dat files) before execute
anything (clear.sh).

Try this in terminal: ./try.sh
Then: ./clear.sh
Then: ./execute.sh

You'll be able to see some *.dat files. They are the results of simulation.

If the terminal gives you a error message on ./*.sh (where * is what you wrote), try to type: chmod 774 *.sh

===========================================================================================================

THE MODEL

Imagine we live in an one-dimensional, and discrete torus. It means that this this torus is made of N sites almost looking like a circumference (the more
sites, the more it looks like a circumference). Each site is connected to two other sites: left, and right.

(to be continued)

===========================================================================================================

EXPLANATION FOR definitions.h

    -> Site: every site in map has a position, and an amount of resources available. It can be a trap (when time_trapping > 0). The 'occupied' is just for a better controlling in go_walk.c file;
    
    -> Walker: every walker has a path (that's pure philosofy) built with steps. The 'is_dead', 'trap_remaining', and 'is_trapped' items helps in the go_walk.c file. I know that they all have the same eat per step rate, but if we want to change it in future, we can (for example two, or more, different species).
    
    -> Step: every step has a (discrete) time and a (discrete) site. The pointer *next tells what's the next step. The *next pointer is NULL if a) the walker is dead or b) the walk is over. If *next is different from NULL, it indicates the next step. And yes, here we don't have a vector. We have a linked list.
    
    -> For higher dimensions, we can implement the struct Coordinates just like that:
        typedef struct Coordinates Coordinates;
        struct Coordinates {
            unsigned int x;
            unsigned int y;
            unsigned int z;
        }
    I want to go for higher dimensions, but the code must be (a lot, A LOT) better.

============================================================================================================

EXPLANATION FOR variables:

    -> Seed: for the random numbers;
    
    -> Sites: number of sites in the map. Must be an odd number. It happens because I want the same amount of sites in the left and in the right of the 0;
    
    -> Is_independent: tells the program if we're talking about dependent (0), or independent (1) walks;
    
    -> Traps: number of sites that traps the walkers. It's obvious that traps <= sites;
    
    -> Mu_time: the average value for time trapping in the traps. If you take a look in the map.c file, you'll see that the distribution of time trapping in traps follows an Poisson distribution with mean mu_time;
    
    -> Num_walkers: number of walkers. Must be considerable lower than the number of sites. This happens because every walker has an initial position different from the others. And, of course, my code for search initial positions is completely lazy and disgusting;
    
    -> Steps: number of steps. Be free to choose, but remember that the map is in an periodic boundary condition. Don't push it too hard;
    
    -> Max_resources: is the maximum value for resources that a site can have. If you take a look in the map.c file, you'll see that the distribution for resources in sites follows an flat (uniform) distribution from 0 to max_resources;
    
    -> Eat_rate: this is the eat per step rate of each walker. For now, all the walkers have the same eat_rate, but we can change this (if you want to);
    
    -> *average: the reason #1 of my nightmares. This calculates the average site in every step;
    
    -> *variance: the reason #2 of my nightmares. This calculates the variance in every step;
    
    -> *map: is a pointer (vector) containing all the sites and characteristics;
    
    -> *walkers: is a pointer (vector) containing all the walkers, characteristics, and history of walks.
    
