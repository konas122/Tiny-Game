cmake_minimum_required(VERSION 3.10)

project(tinyDoom)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")


include(CheckCXXCompilerFlag)
function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

# enable_cxx_compiler_flag_if_supported("-Wall")
# enable_cxx_compiler_flag_if_supported("-Wextra")
# enable_cxx_compiler_flag_if_supported("-pedantic")
enable_cxx_compiler_flag_if_supported("-std=c++17")
enable_cxx_compiler_flag_if_supported("-O3")



file(GLOB SOURCES 
    "${SRC_DIR}/*.h"
    "${SRC_DIR}/*.cpp"
)


add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

find_package(SDL2 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	SDL2::SDL2
	SDL2::SDL2main
)

