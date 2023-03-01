#ifndef A223A8BD_7F08_431C_883A_7356FF93A292
#define A223A8BD_7F08_431C_883A_7356FF93A292

#include "Globals.h"

#define DSPPG_DFT_DOUBLE_DELTA ((double)0.0001)


/* Flag to ensure that rands() is only called once */
extern unsigned int DSPPG__SRAND_INITIALIZED;

/**
 * @brief Generate a random float between 0.0 and max
 * 
 * @param[in] max uppe rlimit
 * 
 * @return random number
 * 
*/
float DSPPG__Helpers__genRand(float max);



/**
 * @brief Round Complex number in place
 *
 * @param[in, out] z pointer to complex number
 * @param[in] delta threshold
 *
 * @return 
 *
*/
int croundf(double complex *z, double delta);







#endif /* A223A8BD_7F08_431C_883A_7356FF93A292 */
