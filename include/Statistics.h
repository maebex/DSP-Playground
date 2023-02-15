#ifndef C54806C8_EA7C_4093_9F89_2E7B5CD4105A
#define C54806C8_EA7C_4093_9F89_2E7B5CD4105A

#include "globals.h"
#include "Helpers.h"
#include "Signals.h"


/**
 * @brief DSPPG Statistics Container
 * 
*/
typedef struct {
    DSPPG_DigSignal_t *signal;          // Signal
    double mean;                        // Mean
    struct {
        double std;     // Standard Deviation
        double _sumSq;  // Sum of squares
        double _sum;    // Sum
    }std;
}DSPPG_StatCont_t;


// Init
/**
 * @brief Initialize a Statistic Container structure with an already initialized signal of type DSPPG_DigSignal_t
 *
 * @param[out, out] cont, pointer to container that is to be initialized
 * @param[in] sig, pointer to signal
 * 
 * @return EFAULT if cont is NULL, 
 *         0 else
 * 
 * @attention User has to ensure that signal has been properly initialize, preferrably with the dedicated function (see signals.h)
 *  
*/
int DSPPG__Statistics__StatCont__setSignal(DSPPG_StatCont_t *cont,
                                           DSPPG_DigSignal_t * const sig);


// Mean
/**
 * @brief Calculate mean of a signal
 * 
 * @param[in, out] cont, points to statistics container where mean is to be calculated
 * 
 * @return EFAULT if cont is NULL
 *         EFAULT if signal length is 0 (avoid division by zero)
 *         0 else
 * 
*/
int DSPPG__Statistics__StatCont__calcMean(DSPPG_StatCont_t *cont);

/**
 * @brief Update mean of a signal by re-calculating with the past n values
 * 
 * @param[in, out] cont, points to statistics container where mean is to be calculated
 * @param[in] n, number of last samples that will be used for re-calulation
 * 
 * @return TODO
 * 
 * @example if cont contains 5 samples (0, 1, 2, 3, 4) and n is 2, then only sample 3 and 4 will be used for re-calculation
 * 
*/
int DSPPG__Statistics__StatCont__updateMean(DSPPG_StatCont_t *cont,
                                            uint16_t n);


/**
 * @brief Calculate standard deviation of signal
 * 
 * @param[in, out] cont, container which contains signal of which standard deviation is to be calculated
 * 
 * @details Using this formula: sigma^2 = (1/(N-1)) * (sum_of_squares-(sum^2 / N))
 * 
*/
int DSPPG__Statistics__StatCont__calcStd(DSPPG_StatCont_t *cont);

/**
 * @brief Update standard deviation of signal
 * 
 * @param[in, out] cont, container which contains signal of which standard deviation is to be calculated
 * @param[in] n, number of new measurements
 * 
*/
int DSPPG__Statistics__StatCont__updateStd(DSPPG_StatCont_t *cont,
                                           uint16_t n);





#endif /* C54806C8_EA7C_4093_9F89_2E7B5CD4105A */
