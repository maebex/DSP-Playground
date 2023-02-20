
#include "Transformations.h"



int DSPPG__Transformations__DFT_Decomposition_decompose(DSPPG_DigSignal_FD_t *decomposition, 
                                                        DSPPG_DigSignal_TD_t *signal)
{
    int err = 0;
    if(!decomposition || !signal || signal->data || 0==signal->len){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    size_t len = signal->len/2;

    



    return err;
}



int DSPPG__Transformations__DFT_Decomposition_destroy(DSPPG_DigSignal_FD_t *decomposition)
{
    int err = 0;
    if(!decomposition){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    if(decomposition->real){
        free(decomposition->real);
        decomposition->real = NULL;
    }
    if(decomposition->imaginary){
        free(decomposition->imaginary);
        decomposition->imaginary = NULL;
    }
    return err;
}