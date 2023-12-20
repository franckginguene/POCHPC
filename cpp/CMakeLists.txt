cmake_minimum_required(VERSION 3.10)

project(Aurora VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)#VS19
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(AuroraAPI)
add_subdirectory(AuroraCLI)
add_subdirectory(3rdParties)

add_custom_target(ConfigFiles SOURCES #Show these files in the IDEs
	../.gitignore
)
