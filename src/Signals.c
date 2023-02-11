
#include "Signals.h"

int DSPPG__Signals__Signal_Int32__Init_empty(DSPPG_Signal_Int32 *sig)
{
    sig = calloc(1, sizeof(DSPPG_Signal_Int32));
    if(!sig){
        int err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    return 0;
}

int DSPPG__Signals__Signal_Int32__Init_prealloc(DSPPG_Signal_Int32 *sig, 
                                                size_t len, 
                                                int32_t *data)
{
    if(!data){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, EFAULT);
        return err;
    }
    sig = calloc(1, sizeof(DSPPG_Signal_Int32));
    if(!sig){
        int err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    sig->len = len;
    sig->data = data;
    return 0;
}
