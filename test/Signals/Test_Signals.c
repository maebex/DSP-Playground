#include "Globals.h"
#include "unity.h"
#include "Signals.h"
#include "Statistics.h"

// #define TEST_PLOTTING

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


void test__DSPPG__Signals__Signal__setData(void)
{
    DSPPG_Signal_t signal;
    memset(&signal, 0, sizeof signal);
    int err = DSPPG__Signals__Signal__setData(&signal, 0, NULL, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);
}


void test__DSPPG__Signals__Signal__convolute_Random(void)
{
    int err;

    // Input
    DSPPG_Signal_t in;
    const unsigned int IN_SIZE = 5;
    DSPPG_Signal_payloadType_t data_in[IN_SIZE];
    data_in[0] = 13;
    data_in[1] = -423;
    data_in[2] = 2;
    data_in[3] = -76;
    data_in[4] = 6;
    err = DSPPG__Signals__Signal__setData(&in, IN_SIZE, data_in, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    // Filter IR
    DSPPG_Signal_t filter;
    const unsigned int FILTER_SIZE = 3;
    DSPPG_Signal_payloadType_t data_filter[FILTER_SIZE];
    data_filter[0] = 17;
    data_filter[1] = 69;
    data_filter[2] = 42;
    err = DSPPG__Signals__Signal__setData(&filter, FILTER_SIZE, data_filter, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    // Result
    DSPPG_Signal_t result;
    const unsigned int RESULT_SIZE = IN_SIZE + FILTER_SIZE - 1;
    DSPPG_Signal_payloadType_t data_result[RESULT_SIZE];
    data_result[0] = 221;
    data_result[1] = -6294;
    data_result[2] = -28607;
    data_result[3] = -18920;
    data_result[4] = -5058;
    data_result[5] = -2778;
    data_result[6] = 252;
    err = DSPPG__Signals__Signal__setData(&result, RESULT_SIZE, data_result, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    // Convolution - Inside algorithm
    DSPPG_Signal_t out;
    memset(&out, 0, sizeof out);
    err = DSPPG__Signals__Signal__convoluteIn(&out, &in, &filter);
    TEST_ASSERT_EQUAL_INT(0, err);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(result.data, out.data, RESULT_SIZE);
    DSPPG__Signals__Signal__destroy(&out);

    // Convolution - Outside algorithm
    memset(&out, 0, sizeof out);
    err = DSPPG__Signals__Signal__convoluteOut(&out, &in, &filter);
    TEST_ASSERT_EQUAL_INT(0, err);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(result.data, out.data, RESULT_SIZE);
    DSPPG__Signals__Signal__destroy(&out);

}


void test__DSPPG__Signals__Signal__convoluteIn_Zero(void)
{
    int err;

    // TODO

}


void test__DSPPG__Signals__Signal__generateNoise(void)
{
    int err;
    float mean;
    float std;
    size_t numSamps;
    DSPPG_StatCont_t cont;
    DSPPG_Signal_t noise;

    /* Test 1 */
    mean = 0;
    std = 15;
    numSamps = 100000;
    err = DSPPG__Signals__Signal__generateNoise(&noise, mean, std, numSamps, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);
    err = DSPPG__Statistics__StatCont__setSignal(&cont, &noise);
    TEST_ASSERT_EQUAL_INT(0, err);
    err = DSPPG__Statistics__StatCont__calcMean(&cont);
    TEST_ASSERT_EQUAL_INT(0, err);
    err = DSPPG__Statistics__StatCont__calcStd(&cont);
    TEST_ASSERT_EQUAL_INT(0, err);
    TEST_ASSERT_FLOAT_WITHIN(0.1, mean, cont.mean);
    TEST_ASSERT_FLOAT_WITHIN(0.1, std, cont.std.std);
    #ifdef TEST_PLOTTING
    char *path1 = "/mnt/c/Users/mberndt/Desktop/gplot/";
    DSPPG__Signals__Signal__toJSON(cont.signal, path1);
    #endif /* TEST_PLOTTING */
    DSPPG__Signals__Signal__destroy(cont.signal);

}




int main(void) 
{
    UNITY_BEGIN();
    
    /* Signals */
    RUN_TEST(test__DSPPG__Signals__Signal__setData);
    RUN_TEST(test__DSPPG__Signals__Signal__convolute_Random);  // some random values
    // RUN_TEST(test__DSPPG__Signals__Signal__convoluteIn_Zero);  // zero input
    RUN_TEST(test__DSPPG__Signals__Signal__generateNoise);

    return UNITY_END();
}