
#include "Fourier.h"


/* Real DFT */


int DSPPG__Fourier__realDFT__calcMagPha(DSPPG_DigSignal_FD_t *spectrum)
{
    int err = 0;
    if(!spectrum || !spectrum->cvalue || !spectrum->magnitude || !spectrum->phase){
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



int DSPPG__Fourier__realDFT__setData(DSPPG_DigSignal_FD_t *spectrum,
                                     size_t len,
                                     double *real,
                                     double *imaginary)
{
    int err = 0;
    if(!spectrum || !real || !imaginary || spectrum->cvalue){
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

    spectrum->numComponents = len;

    for(int i=0; i<spectrum->numComponents; i++){
        spectrum->cvalue[i] += (real[i] + I*imaginary[i]);
    }

    err = DSPPG__Fourier__realDFT__calcMagPha(spectrum);


    return err;

cleanup:
    if(spectrum->cvalue){
        free(spectrum->cvalue);
        spectrum->cvalue = NULL;
    }
    
    spectrum->numComponents = 0;

    return err;
}


int DSPPG__Fourier__realDFT__analyze(DSPPG_DigSignal_FD_t *spectrum, 
                                     DSPPG_DigSignal_TD_t *signal,
                                     uint32_t samplingRate)
{
    int err = 0;
    if(!spectrum || !signal || !signal->data || 0==signal->len){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    size_t len = signal->len; 
    spectrum->numComponents = len;
    spectrum->signal = signal;
    spectrum->samplingRate = samplingRate;

    // allocate memory for DFT components
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

    // Perform spectrum
    double tmpFac;
    double complex ctemp;
    for(int m=0; m<spectrum->numComponents; m++){ // frequency components
        for(int n=0; n<spectrum->numComponents; n++){  // samples
        	tmpFac = (double)n*(double)m/(double)spectrum->numComponents;
            ctemp = cos(2.*M_PI*tmpFac) - sin(2.*M_PI*tmpFac)*I;
            spectrum->cvalue[m] += (spectrum->signal->data[n] * ctemp);
        }

        // Round
        err = croundf(&(spectrum->cvalue[m]), DSPPG_DFT_DOUBLE_DELTA);

        // Calculate magnitude and phase
        err = DSPPG__Fourier__realDFT__calcMagPha(spectrum);

    }
    return err;

cleanup: 

    if(spectrum->magnitude){
        free(spectrum->magnitude);
        spectrum->magnitude = NULL;
    }
    if(spectrum->phase){
        free(spectrum->phase);
        spectrum->phase = NULL;
    }
    return err;
}


int DSPPG__Fourier__realDFT__synthesize(DSPPG_DigSignal_TD_t *signal,
                                        DSPPG_DigSignal_FD_t *spectrum)
{
    int err = 0;
    if(!spectrum || !signal || !spectrum->cvalue || 0==spectrum->numComponents){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    signal->len = spectrum->numComponents;
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
        for(int m=0; m<spectrum->numComponents; m++){
        	tmpFac = (double)n*(double)m/(double)signal->len;
            tmpAcc += (creal(spectrum->cvalue[m])*cos(2.*M_PI*tmpFac)) + (cimag(spectrum->cvalue[m])*sin(2.*M_PI*tmpFac));
        }
        signal->data[n] = tmpAcc / signal->len;
    }

    return 0;
}




int DSPPG__Fourier__realDFT__destroy(DSPPG_DigSignal_FD_t *spectrum)
{
    int err = 0;
    if(!spectrum){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
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
    return err;
}


int DSPPG__Fourier__realDFT__printRect(DSPPG_DigSignal_FD_t *spectrum)
{
    int err = 0;
    if(!spectrum || !spectrum->cvalue){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    printf("\nRe:\t");
    for (int i=0; i<spectrum->numComponents; i++){
        printf("%d:%f\t|\t", i, creal(spectrum->cvalue[i]));
    }
    printf("\nIm:\t");
    for (int i=0; i<spectrum->numComponents; i++){
        printf("%d:%f\t|\t", i, cimag(spectrum->cvalue[i]));
    }
    printf("\n\n");

    return err;

}

int DSPPG__Fourier__realDFT__printPolar(DSPPG_DigSignal_FD_t *spectrum)
{
    int err = 0;
    if(!spectrum || !spectrum->cvalue){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    printf("\nMagnitude:\t");
    for (int i=0; i<spectrum->numComponents; i++){
        printf("%d:%f\t|\t", i, spectrum->magnitude[i]);
    }
    printf("\nPhase:\t");
    for (int i=0; i<spectrum->numComponents; i++){
        printf("%d:%f\t|\t", i, spectrum->phase[i]);
    }
    printf("\n\n");

    return err;

}


void DSPPG__Fourier__realDFT__toJSON(DSPPG_DigSignal_FD_t *spectrum,
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



/* FFT */
