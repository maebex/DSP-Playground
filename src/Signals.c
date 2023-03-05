
#include "Signals.h"


/* SIGNAL */

int DSPPG__Signals__Signal__setData(DSPPG_Signal_t *sig, 
                                    size_t len,
                                    DSPPG_Signal_payloadType_t *data,
                                    int32_t *sampleNum)
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
    sig->sampleNum = sampleNum;

    return 0;
}



int DSPPG__Signals__Signal__convoluteIn(DSPPG_Signal_t *out,
                                        DSPPG_Signal_t *in,
                                        DSPPG_Signal_t *filter)
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


int DSPPG__Signals__Signal__convoluteOut(DSPPG_Signal_t *out,
                                         DSPPG_Signal_t *in,
                                         DSPPG_Signal_t *filter)
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

int DSPPG__Signals__Signal__correlate(DSPPG_Signal_t *out,
                                      DSPPG_Signal_t *in,
                                      DSPPG_Signal_t *filter)
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


void DSPPG__Signals__Signal__destroy(DSPPG_Signal_t *sig)
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



int DSPPG__Signals__Signal__generateNoise(DSPPG_Signal_t *out,
                                          float mean, 
                                          float std,
                                          size_t len,
                                          int32_t *sampleNum)
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
    out->sampleNum = sampleNum;

    return err;
}

void DSPPG__Signals__Signal__toJSON(DSPPG_Signal_t *signal,
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


/* SPECTRUM */



int DSPPG__Signals__Spectrum__setData(DSPPG_Spectrum_t *spectrum,
                                      size_t len,
                                      double *real,
                                      double *imaginary)
{ 
    int err = 0;
    if(!spectrum || !real || !imaginary){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    spectrum->cvalue = calloc(len, sizeof *(spectrum->cvalue));
    if(!spectrum->cvalue){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        goto cleanup;
    }

    spectrum->magnitude = calloc(len, sizeof *(spectrum->magnitude));
    if(!spectrum->magnitude){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        goto cleanup;
    }

    spectrum->phase = calloc(len, sizeof *(spectrum->phase));
    if(!spectrum->phase){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        goto cleanup;
    }

    spectrum->numComponents = len;

    for(int i=0; i<spectrum->numComponents; i++){
        spectrum->cvalue[i] += (real[i] + I*imaginary[i]);
    }

    err = DSPPG__Signals__Spectrum__calcMagPha(spectrum);


    return err;

cleanup:
    if(spectrum->cvalue){
        free(spectrum->cvalue);
        spectrum->cvalue = NULL;
    }
    if(spectrum->magnitude){
        free(spectrum->magnitude);
        spectrum->magnitude = NULL;
    }
    if(spectrum->phase){
        free(spectrum->phase);
        spectrum->phase = NULL;
    }
    
    spectrum->numComponents = 0;

    return err;
}



int DSPPG__Signals__Spectrum__calcMagPha(DSPPG_Spectrum_t *spectrum)
{
    int err = 0;
    if(!spectrum || !spectrum->cvalue){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    
    for(int i=0; i<spectrum->numComponents; i++){
        spectrum->magnitude[i] = cabs(spectrum->cvalue[i]);
        spectrum->phase[i] = carg(spectrum->cvalue[i]);
    }

    return err;
}





void DSPPG__Signals__Spectrum__toJSON(DSPPG_Spectrum_t *spectrum,
                                      const char * const path)
{
    if(!path || !spectrum){
        log_error("%s %d", __FUNCTION__, EFAULT);
        return;
    }
    const size_t MAXLEN = 1000;
    const size_t pathLen = strnlen(path, MAXLEN);  // length of path to directory
    size_t fnameLen;  // length of filename

    char fname[] = "/spectrum_data.json";
    fnameLen = strnlen(fname, MAXLEN);
    char fullPathName[pathLen+fnameLen+1];
    memset(fullPathName, 0, pathLen+fnameLen+1);
    memcpy(fullPathName, path, pathLen);
    strcat(fullPathName, fname);

    //to store to JSON we first put the real and imaginary parts into separated arrays
    double rearr[spectrum->numComponents];
    double imarr[spectrum->numComponents];
    for(int i=0; i<spectrum->numComponents; i++){
        rearr[i] =  creal(spectrum->cvalue[i]);
        imarr[i] =  cimag(spectrum->cvalue[i]);
    }

    /* General */
    cJSON *data = cJSON_CreateObject();
    
    cJSON_AddStringToObject(data, "PlotType", PLOT_TYPE_DECOMPOSITION);
    cJSON_AddNumberToObject(data, "NumComponents", spectrum->numComponents);
    cJSON_AddNumberToObject(data, "SamplingRate", spectrum->samplingRate);

    cJSON *payload = cJSON_CreateObject();
    cJSON_AddItemToObject(data, "Payload", payload);

    /* Rectangular */
    cJSON *rectangular = cJSON_CreateObject();

    cJSON *real = cJSON_CreateDoubleArray(rearr, spectrum->numComponents);
    cJSON_AddItemToObject(rectangular, "Real", real);

    cJSON *imaginary = cJSON_CreateDoubleArray(imarr, spectrum->numComponents);
    cJSON_AddItemToObject(rectangular, "Imaginary", imaginary);

    cJSON_AddItemToObject(payload, "Rectangular", rectangular);

    /* Polar */
    cJSON *polar = cJSON_CreateObject();

    cJSON *magnitude = cJSON_CreateFloatArray(spectrum->magnitude, spectrum->numComponents);
    cJSON_AddItemToObject(polar, "Magnitude", magnitude);

    cJSON *phase = cJSON_CreateFloatArray(spectrum->phase, spectrum->numComponents);
    cJSON_AddItemToObject(polar, "Phase", phase);

    cJSON_AddItemToObject(payload, "Polar", polar);

    /* Write */
    char *asString = NULL;
    asString = cJSON_Print(data);
    cJSON_Delete(data);

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


