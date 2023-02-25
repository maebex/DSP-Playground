
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
}



int DSPPG__Signals__DigSignal__generateNoise(DSPPG_DigSignal_TD_t *out,
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


#ifdef GNUPLOT_IS_INSTALLED


void DSPPG__Signals__DigSignal__plotData(DSPPG_DigSignal_TD_t *sig,
                                         const char *fpath)
{
    int err;
    if(!fpath || !sig){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    FILE *gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set terminal png size 1200,900;");
    fprintf(gnuplot, "set output '%s';", fpath);
    fprintf(gnuplot, "plot '-'\n");
    for (int i = 0; i < sig->len; i++)
        fprintf(gnuplot, "%d %lf\n", i, sig->data[i]);
    fprintf(gnuplot, "e\n");
    fflush(gnuplot);
    err = fclose(gnuplot);
}



void DSPPG__Signals__DigSignal__plotHist(DSPPG_DigSignal_TD_t *sig,
                                         const char * const pngpath,
                                         const char * const datpath)
{
    int err = 0;
    
    if(!pngpath || !sig || !datpath){
        err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    
    /* Find min and max value - so we know how many classes we need */
    double_t min, max;
    unsigned int idx = 1;
    while(sig->data[0] == sig->data[idx]){
        idx++;
    }
    if(sig->data[0] < sig->data[idx]){
        min = sig->data[0];
        max = sig->data[idx];
    }else{
        min = sig->data[idx];
        max = sig->data[0];
    }
    idx++;
    for(;idx<sig->len; idx++){
        if(sig->data[idx] > max){
            max = sig->data[idx];
        }else if(sig->data[idx] < min){
            min = sig->data[idx];
        }
    }
    min = floor(min);
    max = ceil(max);
    const unsigned int maxnumEntries = max-min+1;

    /* Make hash table for the bars */
    ENTRY e, *ep;
    hcreate(maxnumEntries);
   for (int i = 0; i < sig->len; i++) {
        const unsigned int MAX_STRINGLENGTH = 100;
        char _tmpKeyStr[MAX_STRINGLENGTH];
        memset(_tmpKeyStr, 0, MAX_STRINGLENGTH);
        snprintf(_tmpKeyStr, MAX_STRINGLENGTH-1, "%d", (int)(floor(sig->data[i])));
        e.key = _tmpKeyStr;

        // Check if already there
        ep = hsearch(e, FIND);
        if (NULL == ep){
            ep = hsearch(e, ENTER);
            ep->data = (void*) 1;
        }else{
            ep->data++;
        }

        if (ep == NULL) {
            exit(EXIT_FAILURE);
        }
    }

    /* Fill temporary file with the data */
    const char * const _tmpfname = datpath;
    FILE *_tmpf = fopen(_tmpfname, "w+");
    if(!_tmpf){
        exit(EXIT_FAILURE);
    }
    int _tmpMin = min;
    for (int i = 0; i < sig->len; i++) {

        const unsigned int MAX_STRINGLENGTH = 100;
        char _tmpKeyStr[MAX_STRINGLENGTH];
        memset(_tmpKeyStr, 0, MAX_STRINGLENGTH);
        snprintf(_tmpKeyStr, MAX_STRINGLENGTH-1, "%d", _tmpMin);
        e.key = _tmpKeyStr;

        ep = hsearch(e, FIND);
        if(ep){
            int bla = (long)ep->data;
            err = fprintf(_tmpf, "%d %d %ld\n", i, _tmpMin, (long)ep->data);
        }
        _tmpMin++;
    }
    fflush(_tmpf);

/*
Strangely if we use these commands in gnuplot CLI it works:

reset 
set output '/mnt/c/Users/mbern/Desktop/gplot/hist.png'
set boxwidth 1.0
set style fill solid
set terminal png size 1200,800
set xlabel 'Value'
set ylabel 'Occurences'
plot '/mnt/c/Users/mbern/Desktop/gplot/data.dat' using 2:3 with boxes title "data"
*/

    /* Print plot */
    FILE *gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set output \"%s\";", pngpath);
    fprintf(gnuplot, "set boxwidth 1.0;");
    fprintf(gnuplot, "set style fill solid;");
    fprintf(gnuplot, "set xlabel \"Value\";");
    fprintf(gnuplot, "set ylabel \"Occurences\";");
    fprintf(gnuplot, "set terminal png size 1200,900;");
    fprintf(gnuplot, "plot \"%s\" using 2:3 with boxes;\n",  _tmpfname);
    fflush(gnuplot);

    /* Clean up */
    err = fclose(_tmpf);
    err = fclose(gnuplot);
    hdestroy();

}

#endif /* GNUPLOT_IS_INSTALLED */

