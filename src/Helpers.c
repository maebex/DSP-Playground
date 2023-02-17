#include "Helpers.h"



double_t DSPPG__Helpers__genRand(double_t max)
{
    static int srand_initialized = 0;
    if(!srand_initialized){
        srand((unsigned int)time(NULL));
        srand_initialized = 1;
    }
    return (double)rand()/(double)(RAND_MAX/max);
}

