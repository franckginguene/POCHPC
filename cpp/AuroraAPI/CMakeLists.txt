enableStrictWarnings()

add_library(AuroraAPI
	Factorial.h
	Factorial.cpp
)
target_include_directories(AuroraAPI PUBLIC ${GlobalIncludes})

#http://google.github.io/googletest/quickstart-cmake.html
enable_testing()
add_executable(AuroraAPI_Test
	FactorialTest.cpp
)
target_include_directories(AuroraAPI_Test PUBLIC ${GlobalIncludes})
target_link_libraries(AuroraAPI_Test
	AuroraAPI
	GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(AuroraAPI_Test)
