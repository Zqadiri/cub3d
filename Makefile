# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 10:41:21 by zqadiri           #+#    #+#              #
#    Updated: 2020/11/17 13:23:21 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	 cub3D 
MINILIBX_PATH 	= 	./minilibx
LIBFT_PATH 		= 	./libft

FILES_PATH 		=	./main.c\
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
					
OBJS			= 	${SRCS:.c=.o}
INCLUDE 		= 	Cub3d.h
LIBFT 			= 	libft
MINILIBX 		= 	miniLibx
CC				= 	gcc -g -Wall -Wextra -Werror -fsanitize=address
RM				= 	rm -f
MLXFLAGS 		=	-lmlx -framework OpenGl -framework Appkit
LIBFLAGS 		=	./libft/*.c 

# -I Add the directory dir to the list of directories to be searched for header files
# -L Searches the library when linking
# $@ is the name of the target being generated
# @	Don’t print command


all:			all_libft all_mini $(NAME)

$(NAME):		
				@$(CC) $(MLXFLAGS) $(LIBFLAGS) libft.a libmlx.a -I./ $(OBJS) -o $@ 

clean:			clean_libft clean_mini
				@${RM} ${OBJS}

fclean:			fclean_libft fclean_mini clean
				@${RM} ${NAME}

re:				fclean all

# make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command

all_libft:
				make -C $(LIBFT_PATH) all
				cp ./libft/libft.a libft.a

clean_libft:
				make -C $(LIBFT_PATH) clean

fclean_libft:
				make -C $(LIBFT_PATH) fclean
				$(RM) libft.a

all_mini:
				make -C $(MINILIBX_PATH) all
				cp ./minilibx/libmlx.a libmlx.a

clean_mini:
				make -C $(MINILIBX_PATH) clean


fclean_mini:
				make -C $(MINILIBX_PATH) clean
				$(RM) libmlx.a

.PHONY:
				all fclean clean re
				
