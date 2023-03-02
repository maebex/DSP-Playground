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
    double complex *cvalue;
    float *magnitude;
    float *phase;
    uint32_t samplingRate;
}DSPPG_DigSignal_FD_t;


/* Real DFT */

/**
 * @brief Calculate magnitude and phase angle of a frequency domain spectrum
 * 
 * @param[in, out] spectrum pointer to structure
 * 
 * @return 
 * 
 * 
*/
int DSPPG__Fourier__realDFT__calcMagPha(DSPPG_DigSignal_FD_t *spectrum);



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

int DSPPG__Fourier__realDFT__setData(DSPPG_DigSignal_FD_t *spectrum,
                                     size_t len,
                                     double *real,
                                     double *imaginary);

/**
 * @brief Decompose a signal into its frequency components via DFT
 * 
 * @param[out] spectrum contains the signal and the signal components after performing DFT
 * @param[in] signal discrete signal
 * @param[in] samplingRate rate of which the samples were obtained in Hz, may be 0 if not specified 
 * 
 * @return ENOMEM if memory error,
 *         0 else
 * 
 * 
*/
int DSPPG__Fourier__realDFT__analyze(DSPPG_DigSignal_FD_t *spectrum, 
                                     DSPPG_DigSignal_TD_t *signal,
                                     uint32_t samplingRate);

/**
 * @brief Compose a signal from its frquency components via Inverse DFT
 *
 * @param[out] signal discrete signal
 * @param[in] spectrum contains the signal and the signal components before performing IDFT
 * 
 * @return ENOMEM if memory error,
 *         0 else
 *
*/
int DSPPG__Fourier__realDFT__synthesize(DSPPG_DigSignal_TD_t *signal,
                                        DSPPG_DigSignal_FD_t *spectrum);

/**
 * 
 * 
*/
int DSPPG__Fourier__realDFT__destroy(DSPPG_DigSignal_FD_t *spectrum);

/**
 * @brief Print Real and Imaginary part
 * 
*/
int DSPPG__Fourier__realDFT__printRect(DSPPG_DigSignal_FD_t *spectrum);

/**
 * @brief Print Magnitude and Phase (in Radian)
 * 
*/
int DSPPG__Fourier__realDFT__printPolar(DSPPG_DigSignal_FD_t *spectrum);

/**
 * @brief Store data to JSON file
 * 
 * @param[in] spectrum pointer to data structure
 * @param[in] path, Data is stored here: "{path}/spectrum_data.json"
 * 
 * @details The data can be fed into tools/DSPPG_Plot.py as input file 
 * 
*/
void DSPPG__Fourier__realDFT__toJSON(DSPPG_DigSignal_FD_t *spectrum,
                                     const char * const path);




/* FFT */

#endif /* __STDC_IEC_559_COMPLEX__ || __STDC_IEC_60559_COMPLEX__ */

#endif /* A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B */
