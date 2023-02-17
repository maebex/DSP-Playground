
#include "Signals.h"


int DSPPG__Signals__DigSignal__setData(DSPPG_DigSignal_t *sig, 
                                       size_t len,
                                       DSPPG_DigSignal_payloadType_t *data)
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



int DSPPG__Signals__DigSignal__convoluteIn(DSPPG_DigSignal_t *out,
                                           DSPPG_DigSignal_t *in,
                                           DSPPG_DigSignal_t *filter)
{
    int err;
    if(!in || !out || !in->data || !filter->data || 0 == in->len || 0 == filter->len){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    unsigned int lenOut = in->len + filter->len - 1; // length of the output signal = length of the input signal + length of filter - 1
    out->data = calloc(lenOut, sizeof *(out->data));
    out->len = lenOut;
    if(!out->data){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    for(int i=0; i<in->len; i++){  // loop over input signal
        for(int j=0; j<filter->len; j++){ // loop over filter
            out->data[i+j] += in->data[i] * filter->data[j];
        }
    }

    return 0;
}


int DSPPG__Signals__DigSignal__convoluteOut(DSPPG_DigSignal_t *out,
                                            DSPPG_DigSignal_t *in,
                                            DSPPG_DigSignal_t *filter)
{
    int err;
    if(!in || !out || !in->data || !filter->data || 0 == in->len || 0 == filter->len){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    unsigned int lenOut = in->len + filter->len - 1; // length of the output signal = length of the input signal + length of filter - 1
    out->data = calloc(lenOut, sizeof *(out->data));
    out->len = lenOut;
    if(!out->data){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    for(int i=0; i<out->len; i++){  // loop over output signal
        for(int j=0; j<filter->len; j++){ // loop over filter
            if(((i-j)<0) || ((i-j)>(in->len-1))){
                continue;
            }
            out->data[i] += in->data[i-j] * filter->data[j];
        }
    }

    return 0;
}

int DSPPG__Signals__DigSignal__correlate(DSPPG_DigSignal_t *out,
                                         DSPPG_DigSignal_t *in,
                                         DSPPG_DigSignal_t *filter)
{
    int err;
    if(!in || !out || !in->data || !filter->data || 0 == in->len || 0 == filter->len){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    unsigned int lenOut = in->len + filter->len; // length of the output signal = length of the input signal + length of filter
    out->data = calloc(lenOut, sizeof *(out->data));
    out->len = lenOut;
    if(!out->data){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    for(int i=0; i<out->len; i++){  // loop over output signal
        for(int j=0; j<filter->len; j++){ // loop over filter
            out->data[i] += in->data[i+j] * filter->data[j];
        }
    }

    return 0;
}


void DSPPG__Signals__DigSignal__destroy(DSPPG_DigSignal_t *sig)
{
    if(sig->data){
        free(sig->data);
        sig->data = NULL;
    }
}

int DSPPG__Signals__DigSignal__generateNoise(DSPPG_DigSignal_t *out,
                                                  uint32_t mean, 
                                                  double_t sigma,
                                                  size_t len)
{
    int err;
    if(!out || 0 == len){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    out->data = calloc(len, sizeof *(out->data));
    if(!out->data)
    {
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    out->len = len;
    for(int i=0; i<len; i++){
        
    }

    return err;
}

