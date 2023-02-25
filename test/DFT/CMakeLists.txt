
set(TEST_NAME DSPPSG_DFT_Test)
add_executable (${TEST_NAME}
                Test_DFT.c
                ) 

target_include_directories(${TEST_NAME}
                           PUBLIC "/usr/local/include"
                           PUBLIC ${PROJECT_SOURCE_DIR}/include/ 
                          )

target_link_directories(${TEST_NAME} 
                        PUBLIC "/usr/local/lib"
                        PUBLIC ${PROJECT_SOURCE_DIR}/build/
                       )

target_link_libraries(${TEST_NAME}
                      unity
                      DSPPG
                     )

enable_testing()
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})