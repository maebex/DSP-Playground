

#include "Globals.h"
#include "unity.h"
#include "Statistics.h"


#define TEST_ARRAY_LENGTH 5

DSPPG_Signal_t sigStump_fourVals;
DSPPG_Signal_t sigStump_fiveVals;
DSPPG_StatCont_t contStump_fourVals;
DSPPG_StatCont_t contStump_fiveVals;
float TEST_ARR[TEST_ARRAY_LENGTH] = {432519., 35893., -305., 234535., -359048.};
#define MEAN__FIRST_FOUR_NUMS ((float)175660.5)
#define MEAN__FIRST_FIVE_NUMS ((float)68718.8)
#define STDDEV__FIRST_FOUR_NUMS ((float)199951.0832)
#define STDDEV__FIRST_FIVE_NUMS ((float)295242.2103)


void setUp(void) 
{
    // Generate sigStump
    sigStump_fourVals.len = 4;
    sigStump_fourVals.data = TEST_ARR;
    contStump_fourVals.signal = &sigStump_fourVals;
    contStump_fourVals.mean = MEAN__FIRST_FOUR_NUMS;
    contStump_fourVals.std.std = STDDEV__FIRST_FOUR_NUMS;

    sigStump_fiveVals.len = 5;
    sigStump_fiveVals.data = TEST_ARR;
    contStump_fiveVals.signal = &sigStump_fiveVals;
    contStump_fiveVals.mean = MEAN__FIRST_FIVE_NUMS;
    contStump_fiveVals.std.std = STDDEV__FIRST_FIVE_NUMS;

}

void tearDown(void) 
{
    // clean stuff up here
    ;
}

void test__DSPPG__Statistics__StatCont__calcMean(void)
{
    int err;

    DSPPG_StatCont_t contStump;
    memset(&contStump, 0, sizeof contStump);
    err = DSPPG__Statistics__StatCont__setSignal(&contStump, &sigStump_fiveVals);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Statistics__StatCont__calcMean(&contStump);
    TEST_ASSERT_EQUAL_INT(0, err);
    TEST_ASSERT_EQUAL_FLOAT(MEAN__FIRST_FIVE_NUMS, contStump.mean);

}

void test__DSPPG__Statistics__StatCont__updateMean(void)
{
    int err;

    DSPPG_StatCont_t contStump;
    memset(&contStump, 0, sizeof contStump);
    err = DSPPG__Statistics__StatCont__setSignal(&contStump, &sigStump_fourVals);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Statistics__StatCont__calcMean(&contStump);
    TEST_ASSERT_EQUAL_INT(0, err);

    TEST_ASSERT_EQUAL_FLOAT(MEAN__FIRST_FOUR_NUMS, contStump.mean);
    err = DSPPG__Statistics__StatCont__updateMean(&contStump, 1);
    TEST_ASSERT_EQUAL_INT(0, err);
    TEST_ASSERT_EQUAL_FLOAT(MEAN__FIRST_FIVE_NUMS, contStump.mean);

}

void test__DSPPG__Statistics__StatCont__calcStd(void)
{
    int err;

    DSPPG_StatCont_t contStump;
    memset(&contStump, 0, sizeof contStump);
    err = DSPPG__Statistics__StatCont__setSignal(&contStump, &sigStump_fourVals);

    err = DSPPG__Statistics__StatCont__calcStd(&contStump);
    TEST_ASSERT_EQUAL_INT(0, err);
    TEST_ASSERT_EQUAL_FLOAT(STDDEV__FIRST_FOUR_NUMS, contStump.std.std);


}

void test__DSPPG__Statistics__StatCont__updateStd(void)
{
    int err;

    DSPPG_StatCont_t contStump;
    memset(&contStump, 0, sizeof contStump);
    err = DSPPG__Statistics__StatCont__setSignal(&contStump, &sigStump_fourVals);

    err = DSPPG__Statistics__StatCont__calcStd(&contStump);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Statistics__StatCont__setSignal(&contStump, &sigStump_fiveVals);
    err = DSPPG__Statistics__StatCont__updateStd(&contStump, 1);
    TEST_ASSERT_EQUAL_INT(0, err);
    TEST_ASSERT_EQUAL_FLOAT(STDDEV__FIRST_FIVE_NUMS, contStump.std.std);

}



int main(void) 
{
    UNITY_BEGIN();
    
    /* Signals */
    RUN_TEST(test__DSPPG__Statistics__StatCont__calcMean);
    RUN_TEST(test__DSPPG__Statistics__StatCont__updateMean);
    RUN_TEST(test__DSPPG__Statistics__StatCont__calcStd);
    RUN_TEST(test__DSPPG__Statistics__StatCont__updateStd);


    return UNITY_END();
}


