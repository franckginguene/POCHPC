cmake_minimum_required(VERSION 3.10)

project(aurora VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)#VS19
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(sources/Model)
add_subdirectory(sources/CLI)
add_subdirectory(sources/3rdParties/spdlog-1.x)
add_subdirectory(sources/3rdParties/gtest)
add_custom_target(ConfigFiles SOURCES #to show in IDEs
	.gitignore
)
