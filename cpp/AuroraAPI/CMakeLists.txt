add_library(AuroraAPI
	Simulation.h
	Simulation.cpp
	Fitness.h
	Fitness.cpp
)
target_include_directories(AuroraAPI PUBLIC ${GlobalIncludes})
target_link_libraries(AuroraAPI ${GlobalLink})

#http://google.github.io/googletest/quickstart-cmake.html
enable_testing()
add_executable(AuroraAPI_Test
	SimulationTest.cpp
)
target_include_directories(AuroraAPI_Test PUBLIC ${GlobalIncludes})
target_link_libraries(AuroraAPI_Test
	AuroraAPI
	GTest::gtest_main
        ${GlobalLink}
)

include(GoogleTest)
gtest_discover_tests(AuroraAPI_Test)
