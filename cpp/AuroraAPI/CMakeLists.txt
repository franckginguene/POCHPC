include_directories(
	${CMAKE_SOURCE_DIR}/3rdParties/spdlog/include
	${CMAKE_SOURCE_DIR}/3rdParties/eigen
	${CMAKE_SOURCE_DIR}/3rdParties/gtest/googletest/include
)

add_library(AuroraAPI
	Factorial.h
	Factorial.cpp
)

#http://google.github.io/googletest/quickstart-cmake.html
enable_testing()
add_executable(AuroraAPI_Test
	FactorialTest.cpp
)
target_link_libraries(AuroraAPI_Test
	AuroraAPI
	GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(AuroraAPI_Test)
