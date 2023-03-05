#ifndef A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B
#define A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B

#include "Globals.h"
#include "Signals.h"


#if defined __STDC_IEC_559_COMPLEX__ || __STDC_IEC_60559_COMPLEX__


/* DFT */



/* Real DFT */


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
int DSPPG__Fourier__realDFT__analyze(DSPPG_Spectrum_t *spectrum, 
                                     DSPPG_Signal_t *signal,
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
int DSPPG__Fourier__realDFT__synthesize(DSPPG_Signal_t *signal,
                                        DSPPG_Spectrum_t *spectrum);

/**
 * 
 * 
*/
int DSPPG__Fourier__realDFT__destroy(DSPPG_Spectrum_t *spectrum);

/**
 * @brief Print Real and Imaginary part
 * 
*/
int DSPPG__Fourier__realDFT__printRect(DSPPG_Spectrum_t *spectrum);

/**
 * @brief Print Magnitude and Phase (in Radian)
 * 
*/
int DSPPG__Fourier__realDFT__printPolar(DSPPG_Spectrum_t *spectrum);





/* FFT */





#endif /* __STDC_IEC_559_COMPLEX__ || __STDC_IEC_60559_COMPLEX__ */

#endif /* A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B */
