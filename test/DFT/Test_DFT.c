

#include "Globals.h"
#include "unity.h"
#include "DFT.h"



DSPPG_DigSignal_TD_t sigStump_1;
DSPPG_DigSignal_TD_t sigStump_2;
DSPPG_DigSignal_TD_t sigStump_3;

/* TEST 1 - sin(1Hz) */
#define TEST_1_ARRAY_LENGTH 8
#define TEST_1_SAMPLE_RATE 8 // Hz
float TEST_1_ARRAY[TEST_1_ARRAY_LENGTH] = {0.0, 0.7071, 1.0, 0.7071, 0, -0.7071, -1.0, -0.7071 };


/* TEST 2 - sin(1Hz)+0.5*sin/(2Hz+(3*Pi/4)) */
#define TEST_2_ARRAY_LENGTH 8
#define TEST_2_SAMPLE_RATE 8 // Hz
float TEST_2_ARRAY[TEST_2_ARRAY_LENGTH] = {0.3535, 0.3535, 0.6464, 1.0607, 0.3535, -1.0607, -1.3535, -0.3535};


/* TEST 3 - 3+sin(1Hz) */
#define TEST_3_ARRAY_LENGTH 8
#define TEST_3_SAMPLE_RATE 8 // Hz
float TEST_3_ARRAY[TEST_3_ARRAY_LENGTH] = {3.0, 3.7071, 4.0, 3.7071, 3.0, 2.2929, 2.0, 2.2929 };


/* TEST 4 - Leakage */



void setUp(void) 
{
    int err;
    
    err = DSPPG__Signals__DigSignal__setData(&sigStump_1, TEST_1_ARRAY_LENGTH, TEST_1_ARRAY);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__DigSignal__setData(&sigStump_2, TEST_2_ARRAY_LENGTH, TEST_2_ARRAY);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = DSPPG__Signals__DigSignal__setData(&sigStump_3, TEST_3_ARRAY_LENGTH, TEST_3_ARRAY);
    TEST_ASSERT_EQUAL_INT(0, err);


}

void tearDown(void) 
{
    // clean stuff up here
    ;
}

void DSPPG__Transformations__realDFT_Decomposition__decompose__1(void)
{
    int err;
    DSPPG_DigSignal_FD_t decomp;
    err = DSPPG__Transformations__realDFT_Decomposition__decompose(&decomp, &sigStump_1, TEST_1_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    // DSPPG__Transformations__realDFT_Decomposition__printRect(&decomp);
    err = DSPPG__Transformations__realDFT_Decomposition__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
    
}

void DSPPG__Transformations__realDFT_Decomposition__decompose__2(void)
{
    int err;
    DSPPG_DigSignal_FD_t decomp;
    err = DSPPG__Transformations__realDFT_Decomposition__decompose(&decomp, &sigStump_2, TEST_2_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    // DSPPG__Transformations__realDFT_Decomposition__printRect(&decomp);
    DSPPG__Transformations__realDFT_Decomposition__toJSON(&decomp, "/mnt/c/Users/mbern/Desktop/gplot/");
    err = DSPPG__Transformations__realDFT_Decomposition__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
}

void DSPPG__Transformations__realDFT_Decomposition__decompose__3(void)
{
    int err;
    DSPPG_DigSignal_FD_t decomp;
    err = DSPPG__Transformations__realDFT_Decomposition__decompose(&decomp, &sigStump_3, TEST_2_SAMPLE_RATE);
    TEST_ASSERT_EQUAL_INT(0, err);
    // DSPPG__Transformations__realDFT_Decomposition__printRect(&decomp);
    err = DSPPG__Transformations__realDFT_Decomposition__destroy(&decomp);
    TEST_ASSERT_EQUAL_INT(0, err);
}


int main(void) 
{
    UNITY_BEGIN();
    
    /* Signals */
    RUN_TEST(DSPPG__Transformations__realDFT_Decomposition__decompose__1);
    RUN_TEST(DSPPG__Transformations__realDFT_Decomposition__decompose__2);
    // RUN_TEST(DSPPG__Transformations__realDFT_Decomposition__decompose__3);

    return UNITY_END();
}


