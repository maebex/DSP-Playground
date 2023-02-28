set(SOURCES Signals.c
            Statistics.c
            Fourier.c
            Helpers.c
)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${SOURCES})
