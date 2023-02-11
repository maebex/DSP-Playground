#ifndef EE1C1C9A_98D1_4E49_B2C4_8F64C8179A9A
#define EE1C1C9A_98D1_4E49_B2C4_8F64C8179A9A

#include "globals.h"
#include "Signals.h"


void test__DSPPG__Signals__Signal_Int32__Init_prealloc(void)
{
    int err;
    size_t sz = 0;
    DSPPG_Signal_Int32 *stump = NULL;

    // EFAULT
    err = DSPPG__Signals__Signal_Int32__Init_prealloc(stump, sz, NULL);
    TEST_ASSERT_EQUAL_INT(EFAULT, err);
}


#endif /* EE1C1C9A_98D1_4E49_B2C4_8F64C8179A9A */
