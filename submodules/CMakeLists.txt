
add_compile_definitions(UNITY_INCLUDE_CONFIG_H)  # use unity_config.h for configuration
add_library(unity STATIC Unity/src/unity.c)
target_include_directories(unity PUBLIC Unity/src
                                 PUBLIC ./../include
                          )

add_library(log_c STATIC log.c/src/log.c)
target_include_directories(log_c PUBLIC log.c/src)
