include_directories(
  ${CMAKE_SOURCE_DIR}/sources/Model/include
  ${CMAKE_SOURCE_DIR}/sources/3rdParties/spdlog-1.x/include
)

add_executable(
  CLI
  main.cpp
)

target_link_libraries(CLI
	PUBLIC Model
)
