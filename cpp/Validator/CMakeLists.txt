# Preprocessor Definition to let Cpp code retrieve the path of this file
add_definitions(-DVALIDATOR_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data")

###################################
# ADD Validation Library ##########
###################################
add_library(Validator
        Validator.h
        Validator.cpp
)
target_include_directories(Validator PUBLIC ${GlobalIncludes})
target_link_libraries(Validator ${GlobalLink})

# Désactiver le warning de compilation pour l'utilisation de la fonction localtime de la STD
target_compile_definitions(Validator PRIVATE _CRT_SECURE_NO_WARNINGS)

###################################
# ADD Validation Test #############
###################################
add_executable(Validator_Test
        ValidatorTest.cpp
)
target_include_directories(Validator_Test PUBLIC ${GlobalIncludes})
target_link_libraries(Validator_Test
        Validator
        GTest::gtest_main
        ${GlobalLink}
)

###################################
# ADD Validation Perf Test ########
###################################
add_executable(Performance_Validator_Test
        PerformanceValidatorTest.cpp
)
target_include_directories(Performance_Validator_Test PUBLIC ${GlobalIncludes})
target_link_libraries(Performance_Validator_Test    
        Validator
        GTest::gtest_main
        benchmark::benchmark
        ${GlobalLink}
)

target_compile_options(Performance_Validator_Test PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-march=native -mtune=native -ffast-math -mavx2>
    $<$<CXX_COMPILER_ID:MSVC>:/fp:fast /arch:AVX2> # add  /Qvec-report:2 for report vectorization
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(Validator_Test)
gtest_discover_tests(Performance_Validator_Test)
