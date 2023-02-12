#ifndef C54806C8_EA7C_4093_9F89_2E7B5CD4105A
#define C54806C8_EA7C_4093_9F89_2E7B5CD4105A

#include <globals.h>

#include "Signals.h"

/**
 * @details DSPPG Statistics Container
 * 
*/
typedef struct {
    DSPPG_DigSignal_t *signal;          // Signal
    double mean;                        // Mean
    double var;                         // Variance
    double std;                         // Standard Deviation
}DSPPG_StatCont_t;


// Init
/**
 * @details Initialize a Statistic Container structure with an already initialized signal of type DSPPG_DigSignal_t
 *
 * @param[out] cont, pointer to container that is to be initialized
 * @param[in] sig, pointer to signal
 * 
 * @return EFAULT if sig is NULL, 
 *         EFAULT if sig->data is NOTYPE,
 *         ENOMEM if memory allocation error,
 *         0 else
 * 
 * @attention User has to ensure that signal has been properly initialize, preferrably with the dedicated function (see signals.h)
 *  
*/
int DSPPG__Statistics__StatCont__Init(DSPPG_StatCont_t **cont,
                                      DSPPG_DigSignal_t * const sig);

/**
 * @details Destroy a DSPPG_StatCont_t structure properly. 
 * 
 * @param[in] cont, structure that is to be destroyed
 * 
 * @return EFAULT if cont is NULL,
 *         0 else
 * 
 * @attention User has to ensure that cont->data is handled accordingly, e.g. freed if necessary
 * 
*/
int DSPPG__Statistics__StatCont__destroy(DSPPG_StatCont_t **cont);




// Mean
/**
 * @details Calculate mean of a signal
 * 
 * @param[in] cont, points to statistics container where mean is to be calculated
 * 
 * @return EFAULT if cont is NULL
 *         EFAULT if signal length is 0 (avoid division by zero)
 *         0 else
 * 
*/
int DSPPG__Statistics__StatCont__calcMean(DSPPG_StatCont_t *cont);

/**
 * @details Update mean of a signal by re-calculating with the past n values
 * 
 * @param[in] cont, points to statistics container where mean is to be calculated
 * @param[in] n, number of last samples that will be used for re-calulation
 * 
 * @return TODO
 * 
 * @example if cont contains 5 samples (0, 1, 2, 3, 4) and n is 2, then only sample 3 and 4 will be used for re-calculation
 * 
*/
int DSPPG__Statistics__StatCont__updateMean(DSPPG_StatCont_t *cont,
                                            uint16_t n);


// Variance


// Standard Deviation



#endif /* C54806C8_EA7C_4093_9F89_2E7B5CD4105A */
