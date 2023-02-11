
add_library(unity STATIC Unity/src/unity.c)
target_include_directories(unity PUBLIC Unity/src)

add_library(log_c STATIC log.c/src/log.c)
target_include_directories(log_c PUBLIC log.c/src)
