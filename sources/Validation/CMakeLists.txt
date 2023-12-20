include_directories(
  PUBLIC include
  PUBLIC ${CMAKE_SOURCE_DIR}/sources/3rdParties/spdlog/include
  PUBLIC ${CMAKE_SOURCE_DIR}/sources/3rdParties/eigen
  PUBLIC ${CMAKE_SOURCE_DIR}/sources/3rdParties/gtest/googletest/include
)

add_library(Validation
  include/Validation/Validator.h
  sources/Validation/Validator.cpp
)

# Désactiver le warning de compilation pour l'utilisation de la fonction localtime de la STD
target_compile_definitions(Validation PRIVATE _CRT_SECURE_NO_WARNINGS)

enable_testing()
add_executable(Validation_Test
  tests/ValidatorTest.cpp
)
target_link_libraries(Validation_Test
  PRIVATE Validation
  PRIVATE GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(Validation_Test)
