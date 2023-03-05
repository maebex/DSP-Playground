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


int cround(double complex *z, double delta)
{
    int err = 0;
    if(!z){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    double re = creal(*z);
    double im = cimag(*z);
    double re2 = (double)4.4408920985006262e-16;

    if((creal(*z) < 0.0) && (creal(*z) > (-1.*fabs(delta)))){
        *z -= creal(*z);
    }else if ((creal(*z) > 0.0) && (creal(*z) < fabs(delta))){
        *z -= creal(*z);
    }

    if((cimag(*z) < 0.0) && (cimag(*z) > (-1.*fabs(delta)))){
        *z -= I*cimag(*z);
    }else if ((cimag(*z) > 0.0) && (cimag(*z) < fabs(delta))){
        *z -= I*cimag(*z);
    }

    return err;
}