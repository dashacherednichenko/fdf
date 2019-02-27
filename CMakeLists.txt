cmake_minimum_required(VERSION 3.13)
project(fdf C)

set(CMAKE_C_STANDARD 99)
SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")
AUX_SOURCE_DIRECTORY(libft LIB)
add_executable(fdf ${LIB} main.c)
link_libraries(libft/libft.a)