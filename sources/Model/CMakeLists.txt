### Model
add_library(Model
  include/Model/Factorial.h
  sources/Model/Factorial.cpp
)
target_include_directories(Model
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

### Model unit tests
enable_testing()
add_executable(ModelTest
  tests/FactorialTest.cpp
)
target_link_libraries(
  ModelTest
  Model gtest_main
)
include(GoogleTest)
gtest_discover_tests(ModelTest)

include_directories(${CMAKE_SOURCE_DIR}/sources/3rdParties/spdlog-1.x/include)
include_directories(${CMAKE_SOURCE_DIR}/sources/3rdParties/eigen-3.4.0/)
#target_include_directories(yourTarget PUBLIC ${CMAKE_SOURCE_DIR}/libs)