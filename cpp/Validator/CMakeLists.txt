# Preprocessor Definition to let Cpp code retrieve the path of this file
add_definitions(-DVALIDATOR_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data")

###################################
# ADD Validation Library ##########
###################################
add_library(Validation
        Validator.h
        Validator.cpp
)
target_include_directories(Validation PUBLIC ${GlobalIncludes})
target_link_libraries(Validation ${GlobalLink})

# Désactiver le warning de compilation pour l'utilisation de la fonction localtime de la STD
target_compile_definitions(Validation PRIVATE _CRT_SECURE_NO_WARNINGS)

enable_testing()

###################################
# ADD Validation Test #############
###################################
add_executable(Validation_Test
        ValidatorTest.cpp
)
target_include_directories(Validation_Test PUBLIC ${GlobalIncludes})
target_link_libraries(Validation_Test
        Validation
        GTest::gtest_main
        ${GlobalLink}
)

###################################
# ADD Validation Perf Test ########
###################################
add_executable(Validation_Perf_Test
        ValidatorPerfTest.cpp
)
target_include_directories(Validation_Perf_Test PUBLIC ${GlobalIncludes})
target_link_libraries(Validation_Perf_Test
        Validation
        GTest::gtest_main
        benchmark::benchmark
        ${GlobalLink}
)

target_compile_options(Validation_Perf_Test PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-march=native -mtune=native -ffast-math -mavx2>
    $<$<CXX_COMPILER_ID:MSVC>:/fp:fast /arch:AVX2> # add  /Qvec-report:2 for report vectorization
)

include(GoogleTest)
gtest_discover_tests(Validation_Test)
gtest_discover_tests(Validation_Perf_Test)
