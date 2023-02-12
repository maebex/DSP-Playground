#include "Statistics.h"


int DSPPG__Statistics__StatCont__Init(DSPPG_StatCont_t **cont,
                                      DSPPG_DigSignal_t * const sig)
{

    *cont = calloc(1, sizeof(DSPPG_DigSignal_t));
    if(!cont){
        int err = ENOMEM;
        log_error("%s %d", __FUNCTION__, err);
        return err;
    }

    (*cont)->signal = sig;

    return 0;
}

int DSPPG__Statistics__StatCont__destroy(DSPPG_StatCont_t **cont)
{
    if(*cont){
        free(*cont);
        *cont = NULL;
        return 0;
    }else{
        return EFAULT;
    }
}

int DSPPG__Statistics__StatCont__calcMean(DSPPG_StatCont_t *cont)
{
    if(!cont){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, EFAULT);
        return err;
    }

    if(0 == cont->signal->len){
        int err = EFAULT;
        log_error("%s %d", __FUNCTION__, EFAULT);
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
        log_error("%s %d", __FUNCTION__, EFAULT);
        return err;
    }

    cont->mean *= cont->signal->len;

    payloadType_t tmp = 0;
    for(int i=cont->signal->len; i<(cont->signal->len+n); i++){
        tmp += cont->signal->data[i];
    }
    cont->mean += tmp;
    cont->signal->len += n;
    cont->mean /= cont->signal->len;

}
