#ifndef A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B
#define A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B

#include "Globals.h"
#include "Signals.h"



/* DFT */

struct DSPPG__Transformations__DFT_Component {
    uint32_t amplitude;
    uint32_t frequency;
};


/**
 * @brief Frequency domain signal
*/
typedef struct {
    DSPPG_DigSignal_TD_t *signal;
    size_t numComponents;
    DSPPG__Transformations__DFT_Component *real;
    DSPPG__Transformations__DFT_Component *imaginary;
}DSPPG_DigSignal_FD_t;










#endif /* A36BA74E_3F68_4068_BAD1_9B2B6BAD7C3B */
