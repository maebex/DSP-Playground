
#include "DFT.h"



int DSPPG__Transformations__realDFT_Decomposition_decompose(DSPPG_DigSignal_FD_t *decomposition, 
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


int DSPPG__Transformations__realDFT_Decomposition_destroy(DSPPG_DigSignal_FD_t *decomposition)
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


int DSPPG__Transformations__realDFT_Decomposition_printRect(DSPPG_DigSignal_FD_t *decomposition)
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

int DSPPG__Transformations__realDFT_Decomposition_printPolar(DSPPG_DigSignal_FD_t *decomposition)
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



#ifdef GNUPLOT_IS_INSTALLED


void DSPPG__Transformations__realDFT_Decomposition_plotSpectrum(DSPPG_DigSignal_FD_t *decomposition,
                                                                const char * const path)
{
    if(!path || !decomposition){
        log_error("%s %d", __FUNCTION__, EFAULT);
        return;
    }
    const size_t MAXLEN = 1000;
    const size_t pathLen = strnlen(path, MAXLEN);  // length of path to directory
    size_t fnameLen;  // length of filename
    FILE *gnuplot = NULL;

    /* REAL PART*/
    char fname_rect_Re[] = "DFT_Real.png";
    fnameLen = strnlen(fname_rect_Re, MAXLEN);
    char rect_Re[pathLen+fnameLen+1];
    memset(rect_Re, 0, pathLen+fnameLen+1);
    memcpy(rect_Re, path, pathLen);
    strcat(rect_Re, fname_rect_Re);
    gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set terminal png size 1200,900;");
    fprintf(gnuplot, "set output '%s';", rect_Re);
    fprintf(gnuplot, "set xlabel 'Cos Frequency component';");
    fprintf(gnuplot, "set ylabel 'Amplitude';");
    fprintf(gnuplot, "plot '-'\n");
    for (int i = 0; i < decomposition->numComponents; i++)
        fprintf(gnuplot, "%d %lf\n", i, decomposition->real[i]);
    fflush(gnuplot);
    fclose(gnuplot);
    
    /* IMAGINARY PART*/
    char fname_rect_Im[] = "DFT_Imaginary.png";
    fnameLen = strnlen(fname_rect_Im, MAXLEN);
    char rect_Im[pathLen+fnameLen+1];
    memset(rect_Im, 0, pathLen+fnameLen+1);
    memcpy(rect_Im, path, pathLen);
    strcat(rect_Im, fname_rect_Im);
    gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set terminal png size 1200,900;");
    fprintf(gnuplot, "set output '%s';", rect_Im);
    fprintf(gnuplot, "set yrange [-5:5];");
    fprintf(gnuplot, "set xlabel 'Sin Frequency component';");
    fprintf(gnuplot, "set ylabel 'Amplitude';");
    fprintf(gnuplot, "plot '-'\n");
    for (int i = 0; i < decomposition->numComponents; i++)
        fprintf(gnuplot, "%d %lf\n", i, decomposition->imaginary[i]);
    fflush(gnuplot);
    fclose(gnuplot);







}



#endif /* GNUPLOT_IS_INSTALLED */
