#####################################################################
##  SPDLOG   ########################################################
#####################################################################
add_subdirectory(spdlog)

#####################################################################
##  GTEST  ##########################################################
#####################################################################
if(MSVC)
	#Use shared (DLL) run-time lib even when Google Test is built as static lib.
	#When other libraries are using a shared version of runtime libraries,
	#Google Test also has to use one.
	#and apparently we do with MSVC...
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_subdirectory(gtest)

#####################################################################
##  Benchmark   #####################################################
#####################################################################
option(BENCHMARK_ENABLE_TESTING "" OFF)
add_subdirectory(benchmark)
