cmake_minimum_required(VERSION 3.17)
project(TEST C)

set(CMAKE_C_STANDARD 99)

add_executable(TEST srcs/add_data.c
        srcs/check_map.c
        srcs/free.c
        srcs/keycode.c
        srcs/raycasting.c
        srcs/utils.c
        srcs/bmp.c
        srcs/check_paths.c
        srcs/get_elements.c
        srcs/main.c
        srcs/sprite_raycasting.c
        srcs/utils2.c
        srcs/check.c
        srcs/error_funcs.c
        srcs/get_textures.c
        srcs/parsing.c
        srcs/sprite_raycasting2.c
        srcs/check_data.c
        srcs/error_funcs2.c
        srcs/init.c
        srcs/parsing2.c
        srcs/sprites_data.c)

target_link_libraries(TEST ${CMAKE_SOURCE_DIR}/libmlx.a ${CMAKE_SOURCE_DIR}/libft.a)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Ofast -fsanitize=address -lm -framework OpenGL -framework AppKit")
