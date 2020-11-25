# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 10:41:21 by zqadiri           #+#    #+#              #
#    Updated: 2020/11/25 10:45:25 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	 cub3D 
MINILIBX_PATH 	= 	./minilibx
LIBFT_PATH 		= 	./libft

SRCS 			=	./srcs/main.c\
					./srcs/add_data.c\
					./srcs/check.c\
					./srcs/check_data.c\
					./srcs/check_map.c\
					./srcs/check_paths.c\
					./srcs/error_funcs.c\
					./srcs/free.c\
					./srcs/get_elements.c\
					./srcs/get_textures.c\
					./srcs/init.c\
					./srcs/keycode.c\
					./srcs/parsing.c\
					./srcs/parsing2.c\
					./srcs/sprites_data.c\
					./srcs/utils.c\
					./srcs/bmp.c\
					./srcs/sprite_raycasting.c
					
OBJS			= 	${SRCS:.c=.o}
INCLUDE 		= 	Cub3d.h
LIBFT 			= 	libft
MINILIBX 		= 	miniLibx
CC				= 	gcc -g -Wall -Wextra -Werror -fsanitize=address
RM				= 	rm -f
MLXFLAGS 		= -I ./miniLibx -L ./miniLibx -lmlx -framework OpenGl -framework Appkit
LIBFLAGS 		= -I ./libft -L ./libft -L . ./libft/*.c 

# -I Add the directory dir to the list of directories to be searched for header files
# -L Searches the library when linking
# $@ is the name of the target being generated
# @	Don’t print command

all:			libft_all minilibx_all ${NAME}
$(NAME):		${OBJS} 
				@$(CC) $(MLXFLAGS) $(LIBFLAGS) libft.a libmlx.a -I./ $(OBJS) -o $@ 
clean:			libft_clean minilibx_clean
				@${RM} ${OBJS}
fclean:			libft_fclean minilibx_fclean clean
				@${RM} ${NAME}
re:				fclean all

# make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command
libft_all:
				make -C $(LIBFT_PATH) all
				cp ./libft/libft.a libft.a

libft_clean:
				make -C $(LIBFT_PATH) clean

libft_fclean:
				make -C $(LIBFT_PATH) fclean
				$(RM) libft.a

minilibx_all:
				make -C $(MINILIBX_PATH) all
				cp ./minilibX/libmlx.a libmlx.a

minilibx_clean:
				make -C $(MINILIBX_PATH) clean

minilibx_fclean:
				make -C $(MINILIBX_PATH) clean
				$(RM) libmlx.a
				
.PHONY: 		all fclean clean re
