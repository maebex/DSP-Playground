#ifndef FCFCCEF9_F5AC_4F02_86D8_1514E83FC384
#define FCFCCEF9_F5AC_4F02_86D8_1514E83FC384

#include "globals.h"

typedef int32_t DSPPG_DigSignal_payloadType_t;



/**
 * @brief Contains measurement data
 * 
*/
typedef struct {
    size_t len;                 // Number of samples in data
    DSPPG_DigSignal_payloadType_t *data;        // Sampled data
}DSPPG_DigSignal_t;



/**
 * @brief Init a DSPPG_DigSignal structure from an array of already allocated data.
 * 
 * @param[out] sig pointer to structure for which data is set
 * @param[in] len length of data, user has to ensure that
 * @param[in] data pointer to data, must not be NULL
 * 
 * @return EFAULT if sig is NULL,
 *         0 else
 * 
*/
int DSPPG__Signals__DigSignal__setData(DSPPG_DigSignal_t *sig, 
                                       size_t len,
                                       DSPPG_DigSignal_payloadType_t *data);



/**
 * @brief Convolute a signal with a filter using the input side algorithm
 * 
 * @details This function allocates memory on the heap here: res->data.
 *          The user hgas to ensure that this data is freed if not needed anymore by calling DSPPG__Signals__DigSignal__destroy
 *         
 * 
 * @param[in] in signal that is convoluted 
 * @param[in] filter filter that is used
 * @param[out] out convoluted signal
 * 
*/
int DSPPG__Signals__DigSignal__convoluteIn(DSPPG_DigSignal_t *out,
                                           DSPPG_DigSignal_t *in,
                                           DSPPG_DigSignal_t *filter);


/**
 * @brief Convolute a signal with a filter using the outsode side algorithm
 * 
 * @details This function allocates memory on the heap here: res->data.
 *          The user hgas to ensure that this data is freed if not needed anymore by calling DSPPG__Signals__DigSignal__destroy
 *         
 * 
 * @param[in] in signal that is convoluted 
 * @param[in] filter filter that is used
 * @param[out] out convoluted signal
 * 
*/
int DSPPG__Signals__DigSignal__convoluteOut(DSPPG_DigSignal_t *out,
                                            DSPPG_DigSignal_t *in,
                                            DSPPG_DigSignal_t *filter);


/**
 * @brief Convolute 
 * 
*/
int DSPPG__Signals__DigSignal__correlate(DSPPG_DigSignal_t *out,
                                         DSPPG_DigSignal_t *in,
                                         DSPPG_DigSignal_t *filter);



/**
 * @brief Free memory allocated dynamically by DSPPG__Signals__DigSignal__convoluteIn()
 * 
*/
void DSPPG__Signals__DigSignal__destroy(DSPPG_DigSignal_t *sig);


/**
 * @brief Generate a signal of gaussian distributed noise
 *
 * @param[in] mean
 * @param[in] sigma
 * @param[in] len number of samples
 * @param[out] out, pointer to signal
 *
 * @return
 *
 */
int DSPPG__Signals__DigSignal__genGaussNoise(DSPPG_DigSignal_t *out,
                                             uint32_t mean, 
                                             double_t sigma,
                                             size_t len);



#endif /* FCFCCEF9_F5AC_4F02_86D8_1514E83FC384 */
