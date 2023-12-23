add_executable(CLI
	main.cpp
)
target_include_directories(CLI PUBLIC ${GlobalIncludes})
target_link_libraries(CLI
	AuroraAPI
        ${GlobalLink}
)
