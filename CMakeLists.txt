cmake_minimum_required(VERSION 3.10)

project(aurora VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)#VS19
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(sources/Model)
add_subdirectory(sources/CLI)
add_subdirectory(sources/3rdParties/spdlog)

if(MSVC)
	#Use shared (DLL) run-time lib even when Google Test is built as static lib.
	#When other libraries are using a shared version of runtime libraries,
	#Google Test also has to use one.
	#and apparently we do with MSVC...
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
add_subdirectory(sources/3rdParties/gtest)

add_custom_target(ConfigFiles SOURCES #Show these files in the IDEs
	.gitignore
	)
