cmake_minimum_required(VERSION 3.2)

project(Sail-prototype VERSION 1.0)

include(CMakePrintHelpers)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Weffc++ -Werror -fmax-errors=5")
if (WIN32)
	message(STATUS "SETTING WINDOWS FLAGS!!")
	set(CMAKE_CXX_STANDARD_LIBRARIES "--static ${CMAKE_CXX_STANDARD_LIBRARIES}")
	#set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive,-subsystem,windows -lwinpthread -Wl,--no-whole-archive")
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive,-subsystem,windows -lwinpthread -Wl,--no-whole-archive")
endif()

#configure_file(SailConfig.h.in ${CMAKE_SOURCE_DIR}/src/SailConfig.h)

add_executable(sail-prototype ${CMAKE_SOURCE_DIR}/src/Sail.cpp ${CMAKE_SOURCE_DIR}/src/Graphics.cpp)

if(WIN32)
	set(SDL2_DIR ${CMAKE_SOURCE_DIR}/src/lib/i686-w64-mingw32/lib/cmake/SDL2)
	set(SDL2_image_DIR ${CMAKE_SOURCE_DIR}/src/lib/i686-w64-mingw32/lib/cmake/SDL2_image)
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	target_link_libraries(sail-prototype SDL2::SDL2-static SDL2_image::SDL2_image-static)
	target_include_directories(sail-prototype PUBLIC ${CMAKE_SOURCE_DIR}/src/lib/i686-w64-mingw32/include/)
	#add_custom_command(TARGET sail-prototype POST_BUILD
  #COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:sail-prototype> $<TARGET_FILE_DIR:sail-prototype> COMMAND_EXPAND_LISTS)
else()
	target_link_libraries(sail-prototype SDL2 SDL2_image)
	#add_custom_command(TARGET sail-prototype POST_BUILD
  #COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:sail-prototype> $<TARGET_FILE_DIR:sail-prototype> COMMAND_EXPAND_LISTS)
endif()

target_include_directories(sail-prototype PUBLIC ${CMAKE_SOURCE_DIR}/src)
