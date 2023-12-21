enableStrictWarnings()

add_custom_target(HeaderOnly SOURCES  # Show these files in the IDEs
	OptTraced.h
)

enable_testing()
add_executable(MDD_Test
	OptTracedTests.cpp
)
target_include_directories(MDD_Test PUBLIC ${GlobalIncludes})
target_link_libraries(MDD_Test
	GTest::gtest_main
        ${GlobalLink}
)
include(GoogleTest)
gtest_discover_tests(MDD_Test)
