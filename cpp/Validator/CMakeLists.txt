# Preprocessor Definition to let Cpp code retrieve the path of this file
add_definitions(-DVALIDATOR_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data")

add_library(Validation
        Validator.h
        Validator.cpp
)
target_include_directories(Validation PUBLIC ${GlobalIncludes})
target_link_libraries(Validation ${GlobalLink})

# Désactiver le warning de compilation pour l'utilisation de la fonction localtime de la STD
target_compile_definitions(Validation PRIVATE _CRT_SECURE_NO_WARNINGS)

enable_testing()
add_executable(Validation_Test
        ValidatorTest.cpp
)

target_include_directories(Validation_Test PUBLIC ${GlobalIncludes})

target_link_libraries(Validation_Test
        Validation
        GTest::gtest_main
        ${GlobalLink}
)
include(GoogleTest)
gtest_discover_tests(Validation_Test)
