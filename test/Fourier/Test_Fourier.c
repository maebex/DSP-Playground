

#include "Globals.h"
#include "unity.h"
#include "Fourier.h"


// Set this to adjust the directory where test results are stored
#define TEST_DATA_FILE_STORAGE_PATH "/mnt/c/Users/mbern/Desktop/gplot/"

// Set this to adjust the test results that are stored
#define STORE_RESULTS_TEST_1


/* TEST 1 - sin(2*Pi*1Hz) */
DSPPG_Signal_t sigStump_1;
#define TEST_1_ARRAY_LENGTH 8
#define TEST_1_SAMPLE_RATE 8 // Hz
#define TEST_1_OFFSET 0.0
#define TEST_1_FREQUENCY 1.0
float TEST_1_ARRAY[TEST_1_ARRAY_LENGTH] = {
    TEST_1_OFFSET+sin(2.*M_PI*TEST_1_FREQUENCY*0./TEST_1_ARRAY_LENGTH),
    TEST_1_OFFSET+sin(2.*M_PI*TEST_1_FREQUENCY*1./TEST_1_ARRAY_LENGTH),
    TEST_1_OFFSET+sin(2.*M_PI*TEST_1_FREQUENCY*2./TEST_1_ARRAY_LENGTH),
    TEST_1_OFFSET+sin(2.*M_PI*TEST_1_FREQUENCY*3./TEST_1_ARRAY_LENGTH),
    TEST_1_OFFSET+sin(2.*M_PI*TEST_1_FREQUENCY*4./TEST_1_ARRAY_LENGTH),
    TEST_1_OFFSET+sin(2.*M_PI*TEST_1_FREQUENCY*5./TEST_1_ARRAY_LENGTH),
    TEST_1_OFFSET+sin(2.*M_PI*TEST_1_FREQUENCY*6./TEST_1_ARRAY_LENGTH),
    TEST_1_OFFSET+sin(2.*M_PI*TEST_1_FREQUENCY*7./TEST_1_ARRAY_LENGTH),
};


/* TEST 2 - sin(2*PI*1Hz)+0.5*sin/(2*PI*2Hz+(3*Pi/4)) */
DSPPG_Signal_t sigStump_2;
#define TEST_2_ARRAY_LENGTH 8
#define TEST_2_SAMPLE_RATE 8 // Hz
#define TEST_2_OFFSET 0.0
#define TEST_2_FREQUENCY_1 1.0
#define TEST_2_FREQUENCY_2 2.0
#define TEST_2_PHASE_OFFSET (3.*M_PI/4.)
#define TEST_2_SCALING_FACTOR 0.5
float TEST_2_ARRAY[TEST_2_ARRAY_LENGTH] = {
    TEST_2_OFFSET+sin(2.*M_PI*TEST_2_FREQUENCY_1*0./TEST_2_ARRAY_LENGTH) + TEST_2_SCALING_FACTOR*sin(2.*M_PI*TEST_2_FREQUENCY_2*0./TEST_2_ARRAY_LENGTH + TEST_2_PHASE_OFFSET),
    TEST_2_OFFSET+sin(2.*M_PI*TEST_2_FREQUENCY_1*1./TEST_2_ARRAY_LENGTH) + TEST_2_SCALING_FACTOR*sin(2.*M_PI*TEST_2_FREQUENCY_2*1./TEST_2_ARRAY_LENGTH + TEST_2_PHASE_OFFSET),
    TEST_2_OFFSET+sin(2.*M_PI*TEST_2_FREQUENCY_1*2./TEST_2_ARRAY_LENGTH) + TEST_2_SCALING_FACTOR*sin(2.*M_PI*TEST_2_FREQUENCY_2*2./TEST_2_ARRAY_LENGTH + TEST_2_PHASE_OFFSET),
    TEST_2_OFFSET+sin(2.*M_PI*TEST_2_FREQUENCY_1*3./TEST_2_ARRAY_LENGTH) + TEST_2_SCALING_FACTOR*sin(2.*M_PI*TEST_2_FREQUENCY_2*3./TEST_2_ARRAY_LENGTH + TEST_2_PHASE_OFFSET),
    TEST_2_OFFSET+sin(2.*M_PI*TEST_2_FREQUENCY_1*4./TEST_2_ARRAY_LENGTH) + TEST_2_SCALING_FACTOR*sin(2.*M_PI*TEST_2_FREQUENCY_2*4./TEST_2_ARRAY_LENGTH + TEST_2_PHASE_OFFSET),
    TEST_2_OFFSET+sin(2.*M_PI*TEST_2_FREQUENCY_1*5./TEST_2_ARRAY_LENGTH) + TEST_2_SCALING_FACTOR*sin(2.*M_PI*TEST_2_FREQUENCY_2*5./TEST_2_ARRAY_LENGTH + TEST_2_PHASE_OFFSET),
    TEST_2_OFFSET+sin(2.*M_PI*TEST_2_FREQUENCY_1*6./TEST_2_ARRAY_LENGTH) + TEST_2_SCALING_FACTOR*sin(2.*M_PI*TEST_2_FREQUENCY_2*6./TEST_2_ARRAY_LENGTH + TEST_2_PHASE_OFFSET),
    TEST_2_OFFSET+sin(2.*M_PI*TEST_2_FREQUENCY_1*7./TEST_2_ARRAY_LENGTH) + TEST_2_SCALING_FACTOR*sin(2.*M_PI*TEST_2_FREQUENCY_2*7./TEST_2_ARRAY_LENGTH + TEST_2_PHASE_OFFSET)
};


/* TEST 3 - 3+sin(2*Pi*1Hz) */
DSPPG_Signal_t sigStump_3;
#define TEST_3_ARRAY_LENGTH 8
#define TEST_3_SAMPLE_RATE 8 // Hz
#define TEST_3_OFFSET 3.0
float TEST_3_ARRAY[TEST_3_ARRAY_LENGTH] = {
    TEST_3_OFFSET+sin(2.*M_PI*1.*0./TEST_3_ARRAY_LENGTH),
    TEST_3_OFFSET+sin(2.*M_PI*1.*1./TEST_3_ARRAY_LENGTH),
    TEST_3_OFFSET+sin(2.*M_PI*1.*2./TEST_3_ARRAY_LENGTH),
    TEST_3_OFFSET+sin(2.*M_PI*1.*3./TEST_3_ARRAY_LENGTH),
    TEST_3_OFFSET+sin(2.*M_PI*1.*4./TEST_3_ARRAY_LENGTH),
    TEST_3_OFFSET+sin(2.*M_PI*1.*5./TEST_3_ARRAY_LENGTH),
    TEST_3_OFFSET+sin(2.*M_PI*1.*6./TEST_3_ARRAY_LENGTH),
    TEST_3_OFFSET+sin(2.*M_PI*1.*7./TEST_3_ARRAY_LENGTH)
};


/* TEST 4 - Example 2 shifted by 3 samples  */
DSPPG_Signal_t sigStump_4;
#define TEST_4_ARRAY_LENGTH 8
#define TEST_4_SAMPLE_RATE 8 // Hz
#define TEST_4_OFFSET 0.0
#define TEST_4_FREQUENCY_1 1.0
#define TEST_4_FREQUENCY_2 2.0
#define TEST_4_PHASE_OFFSET (3.*M_PI/4.)
#define TEST_4_SCALING_FACTOR 0.5
float TEST_4_ARRAY[TEST_4_ARRAY_LENGTH] = {
    TEST_4_OFFSET+sin(2.*M_PI*TEST_4_FREQUENCY_1*3./TEST_4_ARRAY_LENGTH) + TEST_4_SCALING_FACTOR*sin(2.*M_PI*TEST_4_FREQUENCY_2*3./TEST_4_ARRAY_LENGTH + TEST_4_PHASE_OFFSET),
    TEST_4_OFFSET+sin(2.*M_PI*TEST_4_FREQUENCY_1*4./TEST_4_ARRAY_LENGTH) + TEST_4_SCALING_FACTOR*sin(2.*M_PI*TEST_4_FREQUENCY_2*4./TEST_4_ARRAY_LENGTH + TEST_4_PHASE_OFFSET),
    TEST_4_OFFSET+sin(2.*M_PI*TEST_4_FREQUENCY_1*5./TEST_4_ARRAY_LENGTH) + TEST_4_SCALING_FACTOR*sin(2.*M_PI*TEST_4_FREQUENCY_2*5./TEST_4_ARRAY_LENGTH + TEST_4_PHASE_OFFSET),
    TEST_4_OFFSET+sin(2.*M_PI*TEST_4_FREQUENCY_1*6./TEST_4_ARRAY_LENGTH) + TEST_4_SCALING_FACTOR*sin(2.*M_PI*TEST_4_FREQUENCY_2*6./TEST_4_ARRAY_LENGTH + TEST_4_PHASE_OFFSET),
    TEST_4_OFFSET+sin(2.*M_PI*TEST_4_FREQUENCY_1*7./TEST_4_ARRAY_LENGTH) + TEST_4_SCALING_FACTOR*sin(2.*M_PI*TEST_4_FREQUENCY_2*7./TEST_4_ARRAY_LENGTH + TEST_4_PHASE_OFFSET),
    TEST_4_OFFSET+sin(2.*M_PI*TEST_4_FREQUENCY_1*0./TEST_4_ARRAY_LENGTH) + TEST_4_SCALING_FACTOR*sin(2.*M_PI*TEST_4_FREQUENCY_2*0./TEST_4_ARRAY_LENGTH + TEST_4_PHASE_OFFSET),
    TEST_4_OFFSET+sin(2.*M_PI*TEST_4_FREQUENCY_1*1./TEST_4_ARRAY_LENGTH) + TEST_4_SCALING_FACTOR*sin(2.*M_PI*TEST_4_FREQUENCY_2*1./TEST_4_ARRAY_LENGTH + TEST_4_PHASE_OFFSET),
    TEST_4_OFFSET+sin(2.*M_PI*TEST_4_FREQUENCY_1*2./TEST_4_ARRAY_LENGTH) + TEST_4_SCALING_FACTOR*sin(2.*M_PI*TEST_4_FREQUENCY_2*2./TEST_4_ARRAY_LENGTH + TEST_4_PHASE_OFFSET)
};


/* TEST 5 - Rectangular window */
DSPPG_Signal_t sigStump_5;
#define TEST_5_ARRAY_LENGTH 64
#define TEST_5_SAMPLE_RATE 8 // Hz
float TEST_5_ARRAY[TEST_5_ARRAY_LENGTH] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                           0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                           0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                           1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
                                           1.0, 
                                           0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                           0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                           0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

/* TEST 6 - IDFT */
DSPPG_Signal_t sigStump_6;
#define TEST_6_ARRAY_LENGTH 28
#define TEST_6_SAMPLE_RATE 8 // Hz
float TEST_6_ARRAY[TEST_6_ARRAY_LENGTH] = {1.0, 
                                           0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                           0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                           0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


/* TEST 7 */
DSPPG_Signal_t sigStump_7;
#define TEST_7_ARRAY_LENGTH 9
#define TEST_7_SAMPLE_RATE 8 // Hz
float TEST_7_ARRAY[TEST_7_ARRAY_LENGTH] = {9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0};


/* TEST 8 */
DSPPG_Signal_t sigStump_8;
#define TEST_8_ARRAY_LENGTH 9
#define TEST_8_SAMPLE_RATE 8 // Hz
float TEST_8_ARRAY[TEST_8_ARRAY_LENGTH] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


/* TEST 9 */
DSPPG_Signal_t sigStump_9;
#define TEST_9_ARRAY_LENGTH 9
#define TEST_9_SAMPLE_RATE 8 // Hz
float TEST_9_ARRAY[TEST_9_ARRAY_LENGTH] = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


/* TEST 10 */
DSPPG_Spectrum_t specStump_10;
#define TEST_10_ARRAY_LENGTH 9
#define TEST_10_SAMPLE_RATE 8 // Hz
double TEST_10_ARRAY_RE[TEST_10_ARRAY_LENGTH] = {0.0, 0.0, 0.0, 5.657, 0.0, 5.657, 0.0, 0.0, 0.0};
double TEST_10_ARRAY_IM[TEST_10_ARRAY_LENGTH] = {0.0, 0.0, 0.0, 5.657, 0.0, -5.657, 0.0, 0.0, 0.0};


void setUp(void) 
{
    int err;
    
    err = DSPPG__Signals__Signal__setData(&sigStump_1, TEST_1_ARRAY_LENGTH, TEST_1_ARRAY, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__Signal__setData(&sigStump_2, TEST_2_ARRAY_LENGTH, TEST_2_ARRAY, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__Signal__setData(&sigStump_3, TEST_3_ARRAY_LENGTH, TEST_3_ARRAY, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__Signal__setData(&sigStump_4, TEST_4_ARRAY_LENGTH, TEST_4_ARRAY, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__Signal__setData(&sigStump_5, TEST_5_ARRAY_LENGTH, TEST_5_ARRAY, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__Signal__setData(&sigStump_6, TEST_6_ARRAY_LENGTH, TEST_6_ARRAY, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__Signal__setData(&sigStump_7, TEST_7_ARRAY_LENGTH, TEST_7_ARRAY, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__Signal__setData(&sigStump_8, TEST_8_ARRAY_LENGTH, TEST_8_ARRAY, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__Signal__setData(&sigStump_9, TEST_9_ARRAY_LENGTH, TEST_9_ARRAY, NULL);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__Spectrum__setData(&specStump_10, TEST_10_ARRAY_LENGTH, TEST_10_ARRAY_RE, TEST_10_ARRAY_IM);
    TEST_ASSERT_EQUAL_INT(0, err);


}

void tearDown(void) 
{
    // clean stuff up here
    ;
}

void DSPPG__Fourier__realDFT__analyze__1(void)
{
    int err;
    DSPPG_Spectrum_t decomp;
    err = DSPPG__Fourier__realDFT__analyze(&decomp, &sigStump_1, TEST_1_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    #ifdef STORE_RESULTS_TEST_1
    DSPPG__Signals__Signal__toJSON(&sigStump_1, TEST_DATA_FILE_STORAGE_PATH);
    DSPPG__Signals__Spectrum__toJSON(&decomp, TEST_DATA_FILE_STORAGE_PATH);
    #endif /* STORE_RESULTS_TEST_1 */
    err = DSPPG__Fourier__realDFT__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
    
}

void DSPPG__Fourier__realDFT__analyze__2(void)
{
    int err;
    DSPPG_Spectrum_t decomp;
    err = DSPPG__Fourier__realDFT__analyze(&decomp, &sigStump_2, TEST_2_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    #ifdef STORE_RESULTS_TEST_2
    DSPPG__Signals__Signal__toJSON(&sigStump_2, TEST_DATA_FILE_STORAGE_PATH);
    DSPPG__Signals__Spectrum__toJSON(&decomp, TEST_DATA_FILE_STORAGE_PATH);
    #endif /* STORE_RESULTS_TEST_2 */
    err = DSPPG__Fourier__realDFT__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
}

void DSPPG__Fourier__realDFT__analyze__3(void)
{
    int err;
    DSPPG_Spectrum_t decomp;
    err = DSPPG__Fourier__realDFT__analyze(&decomp, &sigStump_3, TEST_3_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    #ifdef STORE_RESULTS_TEST_3
    DSPPG__Signals__Signal__toJSON(&sigStump_3, TEST_DATA_FILE_STORAGE_PATH);
    DSPPG__Signals__Spectrum__toJSON(&decomp, TEST_DATA_FILE_STORAGE_PATH);
    #endif /* STORE_RESULTS_TEST_3 */
    err = DSPPG__Fourier__realDFT__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
}

void DSPPG__Fourier__realDFT__analyze__4(void)
{
    int err;
    DSPPG_Spectrum_t decomp;
    err = DSPPG__Fourier__realDFT__analyze(&decomp, &sigStump_4, TEST_4_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    #ifdef STORE_RESULTS_TEST_4
    DSPPG__Signals__Signal__toJSON(&sigStump_4, TEST_DATA_FILE_STORAGE_PATH);
    DSPPG__Signals__Spectrum__toJSON(&decomp, TEST_DATA_FILE_STORAGE_PATH);
    #endif /* STORE_RESULTS_TEST_4 */
    err = DSPPG__Fourier__realDFT__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
}



void DSPPG__Fourier__realDFT__analyze__5(void)
{
    int err;
    DSPPG_Spectrum_t decomp;
    err = DSPPG__Fourier__realDFT__analyze(&decomp, &sigStump_5, TEST_5_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    #ifdef STORE_RESULTS_TEST_5
    DSPPG__Signals__Signal__toJSON(&sigStump_5, TEST_DATA_FILE_STORAGE_PATH);
    DSPPG__Signals__Spectrum__toJSON(&decomp, TEST_DATA_FILE_STORAGE_PATH);
    #endif /* STORE_RESULTS_TEST_5 */
    err = DSPPG__Fourier__realDFT__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
}


void DSPPG__Fourier__realDFT__synthesize__6(void)
{
    int err;
    DSPPG_Spectrum_t decomp;
    err = DSPPG__Fourier__realDFT__analyze(&decomp, &sigStump_6, TEST_6_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    DSPPG_Signal_t syntSig;
    memset(&syntSig, 0, sizeof syntSig);
    err = DSPPG__Fourier__realDFT__synthesize(&syntSig, &decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
    #ifdef STORE_RESULTS_TEST_6
    DSPPG__Signals__Spectrum__toJSON(&decomp, TEST_DATA_FILE_STORAGE_PATH);
    DSPPG__Signals__Signal__toJSON(&syntSig, TEST_DATA_FILE_STORAGE_PATH);
    #endif /* STORE_RESULTS_TEST_6 */
    err = DSPPG__Fourier__realDFT__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
}

void DSPPG__Fourier__realDFT__analyze__7(void)
{
    int err;
    DSPPG_Spectrum_t decomp;
    err = DSPPG__Fourier__realDFT__analyze(&decomp, &sigStump_7, TEST_7_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    #ifdef STORE_RESULTS_TEST_7
    DSPPG__Signals__Signal__toJSON(&sigStump_7, TEST_DATA_FILE_STORAGE_PATH);
    DSPPG__Signals__Spectrum__toJSON(&decomp, TEST_DATA_FILE_STORAGE_PATH);
    #endif /* STORE_RESULTS_TEST_7 */
    err = DSPPG__Fourier__realDFT__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
}

void DSPPG__Fourier__realDFT__analyze__8(void)
{
    int err;
    DSPPG_Spectrum_t decomp;
    err = DSPPG__Fourier__realDFT__analyze(&decomp, &sigStump_8, TEST_8_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    #ifdef STORE_RESULTS_TEST_8
    DSPPG__Signals__Signal__toJSON(&sigStump_8, TEST_DATA_FILE_STORAGE_PATH);
    DSPPG__Signals__Spectrum__toJSON(&decomp, TEST_DATA_FILE_STORAGE_PATH);
    #endif /* STORE_RESULTS_TEST_8 */
    err = DSPPG__Fourier__realDFT__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
}

void DSPPG__Fourier__realDFT__analyze__9(void)
{
    int err;
    DSPPG_Spectrum_t decomp;
    err = DSPPG__Fourier__realDFT__analyze(&decomp, &sigStump_9, TEST_9_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    #ifdef STORE_RESULTS_TEST_9
    DSPPG__Signals__Signal__toJSON(&sigStump_9, TEST_DATA_FILE_STORAGE_PATH);
    DSPPG__Signals__Spectrum__toJSON(&decomp, TEST_DATA_FILE_STORAGE_PATH);
    #endif /* STORE_RESULTS_TEST_9 */
    err = DSPPG__Fourier__realDFT__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
}



void DSPPG__Fourier__realDFT__synthesize__10(void)
{
    int err;

    DSPPG_Signal_t syntSig;
    memset(&syntSig, 0, sizeof syntSig);
    err = DSPPG__Fourier__realDFT__synthesize(&syntSig, &specStump_10);
    TEST_ASSERT_EQUAL_INT(0, err);
    #ifdef STORE_RESULTS_TEST_10
    DSPPG__Signals__Signal__toJSON(&syntSig, TEST_DATA_FILE_STORAGE_PATH);
    DSPPG__Signals__Spectrum__toJSON(&specStump_10, TEST_DATA_FILE_STORAGE_PATH);
    #endif /* STORE_RESULTS_TEST_10 */
    err = DSPPG__Fourier__realDFT__destroy(&specStump_10);
    TEST_ASSERT_EQUAL_INT(0, err);
}



int main(void) 
{
    UNITY_BEGIN();
    
    RUN_TEST(DSPPG__Fourier__realDFT__analyze__1);
    RUN_TEST(DSPPG__Fourier__realDFT__analyze__2);
    RUN_TEST(DSPPG__Fourier__realDFT__analyze__3);
    RUN_TEST(DSPPG__Fourier__realDFT__analyze__4);
    RUN_TEST(DSPPG__Fourier__realDFT__analyze__5);
    RUN_TEST(DSPPG__Fourier__realDFT__synthesize__6);
    RUN_TEST(DSPPG__Fourier__realDFT__analyze__7);
    RUN_TEST(DSPPG__Fourier__realDFT__analyze__8);
    RUN_TEST(DSPPG__Fourier__realDFT__analyze__9);
    RUN_TEST(DSPPG__Fourier__realDFT__synthesize__10);

    return UNITY_END();
}


