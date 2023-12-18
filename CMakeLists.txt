cmake_minimum_required(VERSION 3.10)

### Project Configuration
project(aurora VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)#VS19
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip # Release 1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

### Libraries
add_subdirectory(sources/Model)

### 3rdParties
add_subdirectory(sources/3rdParties/spdlog-1.x)
# add_subdirectory(sources/3rdParties/eigen-3.4.0)

### Executables
add_subdirectory(sources/CLI)


add_custom_target(ConfigFiles SOURCES #to show in IDEs
	.gitignore
)
