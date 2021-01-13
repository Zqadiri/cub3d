# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 10:41:21 by zqadiri           #+#    #+#              #
#    Updated: 2021/01/13 11:51:48 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	 cub3D 
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
					./srcs/utils2.c\
					./srcs/utils3.c\
					./srcs/utils.c\
					./srcs/bmp.c\
					./srcs/sprite_raycasting.c\
					./srcs/sprite_raycasting2.c\
					./srcs/error_funcs2.c\
					./srcs/error_funcs3.c\
					./srcs/raycasting.c\
					./srcs/raycasting2.c
					
OBJS			= 	${SRCS:.c=.o}
INCLUDE 		= 	cub.h
LIBFT 			= 	libft
CC				= 	gcc  -Wall -Wextra -Werror -Ofast
RM				= 	rm -f
MLXFLAGS 		=   /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
LIBFLAGS 		= 	-I ./libft -L ./libft -L . ./libft/*.c 

# -I Add the directory dir to the list of directories to be searched for header files
# -L Searches the library when linking
# $@ is the name of the target being generated
# @	Don’t print command

all:			 ${NAME} libft_all

$(NAME):		${OBJS} 
				$(CC) -o $(NAME)  $(SRCS) $(LIBFLAGS) -L $(MLXFLAGS) 

clean:			libft_clean
				@${RM} ${OBJS}
fclean:			libft_fclean clean
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
				
.PHONY: 		all fclean clean re