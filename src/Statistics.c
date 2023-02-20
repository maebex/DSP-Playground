#include "Statistics.h"
#include <math.h>

int DSPPG__Statistics__StatCont__setSignal(DSPPG_StatCont_t *cont,
                                           DSPPG_DigSignal_TD_t * const sig)
{
    if(!cont){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    cont->signal = sig;
    return 0;
}

int DSPPG__Statistics__StatCont__calcMean(DSPPG_StatCont_t *cont)
{
    if(!cont){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    if(0 == cont->signal->len){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    cont->mean = 0;
    for(int i=0; i<cont->signal->len; i++){
        cont->mean += cont->signal->data[i];
    }
    cont->mean /= cont->signal->len;


    return 0;
}

int DSPPG__Statistics__StatCont__updateMean(DSPPG_StatCont_t *cont,
                                            uint16_t n)
{
    if(!cont){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    cont->mean *= cont->signal->len;

    DSPPG_DigSignal_payloadType_t tmp = 0;
    for(int i=cont->signal->len; i<(cont->signal->len+n); i++){
        tmp += cont->signal->data[i];
    }
    cont->mean += tmp;
    cont->signal->len += n;
    cont->mean /= cont->signal->len;
    return 0;
}

int DSPPG__Statistics__StatCont__calcStd(DSPPG_StatCont_t *cont)
{
    double tmp;
    double subtrahend;
    if(0==cont->signal->len){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    cont->std._sumSq = 0.;
    cont->std._sum = 0.;
    for(int i=0; i<cont->signal->len; i++){
        tmp = cont->signal->data[i];
        cont->std._sumSq += tmp*tmp;
        cont->std._sum += tmp;
    }
    subtrahend = (cont->std._sum*cont->std._sum) / cont->signal->len;
    tmp = (1./(cont->signal->len-1)) * (cont->std._sumSq - subtrahend);   // tmp is re-used - now variance
    cont->std.std = sqrt(tmp);
    return 0;
}

int DSPPG__Statistics__StatCont__updateStd(DSPPG_StatCont_t *cont,
                                           uint16_t n)
{
    double tmp;
    double subtrahend;
    if(0==cont->signal->len){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }
    if(0==n){
        return 0;
    }
    for(int i=cont->signal->len-n; i<cont->signal->len; i++){
        tmp = cont->signal->data[i];
        cont->std._sumSq += tmp*tmp;
        cont->std._sum += tmp;
    }
    subtrahend = (cont->std._sum*cont->std._sum) / cont->signal->len;
    tmp = (1./(cont->signal->len-1)) * (cont->std._sumSq - subtrahend);   // tmp is re-used - now variance
    cont->std.std = sqrt(tmp);

    return 0;
}


