enableStrictWarnings()

# Preprocessor Definition to let Cpp code retrieve the project path
add_definitions(-DPROJECT_PATH="${CMAKE_SOURCE_DIR}")

add_library(Validation
  Validator.h
  Validator.cpp
)
target_include_directories(Validation PUBLIC ${GlobalIncludes})


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
)
include(GoogleTest)
gtest_discover_tests(Validation_Test)
