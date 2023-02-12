#include "globals.h"
#include "unity.h"
#include "Signals.h"

void setUp(void) 
{
    // set stuff up here
    ;

}

void tearDown(void) 
{
    // clean stuff up here
    ;
}

void test__DSPPG__Signals__DigSignal__Init_prealloc(void)
{
    int err;
    DSPPG_DigSignal_t *stump = NULL;

    // EFAULT
    err = DSPPG__Signals__DigSignal__Init_prealloc(&stump, 0, NULL);
    TEST_ASSERT_EQUAL_INT(EFAULT, err);


}



int main(void) 
{
    UNITY_BEGIN();
    
    /* Signals */
    RUN_TEST(test__DSPPG__Signals__DigSignal__Init_prealloc);


    return UNITY_END();
}