set(SOURCES Signals.c
            Statistics.c
            DFT.c
            Helpers.c
)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${SOURCES})
