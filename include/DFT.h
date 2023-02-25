#ifndef A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B
#define A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B

#include "Globals.h"
#include "Signals.h"



/* DFT */


/**
 * @brief Frequency domain signal
 * 
 * 
*/
typedef struct {
    DSPPG_DigSignal_TD_t *signal;
    size_t numComponents;
    float *real;
    float *imaginary;
    float *magnitude;
    float *phase;
    uint32_t samplingRate;
}DSPPG_DigSignal_FD_t;



/**
 * @brief
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
int DSPPG__Transformations__realDFT_Decomposition_decompose(DSPPG_DigSignal_FD_t *decomposition, 
                                                            DSPPG_DigSignal_TD_t *signal,
                                                            uint32_t samplingRate);


/**
 * 
 * 
*/
int DSPPG__Transformations__realDFT_Decomposition_destroy(DSPPG_DigSignal_FD_t *decomposition);

/**
 * @brief Print Real and Imaginary part
 * 
*/
int DSPPG__Transformations__realDFT_Decomposition_printRect(DSPPG_DigSignal_FD_t *decomposition);

/**
 * @brief Print Magnitude and Phase (in Radian)
 * 
*/
int DSPPG__Transformations__realDFT_Decomposition_printPolar(DSPPG_DigSignal_FD_t *decomposition);


#ifdef GNUPLOT_IS_INSTALLED


/**
 * 
 * 
*/
void DSPPG__Transformations__realDFT_Decomposition_plotSpectrum(DSPPG_DigSignal_FD_t *decomposition,
                                                                const char * const pngpath);





#endif /* GNUPLOT_IS_INSTALLED */


#endif /* A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B */
