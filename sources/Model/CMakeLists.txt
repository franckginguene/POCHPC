include_directories(
  PUBLIC include
  PUBLIC ${CMAKE_SOURCE_DIR}/sources/3rdParties/spdlog-1.x/include
  PUBLIC ${CMAKE_SOURCE_DIR}/sources/3rdParties/eigen-3.4.0/
  PUBLIC ${CMAKE_SOURCE_DIR}/sources/3rdParties/gtest/googletest/include
)

add_library(Model
  include/Model/Factorial.h
  sources/Model/Factorial.cpp
)


### Model unit tests
#enable_testing()
add_executable(ModelTest
  tests/FactorialTest.cpp
)
target_link_libraries(
  ModelTest
  Model
)
#include(GoogleTest)
#gtest_discover_tests(ModelTest)
