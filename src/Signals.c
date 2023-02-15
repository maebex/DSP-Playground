
#include "Signals.h"


int DSPPG__Signals__DigSignal__setData(DSPPG_DigSignal_t *sig, 
                                       size_t len,
                                       payloadType_t *data)
{
    if(!sig){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    if(!data){
        sig->len = 0;
        sig->data = NULL;
    }else{
        sig->len = len;
        sig->data = data;
    }
    return 0;
}



int DSPPG__Signals__DigSignal__convolute(DSPPG_DigSignal_t *res,
                                         DSPPG_DigSignal_t *signal,
                                         DSPPG_DigSignal_t *filter)
{


    return 0;
}
