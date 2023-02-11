
#include "globals.h"
#include "unity.h"

#include "Test_Signals.h"

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



int main(void) 
{
    UNITY_BEGIN();
    
    /* Signals */
    RUN_TEST(test__DSPPG__Signals__Signal_Int32__Init_prealloc);


    return UNITY_END();
}