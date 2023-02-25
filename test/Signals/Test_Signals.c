#include "Globals.h"
#include "unity.h"
#include "Signals.h"
#include "Statistics.h"

#define TEST_PLOTTING

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


void test__DSPPG__Signals__DigSignal__setData(void)
{
    DSPPG_DigSignal_TD_t signal;
    memset(&signal, 0, sizeof signal);
    int err = DSPPG__Signals__DigSignal__setData(&signal, 0, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);
}


void test__DSPPG__Signals__DigSignal__convolute_Random(void)
{
    int err;

    // Input
    DSPPG_DigSignal_TD_t in;
    const unsigned int IN_SIZE = 5;
    DSPPG_DigSignal_payloadType_t data_in[IN_SIZE];
    data_in[0] = 13;
    data_in[1] = -423;
    data_in[2] = 2;
    data_in[3] = -76;
    data_in[4] = 6;
    err = DSPPG__Signals__DigSignal__setData(&in, IN_SIZE, data_in);
    TEST_ASSERT_EQUAL_INT(0, err);

    // Filter IR
    DSPPG_DigSignal_TD_t filter;
    const unsigned int FILTER_SIZE = 3;
    DSPPG_DigSignal_payloadType_t data_filter[FILTER_SIZE];
    data_filter[0] = 17;
    data_filter[1] = 69;
    data_filter[2] = 42;
    err = DSPPG__Signals__DigSignal__setData(&filter, FILTER_SIZE, data_filter);
    TEST_ASSERT_EQUAL_INT(0, err);

    // Result
    DSPPG_DigSignal_TD_t result;
    const unsigned int RESULT_SIZE = IN_SIZE + FILTER_SIZE - 1;
    DSPPG_DigSignal_payloadType_t data_result[RESULT_SIZE];
    data_result[0] = 221;
    data_result[1] = -6294;
    data_result[2] = -28607;
    data_result[3] = -18920;
    data_result[4] = -5058;
    data_result[5] = -2778;
    data_result[6] = 252;
    err = DSPPG__Signals__DigSignal__setData(&result, RESULT_SIZE, data_result);
    TEST_ASSERT_EQUAL_INT(0, err);

    // Convolution - Inside algorithm
    DSPPG_DigSignal_TD_t out;
    memset(&out, 0, sizeof out);
    err = DSPPG__Signals__DigSignal__convoluteIn(&out, &in, &filter);
    TEST_ASSERT_EQUAL_INT(0, err);
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(result.data, out.data, RESULT_SIZE);
    DSPPG__Signals__DigSignal__destroy(&out);

    // Convolution - Outside algorithm
    memset(&out, 0, sizeof out);
    err = DSPPG__Signals__DigSignal__convoluteOut(&out, &in, &filter);
    TEST_ASSERT_EQUAL_INT(0, err);
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(result.data, out.data, RESULT_SIZE);
    DSPPG__Signals__DigSignal__destroy(&out);

}


void test__DSPPG__Signals__DigSignal__convoluteIn_Zero(void)
{
    int err;

    // TODO

}


void test__DSPPG__Signals__DigSignal__generateNoise(void)
{
    int err;
    double_t mean;
    double_t std;
    size_t numSamps;
    DSPPG_StatCont_t cont;
    DSPPG_DigSignal_TD_t noise;

    /* Test 1 */
    mean = 350.5;
    std = 1.5;
    numSamps = 100000;
    err = DSPPG__Signals__DigSignal__generateNoise(&noise, mean, std, numSamps);
    TEST_ASSERT_EQUAL_INT(0, err);
    err = DSPPG__Statistics__StatCont__setSignal(&cont, &noise);
    TEST_ASSERT_EQUAL_INT(0, err);
    err = DSPPG__Statistics__StatCont__calcMean(&cont);
    TEST_ASSERT_EQUAL_INT(0, err);
    err = DSPPG__Statistics__StatCont__calcStd(&cont);
    TEST_ASSERT_EQUAL_INT(0, err);
    TEST_ASSERT_DOUBLE_WITHIN(0.1, mean, cont.mean);
    TEST_ASSERT_DOUBLE_WITHIN(0.1, std, cont.std.std);
    #ifdef TEST_PLOTTING
    char *path1 = "/mnt/c/Users/mbern/Desktop/gplot/testnoise.png";
    char *path2 = "/mnt/c/Users/mbern/Desktop/gplot/testhist.png";
    char *path3 = "/mnt/c/Users/mbern/Desktop/gplot/testdata.dat";
    DSPPG__Signals__DigSignal__plotData(cont.signal, path1);
    DSPPG__Signals__DigSignal__plotHist(cont.signal, path2, path3);
    #endif /* TEST_PLOTTING */
    DSPPG__Signals__DigSignal__destroy(cont.signal);




}




int main(void) 
{
    UNITY_BEGIN();
    
    /* Signals */
    RUN_TEST(test__DSPPG__Signals__DigSignal__setData);
    RUN_TEST(test__DSPPG__Signals__DigSignal__convolute_Random);  // some random values
    // RUN_TEST(test__DSPPG__Signals__DigSignal__convoluteIn_Zero);  // zero input
    RUN_TEST(test__DSPPG__Signals__DigSignal__generateNoise);

    return UNITY_END();
}