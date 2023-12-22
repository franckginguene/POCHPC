cmake_minimum_required(VERSION 3.15)

project(Aurora VERSION 1.0.0 LANGUAGES CXX)

#####################################################################
##  Global config   #################################################
#####################################################################

set(CMAKE_CXX_STANDARD 17)  # VS19
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
	 add_compile_options("$<$<CONFIG:RELEASE>:/O2>")  # compiler optimisation level
else()
	 add_compile_options("$<$<CONFIG:RELEASE>:-O3>")  # compiler optimisation level
endif()

macro(enableStrictWarnings) # call this macro in a subdir CMakeLists to enable strict warnings
	if(MSVC)
		 add_compile_options("/W4" "/WX")
	else()
		 add_compile_options("-Wall" "-Wextra" "-pedantic" "-Werror")
	endif()
endmacro()

set(GlobalIncludes
	../  # This will be interpreted relatively for each usage and is not relative to this current file
	${CMAKE_SOURCE_DIR}/3rdParties/spdlog/include
	${CMAKE_SOURCE_DIR}/3rdParties/eigen
	${CMAKE_SOURCE_DIR}/3rdParties/gtest/googletest/include
	${CMAKE_SOURCE_DIR}/3rdParties/backward-cpp
	# The path to the 3rdParty dependencies is added to enable the implementation of a 'proxy' that 
	# avoids warnings for external includes. This way, we can compile our code with a high level of warning and consider warnings as errors.
	${CMAKE_SOURCE_DIR}/3rdParties
)  # Declared before adding subdirectories to let them inherit it

if(MINGW)
        set(GlobalLink
                dbghelp
        )  # Declared before adding subdirectories to let them inherit it
endif()


#####################################################################
##  subdirs   #######################################################
#####################################################################

add_subdirectory(3rdParties)
add_subdirectory(AuroraAPI)
add_subdirectory(AuroraCLI)
add_subdirectory(MDD)
add_subdirectory(Validator)
add_custom_target(ConfigFiles SOURCES #Show these files in the IDEs
	../.gitignore
)
