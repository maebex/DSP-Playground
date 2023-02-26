
#include "DFT.h"




int DSPPG__Transformations__realDFT_Decomposition__decompose(DSPPG_DigSignal_FD_t *decomposition, 
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
    float tmpFac;
    for(int m=0; m<decomposition->numComponents; m++){ // frequency components
        for(int n=0; n<decomposition->numComponents; n++){  // samples
        	tmpFac = (float)n*(float)m/(float)decomposition->numComponents;
            decomposition->real[m] += ( decomposition->signal->data[n] * cos(2.*M_PI*tmpFac));
            decomposition->imaginary[m] -= ( decomposition->signal->data[n] * sin(2.*M_PI*tmpFac));
        }

        // Calculate magnitude and phase
        decomposition->magnitude[m] = sqrt(decomposition->real[m]*decomposition->real[m]+decomposition->imaginary[m]*decomposition->imaginary[m]);
        decomposition->phase[m] = atan(decomposition->imaginary[m]/decomposition->real[m]);
    }

    return err;

cleanup: 
    if(decomposition->real){
        free(decomposition->real);
        decomposition->real = NULL;
    }
    if(decomposition->imaginary){
        free(decomposition->imaginary);
        decomposition->imaginary = NULL;
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


int DSPPG__Transformations__realDFT_Decomposition__destroy(DSPPG_DigSignal_FD_t *decomposition)
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


int DSPPG__Transformations__realDFT_Decomposition__printRect(DSPPG_DigSignal_FD_t *decomposition)
{
    int err = 0;
    if(!decomposition || !decomposition->real || !decomposition->imaginary){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    printf("\nRe:\t");
    for (int i=0; i<decomposition->numComponents; i++){
        printf("%d:%f\t|\t", i, decomposition->real[i]);
    }
    printf("\nIm:\t");
    for (int i=0; i<decomposition->numComponents; i++){
        printf("%d:%f\t|\t", i, decomposition->imaginary[i]);
    }
    printf("\n\n");

    return err;

}

int DSPPG__Transformations__realDFT_Decomposition__printPolar(DSPPG_DigSignal_FD_t *decomposition)
{
    int err = 0;
    if(!decomposition || !decomposition->real || !decomposition->imaginary){
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


void DSPPG__Transformations__realDFT_Decomposition__toJSON(DSPPG_DigSignal_FD_t *decomposition,
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

    /* General */
    cJSON *data = cJSON_CreateObject();
    
    cJSON_AddStringToObject(data, "plotType", PLOT_TYPE_DECOMPOSITION);
    cJSON_AddNumberToObject(data, "numComponents", decomposition->numComponents);
    cJSON_AddNumberToObject(data, "samplingRate", decomposition->samplingRate);

    cJSON *payload = cJSON_CreateObject();
    cJSON_AddItemToObject(data, "Payload", payload);

    /* Rectangular */
    cJSON *rectangular = cJSON_CreateObject();

    cJSON *real = cJSON_CreateFloatArray(decomposition->real, decomposition->numComponents);
    cJSON_AddItemToObject(rectangular, "Real", real);

    cJSON *imaginary = cJSON_CreateFloatArray(decomposition->imaginary, decomposition->numComponents);
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


