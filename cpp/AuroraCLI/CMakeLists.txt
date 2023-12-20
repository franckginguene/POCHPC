add_executable(CLI
	main.cpp
)
target_include_directories( CLI PUBLIC
	../
	${CMAKE_SOURCE_DIR}/3rdParties/spdlog/include
)
target_link_libraries( CLI
	AuroraAPI
)
