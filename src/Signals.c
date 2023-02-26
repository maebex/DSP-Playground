
#include "Signals.h"


int DSPPG__Signals__DigSignal__setData(DSPPG_DigSignal_TD_t *sig, 
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
    sig->sampleNum = NULL; // TODO
    return 0;
}



int DSPPG__Signals__DigSignal__convoluteIn(DSPPG_DigSignal_TD_t *out,
                                           DSPPG_DigSignal_TD_t *in,
                                           DSPPG_DigSignal_TD_t *filter)
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


int DSPPG__Signals__DigSignal__convoluteOut(DSPPG_DigSignal_TD_t *out,
                                            DSPPG_DigSignal_TD_t *in,
                                            DSPPG_DigSignal_TD_t *filter)
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

int DSPPG__Signals__DigSignal__correlate(DSPPG_DigSignal_TD_t *out,
                                         DSPPG_DigSignal_TD_t *in,
                                         DSPPG_DigSignal_TD_t *filter)
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


void DSPPG__Signals__DigSignal__destroy(DSPPG_DigSignal_TD_t *sig)
{
    if(sig->data){
        free(sig->data);
        sig->data = NULL;
    }
    if(sig->sampleNum){
        free(sig->sampleNum);
        sig->sampleNum = NULL;
    }
}



int DSPPG__Signals__DigSignal__generateNoise(DSPPG_DigSignal_TD_t *out,
                                             float mean, 
                                             float std,
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
    out->sampleNum = NULL; // TODO

    return err;
}

void DSPPG__Signals__DigSignal__toJSON(DSPPG_DigSignal_TD_t *signal,
                                       const char * const path)
{
    if(!path || !signal){
        log_error("%s %d", __FUNCTION__, EFAULT);
        return;
    }
    const size_t MAXLEN = 1000;
    const size_t pathLen = strnlen(path, MAXLEN);  // length of path to directory
    size_t fnameLen;  // length of filename

    char fname[] = "/signal_data.json";
    fnameLen = strnlen(fname, MAXLEN);
    char fullPathName[pathLen+fnameLen+1];
    memset(fullPathName, 0, pathLen+fnameLen+1);
    memcpy(fullPathName, path, pathLen);
    strcat(fullPathName, fname);

    /* General */
    cJSON *json = cJSON_CreateObject();

    cJSON_AddStringToObject(json, "PlotType", PLOT_TYPE_REAL_SIGNAL);
    cJSON_AddNumberToObject(json, "Length", signal->len);
    if(signal->sampleNum){
        cJSON *sampleNum = cJSON_CreateIntArray(signal->sampleNum, signal->len);
        cJSON_AddItemToObject(json, "SampleNum", sampleNum);
    }
    cJSON *data = cJSON_CreateFloatArray(signal->data, signal->len);
    cJSON_AddItemToObject(json, "SampleData", data);

    /* Write */
    char *asString = NULL;
    asString = cJSON_Print(json);
    cJSON_Delete(json);

    FILE *file = fopen(fullPathName, "w+");
    if (!file) {
        log_error("%s could not open file %s", __FUNCTION__, fullPathName);
        return;
    }
    int err = fputs(asString, file);
    if (err == EOF) {
        log_error("%s could not write to file %s", __FUNCTION__, fullPathName);
        return;
    }
    fclose(file);

}


