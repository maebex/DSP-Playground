
#include "Signals.h"

int DSPPG__Signals__DigSignal__Init_empty(DSPPG_DigSignal_t **sig)
{
    *sig = calloc(1, sizeof(DSPPG_DigSignal_t));
    if(!(*sig)){
        int err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    return 0;
}

int DSPPG__Signals__DigSignal__Init_prealloc(DSPPG_DigSignal_t **sig, 
                                             size_t len,
                                             payloadType_t *data)
{
    if(!data){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, EFAULT);
        return err;
    }
    (*sig) = calloc(1, sizeof(DSPPG_DigSignal_t));
    if(!(*sig)){
        int err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    (*sig)->len = len;
    (*sig)->data = data;
    return 0;
}

int DSPPG__Signals__DigSignal__destroy(DSPPG_DigSignal_t **cont)
{
    if(*cont){
        free(*cont);
        *cont = NULL;
        return 0;
    }else{
        return EFAULT;
    }
}