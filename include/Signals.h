#ifndef FCFCCEF9_F5AC_4F02_86D8_1514E83FC384
#define FCFCCEF9_F5AC_4F02_86D8_1514E83FC384

#include <globals.h>

typedef int32_t payloadType_t;



/**
 * @details Contains measurement data
 * 
*/
typedef struct {
    size_t len;                 // Number of samples in data
    payloadType_t *data;        // Sampled data
}DSPPG_DigSignal_t;


/* Init */

/**
 * @details Init an empty DSPPG_DigSignal_t structure
 * 
 * @param[out] sig, pointer to structure for which memory is allocated (heap)
 * 
 * @return ENOMEM if memory error,
 *         0 else
*/
int DSPPG__Signals__DigSignal__Init_empty(DSPPG_DigSignal_t **sig);

/**
 * @details Init a DSPPG_DigSignal structure from an array of already allocated data.
 *          The user has to ensure that *data remains in scope
 * 
 * @param[out] sig, pointer to structure for which memory is allocated (heap)
 * @param[in] len, length of data, user has to ensure that
 * @param[in] data, pointer to data, must not be NULL
 * 
 * @return EFAULT if data is false,
 *         ENOMEM if memory error
 *         0 else
 * 
*/
int DSPPG__Signals__DigSignal__Init_prealloc(DSPPG_DigSignal_t **sig, 
                                             size_t len,
                                             payloadType_t *data);

/**
 * @details Destroy object and free memory
 * 
 * @param[in] cont, pointer to object that is to be destroyed
 * 
 * @return EFAULT if *cont is NULL,
 *         0 else
 * 
*/
int DSPPG__Signals__DigSignal__destroy(DSPPG_DigSignal_t **cont);

#endif /* FCFCCEF9_F5AC_4F02_86D8_1514E83FC384 */
