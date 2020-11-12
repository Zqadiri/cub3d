# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 12:11:32 by zqadiri           #+#    #+#              #
#    Updated: 2019/10/24 22:32:22 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libft.a
AR = ar
OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)
CFLAGS = -Wall -Wextra -Werror
SRCB =  ft_lstlast_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstnew_bonus.c\
		ft_lstadd_back_bonus.c\

SRC = ft_memset.c\
	  ft_bzero.c\
	  ft_memcpy.c\
	  ft_memccpy.c\
	  ft_memmove.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_strlen.c\
	  ft_isalpha.c\
	  ft_isdigit.c\
	  ft_isalnum.c\
	  ft_isascii.c\
	  ft_isprint.c\
	  ft_toupper.c\
	  ft_tolower.c\
	  ft_strchr.c\
	  ft_strrchr.c\
	  ft_strncmp.c\
	  ft_strlcpy.c\
	  ft_strlcat.c\
	  ft_strnstr.c\
	  ft_atoi.c\
	  ft_calloc.c\
	  ft_strdup.c\
	  ft_substr.c\
	  ft_strjoin.c\
	  ft_strtrim.c\
	  ft_split.c\
	  ft_itoa.c\
	  ft_strmapi.c\
	  ft_putchar_fd.c\
	  ft_putstr_fd.c\
	  ft_putendl_fd.c\
	  ft_putnbr_fd.c\
		  

all:	$(NAME)

$(NAME): 
		$(CC) $(CFLAGS) -c $(SRC)
	 	$(AR) rsc $(NAME) $(OBJ)
		ranlib $(NAME)
clean:
		rm -rf $(OBJ) $(OBJB)

bonus:
		$(CC) $(CFLAGS) -c $(SRCB)
	 	$(AR) rsc $(NAME) $(OBJB)
		ranlib $(NAME)

fclean: clean
		rm -rf $(NAME)
re: fclean all
    
