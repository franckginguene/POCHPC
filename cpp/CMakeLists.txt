cmake_minimum_required(VERSION 3.10)

project(Aurora VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)#VS19
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GlobalIncludes
	../  # This will be interpreted relatively for each usage and is not relative to this current file.
	${CMAKE_SOURCE_DIR}/3rdParties/spdlog/include
	${CMAKE_SOURCE_DIR}/3rdParties/eigen
	${CMAKE_SOURCE_DIR}/3rdParties/gtest/googletest/include
	${CMAKE_SOURCE_DIR}/3rdParties/backward-cpp
)  # Declared before adding subdirectories to let them inherit it

add_subdirectory(3rdParties)
add_subdirectory(AuroraAPI)
add_subdirectory(AuroraCLI)
add_subdirectory(MDD)

add_custom_target(ConfigFiles SOURCES #Show these files in the IDEs
	../.gitignore
)
