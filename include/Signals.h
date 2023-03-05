#ifndef FCFCCEF9_F5AC_4F02_86D8_1514E83FC384
#define FCFCCEF9_F5AC_4F02_86D8_1514E83FC384

#include "Globals.h"
#include "Helpers.h"

#ifdef GNUPLOT_IS_INSTALLED
#include <search.h>
#endif /* GNUPLOT_IS_INSTALLED */


typedef float DSPPG_Signal_payloadType_t;

/**
 * @brief Time domain signal
*/
typedef struct {
    size_t len;                                 // Number of samples in data
    int32_t *sampleNum;                         // TODO - number/ID of samples corresponding to samples in data
    DSPPG_Signal_payloadType_t *data;        // Sampled data
}DSPPG_Signal_t;


/**
 * @brief Frequency domain spectrum
 * 
*/
typedef struct {
    DSPPG_Signal_t *signal;
    size_t numComponents;
    double complex *cvalue;
    float *magnitude;
    float *phase;
    uint32_t samplingRate;
}DSPPG_Spectrum_t;




/**
 * @brief Init a DSPPG_Signal structure from an array of already allocated data.
 * 
 * @param[out] sig pointer to structure for which data is set
 * @param[in] len length of data, user has to ensure that
 * @param[in] data pointer to data, must not be NULL
 * 
 * @return EFAULT if sig is NULL,
 *         0 else
 * 
*/
int DSPPG__Signals__Signal__setData(DSPPG_Signal_t *sig, 
                                    size_t len,
                                    DSPPG_Signal_payloadType_t *data,
                                    int32_t *sampleNum);



/**
 * @brief Convolute a signal with a filter using the input side algorithm
 * 
 * @details This function allocates memory on the heap here: res->data.
 *          The user hgas to ensure that this data is freed if not needed anymore by calling DSPPG__Signals__Signal__destroy
 *         
 * 
 * @param[in] in signal that is convoluted 
 * @param[in] filter filter that is used
 * @param[out] out convoluted signal
 * 
*/
int DSPPG__Signals__Signal__convoluteIn(DSPPG_Signal_t *out,
                                        DSPPG_Signal_t *in,
                                        DSPPG_Signal_t *filter);


/**
 * @brief Convolute a signal with a filter using the outsode side algorithm
 * 
 * @details This function allocates memory on the heap here: res->data.
 *          The user hgas to ensure that this data is freed if not needed anymore by calling DSPPG__Signals__Signal__destroy
 *         
 * 
 * @param[in] in signal that is convoluted 
 * @param[in] filter filter that is used
 * @param[out] out convoluted signal
 * 
*/
int DSPPG__Signals__Signal__convoluteOut(DSPPG_Signal_t *out,
                                         DSPPG_Signal_t *in,
                                         DSPPG_Signal_t *filter);


/**
 * @brief Convolute 
 * 
*/
int DSPPG__Signals__Signal__correlate(DSPPG_Signal_t *out,
                                      DSPPG_Signal_t *in,
                                      DSPPG_Signal_t *filter);



/**
 * @brief Free memory allocated dynamically for sig->data
 * 
*/
void DSPPG__Signals__Signal__destroy(DSPPG_Signal_t *sig);


/**
 * @brief Generate a signal of gaussian distributed noise.
 * 
 * @details Allocates heap memory for out->data - must be freed afterwards, 
 *          i.e. call DSPPG__Signals__Signal__destroy().
 *          Also it is important that len is sufficiently large for the data to be truly gaussian distributed
 *
 * @param[in] mean
 * @param[in] sigma
 * @param[in] len number of samples
 * @param[out] out, pointer to signal
 *
 * @return EFAULT if out is NULL or len==0,
 *         ERNOMEM if memory error,
 *         0 else
 *
 *  Algorithm taken from The Scientist and Engineer’s Guide to Digital Signal Processing, Steven W. Smith, chapter 2
 * 
 * For each sample in the signal: 
 *   (1) add twelve random numbers
 *   (2) subtract six to make the mean equal to zero
 *   (3) multiply by the standard deviation desired
 *   (4) add the desired mean
 * 
 */
int DSPPG__Signals__Signal__generateNoise(DSPPG_Signal_t *out,
                                          float mean, 
                                          float std,
                                          size_t len, 
                                          int32_t *sampleNum);


/**
 * @brief Store data to JSON file
 * 
 * @param[in] signal pointer to data structure
 * @param[in] path, Data is stored here: "{path}/signal_data.json"
 * 
 * @details The data can be fed into tools/DSPPG_Plot.py as input file 
 * 
*/
void DSPPG__Signals__Signal__toJSON(DSPPG_Signal_t *signal,
                                    const char * const path);

/**
 * @brief Add two signals
 * 
 * TODO
*/
int DSPPG__Signals__Signal__add(DSPPG_Signal_t **out,
                                DSPPG_Signal_t *sig1,
                                DSPPG_Signal_t *sig2);

/**
 * @brief Check if signal is real i.e. symmetrical to sample 0
 * 
 * TODO
*/
int DSPPG__Signals__Signal__isReal(DSPPG_Signal_t *sig);




/**
 * @brief Set data of spectrum manually
 * 
 * @param[out] spectrum data is set here
 * @param[in] real array of cos parts
 * @param[in] imaginary array of sin parts
 * 
 * @details This functions also allocates memory for spectrum->magnitude and spectrum->phase and sets it to 0. 
 *          Should be calculated with DSPPG__Fourier__realDFT__calcMagPha()
 * 
 * @return ENOMEM if memory error,
 *         EFAULT if spectrum is NULL, real is NULL or imaginary is NULL or spectrum->cvalue is not NULL
 *         0 else
 * 
 * 
*/

int DSPPG__Signals__Spectrum__setData(DSPPG_Spectrum_t *spectrum,
                                      size_t len,
                                      double *real,
                                      double *imaginary);

 
/**
 * @brief Store data to JSON file
 * 
 * @param[in] spectrum pointer to data structure
 * @param[in] path, Data is stored here: "{path}/spectrum_data.json"
 * 
 * @details The data can be fed into tools/DSPPG_Plot.py as input file 
 * 
*/
void DSPPG__Signals__Spectrum__toJSON(DSPPG_Spectrum_t *spectrum,
                                      const char * const path);

/**
 * @brief Calculate magnitude and phase angle
 * 
 * @param[in, out] spectrum pointer to structure
 * 
 * @return EFAULT if !spectrum or !spectrum->cval,
 *         0 else
 * 
 * 
*/
int DSPPG__Signals__Spectrum__calcMagPha(DSPPG_Spectrum_t *spectrum);




#endif /* FCFCCEF9_F5AC_4F02_86D8_1514E83FC384 */
