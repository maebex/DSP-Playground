#ifndef FCFCCEF9_F5AC_4F02_86D8_1514E83FC384
#define FCFCCEF9_F5AC_4F02_86D8_1514E83FC384

#include <globals.h>



/**
 * @details Contains measurement data
 * 
*/
typedef struct {
    size_t len;         // Number of samples in data
    int32_t *data;      // Sampled data
    uint32_t smpl_rate  // Sample rate
}DSPPG_Signal_Int32;

/**
 * @details Init an empty DSPPG_Signal_Int32 structure
 * 
 * @param[out] sig, pointer to structure for which memory is allocated (heap)
 * 
 * @return ENOMEM if memory error
*/
int DSPPG__Signals__Signal_Int32__Init_empty(DSPPG_Signal_Int32 *sig);

/**
 * @details Init a DSPPG_Signal_Int32 structure from an array of already allocated data.
 *          The user has to ensure that *data remains in scope
 * 
 * @param[out] sig, pointer to structure for which memory is allocated (heap)
 * @param[in] len, length of data, user has to ensure that 
 * @param[in] data, pointer to data, must not be NULL
 * 
 * @return EFAULT if data is false,
 *         ENOMEM if memory error
 * 
*/
int DSPPG__Signals__Signal_Int32__Init_prealloc(DSPPG_Signal_Int32 *sig, 
                                                size_t len, 
                                                int32_t *data);

/**
 * TODO
*/
int DSPPG__Signals__Signal_Int32__Init_fromFile(DSPPG_Signal_Int32 *sig, 
                                                size_t len, 
                                                FILE *f);



#endif /* FCFCCEF9_F5AC_4F02_86D8_1514E83FC384 */
