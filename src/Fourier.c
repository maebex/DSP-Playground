
#include "Fourier.h"


/* Real DFT */

int DSPPG__Fourier__realDFT__analyze(DSPPG_DigSignal_FD_t *decomposition, 
                                     DSPPG_DigSignal_TD_t *signal,
                                     uint32_t samplingRate)
{
    int err = 0;
    if(!decomposition || !signal || !signal->data || 0==signal->len){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    size_t len = signal->len; 
    decomposition->numComponents = len;
    decomposition->signal = signal;
    decomposition->samplingRate = samplingRate;

    // allocate memory for DFT components
    decomposition->cvalue = calloc(len, sizeof *(decomposition->cvalue));
    if(!decomposition->cvalue){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        goto cleanup;
    }
    decomposition->magnitude = calloc(len, sizeof *(decomposition->magnitude));
    if(!decomposition->magnitude){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        goto cleanup;
    }
    decomposition->phase = calloc(len, sizeof *(decomposition->phase));
    if(!decomposition->phase){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        goto cleanup;
    }

    // Perform decomposition
    double tmpFac;
    double complex ctemp;
    for(int m=0; m<decomposition->numComponents; m++){ // frequency components
        for(int n=0; n<decomposition->numComponents; n++){  // samples
        	tmpFac = (double)n*(double)m/(double)decomposition->numComponents;
            ctemp = cos(2.*M_PI*tmpFac) - sin(2.*M_PI*tmpFac)*I;
            decomposition->cvalue[m] += (decomposition->signal->data[n] * ctemp);
        }

        // Round
        err = croundf(&(decomposition->cvalue[m]), DSPPG_DFT_DOUBLE_DELTA);

        // Calculate magnitude and phase
        decomposition->magnitude[m] = cabs(decomposition->cvalue[m]);
        decomposition->phase[m] = carg(decomposition->cvalue[m]);
        double re = creal(decomposition->cvalue[m]);
        double im = cimag(decomposition->cvalue[m]);
        double res = decomposition->phase[m];
    }
    return err;

cleanup: 

    if(decomposition->magnitude){
        free(decomposition->magnitude);
        decomposition->magnitude = NULL;
    }
    if(decomposition->phase){
        free(decomposition->phase);
        decomposition->phase = NULL;
    }
    return err;
}


int DSPPG__Fourier__realDFT__synthesize(DSPPG_DigSignal_TD_t *signal,
                                        DSPPG_DigSignal_FD_t *decomposition)
{
    int err = 0;
    if(!decomposition || !signal || !decomposition->cvalue || 0==decomposition->numComponents){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    signal->len = decomposition->numComponents;
    // allocate memory for samples
    signal->data = calloc(signal->len, sizeof *(signal->data));
    if(!signal->data){
        err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    double tmpFac;
    double tmpAcc;
    for(int n=0; n<signal->len; n++){
        tmpAcc = 0.0;
        for(int m=0; m<decomposition->numComponents; m++){
        	tmpFac = (double)n*(double)m/(double)signal->len;
            tmpAcc += (creal(decomposition->cvalue[m])*cos(2.*M_PI*tmpFac)) + (cimag(decomposition->cvalue[m])*sin(2.*M_PI*tmpFac));
        }
        signal->data[n] = tmpAcc / signal->len;
    }

    return 0;
}




int DSPPG__Fourier__realDFT__destroy(DSPPG_DigSignal_FD_t *decomposition)
{
    int err = 0;
    if(!decomposition){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    if(decomposition->cvalue){
        free(decomposition->cvalue);
        decomposition->cvalue = NULL;
    }
    if(decomposition->magnitude){
        free(decomposition->magnitude);
        decomposition->magnitude = NULL;
    }
    if(decomposition->phase){
        free(decomposition->phase);
        decomposition->phase = NULL;
    }
    return err;
}


int DSPPG__Fourier__realDFT__printRect(DSPPG_DigSignal_FD_t *decomposition)
{
    int err = 0;
    if(!decomposition || !decomposition->cvalue){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    printf("\nRe:\t");
    for (int i=0; i<decomposition->numComponents; i++){
        printf("%d:%f\t|\t", i, creal(decomposition->cvalue[i]));
    }
    printf("\nIm:\t");
    for (int i=0; i<decomposition->numComponents; i++){
        printf("%d:%f\t|\t", i, cimag(decomposition->cvalue[i]));
    }
    printf("\n\n");

    return err;

}

int DSPPG__Fourier__realDFT__printPolar(DSPPG_DigSignal_FD_t *decomposition)
{
    int err = 0;
    if(!decomposition || !decomposition->cvalue){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    printf("\nMagnitude:\t");
    for (int i=0; i<decomposition->numComponents; i++){
        printf("%d:%f\t|\t", i, decomposition->magnitude[i]);
    }
    printf("\nPhase:\t");
    for (int i=0; i<decomposition->numComponents; i++){
        printf("%d:%f\t|\t", i, decomposition->phase[i]);
    }
    printf("\n\n");

    return err;

}


void DSPPG__Fourier__realDFT__toJSON(DSPPG_DigSignal_FD_t *decomposition,
                                     const char * const path)
{
    if(!path || !decomposition){
        log_error("%s %d", __FUNCTION__, EFAULT);
        return;
    }
    const size_t MAXLEN = 1000;
    const size_t pathLen = strnlen(path, MAXLEN);  // length of path to directory
    size_t fnameLen;  // length of filename

    char fname[] = "/decomposition_data.json";
    fnameLen = strnlen(fname, MAXLEN);
    char fullPathName[pathLen+fnameLen+1];
    memset(fullPathName, 0, pathLen+fnameLen+1);
    memcpy(fullPathName, path, pathLen);
    strcat(fullPathName, fname);

    //to store to JSON we first put the real and imaginary parts into separated arrays
    double rearr[decomposition->numComponents];
    double imarr[decomposition->numComponents];
    for(int i=0; i<decomposition->numComponents; i++){
        rearr[i] =  creal(decomposition->cvalue[i]);
        imarr[i] =  cimag(decomposition->cvalue[i]);
    }

    /* General */
    cJSON *data = cJSON_CreateObject();
    
    cJSON_AddStringToObject(data, "PlotType", PLOT_TYPE_DECOMPOSITION);
    cJSON_AddNumberToObject(data, "NumComponents", decomposition->numComponents);
    cJSON_AddNumberToObject(data, "SamplingRate", decomposition->samplingRate);

    cJSON *payload = cJSON_CreateObject();
    cJSON_AddItemToObject(data, "Payload", payload);

    /* Rectangular */
    cJSON *rectangular = cJSON_CreateObject();

    cJSON *real = cJSON_CreateDoubleArray(rearr, decomposition->numComponents);
    cJSON_AddItemToObject(rectangular, "Real", real);

    cJSON *imaginary = cJSON_CreateDoubleArray(imarr, decomposition->numComponents);
    cJSON_AddItemToObject(rectangular, "Imaginary", imaginary);

    cJSON_AddItemToObject(payload, "Rectangular", rectangular);

    /* Polar */
    cJSON *polar = cJSON_CreateObject();

    cJSON *magnitude = cJSON_CreateFloatArray(decomposition->magnitude, decomposition->numComponents);
    cJSON_AddItemToObject(polar, "Magnitude", magnitude);

    cJSON *phase = cJSON_CreateFloatArray(decomposition->phase, decomposition->numComponents);
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



/* FFT */
