
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
    // length of the output signal = length of the input signal + length of filter - 1
    unsigned int lenOut = in->len + filter->len - 1; 
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
    // length of the output signal = length of the input signal + length of filter - 1
    unsigned int lenOut = in->len + filter->len - 1; 
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
    // length of the output signal = length of the input signal + length of filter
    unsigned int lenOut = in->len + filter->len; 
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
                                             double_t mean, 
                                             double_t std,
                                             size_t len)
{
    int err = 0;
    // Number of values added, has to be even - increase for better distribution resolution
    unsigned int num_iters = 12;  
    if(num_iters%2){
        num_iters++;
    }
    if(!out || 0 == len || 0 > std){
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
    for(int i=0; i<len; i++){  // samples
        for (int j=0; j<num_iters; j++){
            out->data[i] += DSPPG__Helpers__genRand(1.0);

        }
        out->data[i] -= (num_iters>>1);
        out->data[i] *= std;
        out->data[i] += mean;
    }

    return err;
}




void DSPPG__Signals__DigSignal__plotData(DSPPG_DigSignal_t *sig,
                                         const char *fpath)
{
    FILE *gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set terminal png size 1200,900;");
    fprintf(gnuplot, "set output '%s';", fpath);
    fprintf(gnuplot, "plot '-'\n");
    for (int i = 0; i < sig->len; i++)
        fprintf(gnuplot, "%d %lf\n", i, sig->data[i]);
    fprintf(gnuplot, "e\n");
    fflush(gnuplot);

}





