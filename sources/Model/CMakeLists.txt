include_directories(
  PUBLIC include
  PUBLIC ${CMAKE_SOURCE_DIR}/sources/3rdParties/spdlog/include
  PUBLIC ${CMAKE_SOURCE_DIR}/sources/3rdParties/eigen
  PUBLIC ${CMAKE_SOURCE_DIR}/sources/3rdParties/gtest/googletest/include
)

add_library(AuroraAPI
  include/Model/Factorial.h
  sources/Model/Factorial.cpp
)


#http://google.github.io/googletest/quickstart-cmake.html
enable_testing()
add_executable(AuroraAPI_Test
  tests/FactorialTest.cpp
)
target_link_libraries(AuroraAPI_Test
  PRIVATE AuroraAPI
  PRIVATE GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(AuroraAPI_Test)
