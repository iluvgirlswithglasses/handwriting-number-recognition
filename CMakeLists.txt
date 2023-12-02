cmake_minimum_required (VERSION 3.9)
project(ib-face CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include(CheckIPOSupported)
check_ipo_supported(RESULT result OUTPUT output)
if(result)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
else()
	message(WARNING "IPO is not supported: ${output}")
endif()

include(CheckCXXCompilerFlag)
include(AddCXXCompilerFlag)

add_cxx_compiler_flag(-DUSE_SSE2_INSTRUCTIONS=ON)
add_cxx_compiler_flag(-DUSE_SSE4_INSTRUCTIONS=ON)
add_cxx_compiler_flag(-DUSE_AVX_INSTRUCTIONS=ON)

if (MSVC)
	string(REGEX REPLACE "[-/]W[1-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

	add_cxx_compiler_flag(-GS-)
	add_cxx_compiler_flag(-Ob2)
	add_cxx_compiler_flag(-Oi)
	add_cxx_compiler_flag(-Ot)
	add_cxx_compiler_flag(-Oy)
	add_cxx_compiler_flag(-GT)
	add_cxx_compiler_flag(-Zc:__cplusplus)
	add_cxx_compiler_flag(-march=native)

else()
	add_cxx_compiler_flag(-O3)
	add_cxx_compiler_flag(-march=native)
	add_cxx_compiler_flag(-mtune=native)

	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		find_program(GCC_AR gcc-ar)
		if (GCC_AR)
			set(CMAKE_AR ${GCC_AR})
		endif()
		find_program(GCC_RANLIB gcc-ranlib)
		if (GCC_RANLIB)
			set(CMAKE_RANLIB ${GCC_RANLIB})
		endif()
	elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
		include(llvm-toolchain)
	endif()
endif()

add_subdirectory(dlib)
file(GLOB SRC_FILES src/*.h src/*.cpp)
file(GLOB CLI_FILES cli/*.h cli/*.cpp)

add_executable(number-recog param.h ${SRC_FILES} ${CLI_FILES})
target_link_libraries(number-recog dlib::dlib)

