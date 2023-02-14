

#include "globals.h"
#include "unity.h"
#include "Statistics.h"


#define TEST_ARRAY_LENGTH 5

DSPPG_DigSignal_t sigStump_fourVals;
DSPPG_DigSignal_t sigStump_fiveVals;
DSPPG_StatCont_t contStump_fourVals;
DSPPG_StatCont_t contStump_fiveVals;
int32_t TEST_ARR[TEST_ARRAY_LENGTH] = {432519, 35893, -305, 234535, -359048};
#define MEAN__FIRST_FOUR_NUMS ((double)175660.5)
#define MEAN__FIRST_FIVE_NUMS ((double)68718.8)


void setUp(void) 
{
    // Generate sigStump
    sigStump_fourVals.len = 4;
    sigStump_fourVals.data = TEST_ARR;
    contStump_fourVals.signal = &sigStump_fourVals;
    contStump_fourVals.mean = MEAN__FIRST_FOUR_NUMS;

    sigStump_fiveVals.len = 5;
    sigStump_fiveVals.data = TEST_ARR;
    contStump_fiveVals.signal = &sigStump_fiveVals;
    contStump_fiveVals.mean = MEAN__FIRST_FIVE_NUMS;

}

void tearDown(void) 
{
    // clean stuff up here
    ;
}

void test__DSPPG__Statistics__StatCont__calcMean(void)
{
    int err;
    err = DSPPG__Signals__DigSignal__Init_prealloc(&sigStump, TEST_ARRAY_LENGTH, TEST_ARR);
    if(err){
        TEST_FAIL();
    }

    DSPPG_StatCont_t *contStump = NULL;
    err = DSPPG__Statistics__StatCont__Init(&contStump, sigStump);

    err = DSPPG__Statistics__StatCont__calcMean(contStump);
    TEST_ASSERT_EQUAL_DOUBLE(MEAN__FIRST_FIVE_NUMS, contStump->mean);

    err = DSPPG__Signals__DigSignal__destroy(&sigStump);
    err = DSPPG__Statistics__StatCont__destroy(&contStump);

}

void test__DSPPG__Statistics__StatCont__updateMean(void)
{
    int err;
    err = DSPPG__Signals__DigSignal__Init_prealloc(&sigStump, TEST_ARRAY_LENGTH-1, TEST_ARR);
    if(err){
        TEST_FAIL();
    }

    err = DSPPG__Statistics__StatCont__Init(&contStump, sigStump);

    err = DSPPG__Statistics__StatCont__calcMean(contStump);
    TEST_ASSERT_EQUAL_DOUBLE(MEAN__FIRST_FOUR_NUMS, contStump->mean);
    err = DSPPG__Statistics__StatCont__updateMean(contStump, 1);
    TEST_ASSERT_EQUAL_DOUBLE(MEAN__FIRST_FIVE_NUMS, contStump->mean);

    err = DSPPG__Signals__DigSignal__destroy(&sigStump);
    err = DSPPG__Statistics__StatCont__destroy(&contStump);

}



int main(void) 
{
    UNITY_BEGIN();
    
    /* Signals */
   RUN_TEST(test__DSPPG__Statistics__StatCont__calcMean);
   RUN_TEST(test__DSPPG__Statistics__StatCont__updateMean);


    return UNITY_END();
}


