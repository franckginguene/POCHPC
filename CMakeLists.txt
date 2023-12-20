cmake_minimum_required(VERSION 3.10)

project(aurora VERSION 1.0.0 LANGUAGES CXX)

# Configuration pour le mode Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -W3")

# Configuration pour le mode Release
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Configuration commune
set(CMAKE_CXX_STANDARD 17)#VS19
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Définit un symbole pour récupérer le chemin du projet dans le code
add_definitions(-DPROJECT_PATH="${CMAKE_SOURCE_DIR}")

add_subdirectory(sources/Model)
add_subdirectory(sources/Validation)
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
