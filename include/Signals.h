#ifndef FCFCCEF9_F5AC_4F02_86D8_1514E83FC384
#define FCFCCEF9_F5AC_4F02_86D8_1514E83FC384

#include "globals.h"

typedef int32_t payloadType_t;



/**
 * @brief Contains measurement data
 * 
*/
typedef struct {
    size_t len;                 // Number of samples in data
    payloadType_t *data;        // Sampled data
}DSPPG_DigSignal_t;



/**
 * @brief Init a DSPPG_DigSignal structure from an array of already allocated data.
 * 
 * @param[out] sig, pointer to structure for which data is set
 * @param[in] len, length of data, user has to ensure that
 * @param[in] data, pointer to data, must not be NULL
 * 
 * @return EFAULT if sig is NULL,
 *         0 else
 * 
*/
int DSPPG__Signals__DigSignal__setData(DSPPG_DigSignal_t *sig, 
                                       size_t len,
                                       payloadType_t *data);



/**
 * @brief Convolute a signal with a filter
 * 
 * @details This function allocates memory on the heap here: res->data
 *          After usage the object allocated for *res should be destroyed, e.g. with DSPPG__Signals__DigSignal__destroySigandData
 * 
 * @param[in] signal, signal that is convoluted 
 * @param[in] filter, filter that is used
 * @param[out] res, convoluted signal
 * 
*/
int DSPPG__Signals__DigSignal__convolute(DSPPG_DigSignal_t *res,
                                         DSPPG_DigSignal_t *signal,
                                         DSPPG_DigSignal_t *filter);


#endif /* FCFCCEF9_F5AC_4F02_86D8_1514E83FC384 */
