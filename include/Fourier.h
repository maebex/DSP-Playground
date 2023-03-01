#ifndef A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B
#define A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B

#include "Globals.h"
#include "Signals.h"


#if defined __STDC_IEC_559_COMPLEX__ || __STDC_IEC_60559_COMPLEX__


/* DFT */

/**
 * @brief Frequency domain signal
 * 
 * 
*/
typedef struct {
    DSPPG_DigSignal_TD_t *signal;
    size_t numComponents;
    // float *real;
    // float *imaginary;
    double complex *cvalue;
    float *magnitude;
    float *phase;
    uint32_t samplingRate;
}DSPPG_DigSignal_FD_t;


/* Real DFT */


/**
 * @brief Decompose a signal into its frequency components via DFT
 * 
 * @param[out] decomposition contains the signal and the signal components after performing DFT
 * @param[in] signal discrete signal
 * @param[in] samplingRate rate of which the samples were obtained in Hz, may be 0 if not specified 
 * 
 * @return ENOMEM if memory error,
 *         0 else
 * 
 * 
*/
int DSPPG__Fourier__realDFT__analyze(DSPPG_DigSignal_FD_t *decomposition, 
                                     DSPPG_DigSignal_TD_t *signal,
                                     uint32_t samplingRate);

/**
 * @brief Compose a signal from its frquency components via Inverse DFT
 *
 * @param[out] signal discrete signal
 * @param[in] decomposition contains the signal and the signal components before performing IDFT
 * 
 * @return ENOMEM if memory error,
 *         0 else
 *
*/
int DSPPG__Fourier__realDFT__synthesize(DSPPG_DigSignal_TD_t *signal,
                                        DSPPG_DigSignal_FD_t *decomposition);

/**
 * 
 * 
*/
int DSPPG__Fourier__realDFT__destroy(DSPPG_DigSignal_FD_t *decomposition);

/**
 * @brief Print Real and Imaginary part
 * 
*/
int DSPPG__Fourier__realDFT__printRect(DSPPG_DigSignal_FD_t *decomposition);

/**
 * @brief Print Magnitude and Phase (in Radian)
 * 
*/
int DSPPG__Fourier__realDFT__printPolar(DSPPG_DigSignal_FD_t *decomposition);

/**
 * @brief Store data to JSON file
 * 
 * @param[in] decomposition pointer to data structure
 * @param[in] path, Data is stored here: "{path}/decomposition_data.json"
 * 
 * @details The data can be fed into tools/DSPPG_Plot.py as input file 
 * 
*/
void DSPPG__Fourier__realDFT__toJSON(DSPPG_DigSignal_FD_t *decomposition,
                                     const char * const path);




/* FFT */

#endif /* __STDC_IEC_559_COMPLEX__ || __STDC_IEC_60559_COMPLEX__ */

#endif /* A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B */
