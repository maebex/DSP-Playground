
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

    size_t len = (signal->len+1)/2;  // +1 to round up
    decomposition->numComponents = len;

    decomposition->real = calloc(len, sizeof *(decomposition->real));
    if(!decomposition->real){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
    }

    decomposition->imaginary = calloc(len, sizeof *(decomposition->imaginary));
    if(!decomposition->imaginary){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        goto cleanup;
    }



    return err;

cleanup: 
    free(decomposition->real);
    decomposition->real = NULL;
    decomposition->signal = NULL;
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