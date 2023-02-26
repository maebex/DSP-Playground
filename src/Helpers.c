#include "Helpers.h"



float DSPPG__Helpers__genRand(float max)
{
    static unsigned int DSPPG__SRAND_INITIALIZED = 0;
    if(!DSPPG__SRAND_INITIALIZED){
        srand((unsigned int)time(NULL));
        DSPPG__SRAND_INITIALIZED = 1;
    }
    return (float)rand()/(float)(RAND_MAX/max);
}

