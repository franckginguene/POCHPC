## Sources
set(CLI_SOURCES
)

## Executable
add_executable(
  CLI
  main.cpp
)

## Libraries dependency
target_link_libraries(CLI PUBLIC Model)

include_directories(${CMAKE_SOURCE_DIR}/sources/3rdParties/spdlog-1.x/include)
