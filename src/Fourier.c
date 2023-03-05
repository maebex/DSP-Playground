
#include "Fourier.h"


/* Real DFT */



int DSPPG__Fourier__realDFT__analyze(DSPPG_Spectrum_t *spectrum, 
                                     DSPPG_Signal_t *signal,
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
        err = cround(&(spectrum->cvalue[m]), DSPPG_DFT_DOUBLE_DELTA);

        // Calculate magnitude and phase
        err = DSPPG__Signals__Spectrum__calcMagPha(spectrum);

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


int DSPPG__Fourier__realDFT__synthesize(DSPPG_Signal_t *signal,
                                        DSPPG_Spectrum_t *spectrum)
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


int DSPPG__Fourier__realDFT__destroy(DSPPG_Spectrum_t *spectrum)
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


int DSPPG__Fourier__realDFT__printRect(DSPPG_Spectrum_t *spectrum)
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

int DSPPG__Fourier__realDFT__printPolar(DSPPG_Spectrum_t *spectrum)
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




/* FFT */
