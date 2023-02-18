#include "Helpers.h"



double DSPPG__Helpers__genRand(double max)
{
    static unsigned int DSPPG__SRAND_INITIALIZED = 0;
    if(!DSPPG__SRAND_INITIALIZED){
        srand((unsigned int)time(NULL));
        DSPPG__SRAND_INITIALIZED = 1;
    }
    return (double)rand()/(double)(RAND_MAX/max);
}

