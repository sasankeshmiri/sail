cmake_minimum_required(VERSION 3.5)

project(Sail-prototype VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CMakePrintHelpers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Weffc++ -Werror -fmax-errors=5")
if (!WIN32)
	set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lSDL2 -lSDL2_image")
endif()

if (WIN32)
	set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -I/mnt/d/sail/Source/lib/i686-w64-mingw32/include/ -L/mnt/d/sail/Source/lib/i686-w64-mingw32/lib -lSDL2 -lSDL2_image ${CMAKE_CXX_STANDARD_LIBRARIES}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive,-subsystem,windows -lwinpthread -Wl,--no-whole-archive")

	#add_library(SDL2_LIB SHARED IMPORTED)
	#set_target_properties(SDL2_LIB PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../Source/lib/i686-w64-mingw32.so)
	
	cmake_print_variables(CMAKE_BINARY_DIR)
	cmake_print_variables(CMAKE_SOURCE_DIR)
	cmake_print_variables(CMAKE_PREFIX_PATH)
	endif()

# TODO 8: Use configure_file to configure and copy TutorialConfig.h.in to
#         TutorialConfig.h
configure_file(SailConfig.h.in SailConfig.h)

# TODO 3: Add an executable called Tutorial to the project
# Hint: Be sure to specify the source file as tutorial.cxx
add_executable(sail-prototype ${CMAKE_SOURCE_DIR}/../Source/Sail.cpp ${CMAKE_SOURCE_DIR}/../Source/Graphics.cpp)

if (WIN32)
	set(SDL2_DIR ${CMAKE_SOURCE_DIR}/../Source/lib/i686-w64-mingw32/lib/cmake/SDL2)
	set(SDL2_image_DIR ${CMAKE_SOURCE_DIR}/../Source/lib/i686-w64-mingw32/lib/cmake/SDL2_image)
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	target_link_libraries(sail-prototype SDL2::SDL2 SDL2_image::SDL2_image)
	add_custom_command(TARGET sail-prototype POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:sail-prototype> $<TARGET_FILE_DIR:sail-prototype>
  COMMAND_EXPAND_LISTS
  )
endif()

# TODO 9: Use target_include_directories to include ${PROJECT_BINARY_DIR}
target_include_directories(sail-prototype PUBLIC ${PROJECT_BINARY_DIR}/../../Source)
target_link_directories(sail-prototype PUBLIC ${PROJECT_BINARY_DIR}/../../Source/lib/i686-w64-mingw32/lib)

cmake_print_variables(PROJECT_BINARY_DIR)
