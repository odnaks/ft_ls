# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drestles <drestles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/22 02:59:15 by drestles          #+#    #+#              #
#    Updated: 2019/03/01 20:55:28 by pcollio-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRC =  ft_strlen.c ft_strdup.c ft_strcpy.c \
	  ft_strncpy.c ft_strcat.c ft_strncat.c \
	  ft_strchr.c ft_strrchr.c ft_strstr.c \
	  ft_strnstr.c ft_strcmp.c ft_strncmp.c \
	  ft_memset.c ft_bzero.c ft_memcpy.c \
	  ft_memccpy.c ft_memmove.c ft_memchr.c \
	  ft_memcmp.c ft_strlcat.c ft_atoi.c \
	  ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	  ft_isascii.c ft_isprint.c ft_toupper.c \
	  ft_tolower.c ft_putchar.c ft_putstr.c \
	  ft_putchar_fd.c ft_putstr_fd.c \
	  ft_memalloc.c ft_memdel.c ft_strnew.c \
	  ft_strdel.c ft_strclr.c ft_striter.c \
	  ft_striteri.c ft_strmap.c ft_strmapi.c \
	  ft_strequ.c ft_strnequ.c ft_strsub.c \
	  ft_strjoin.c ft_strtrim.c ft_itoa.c \
	  ft_putnbr.c ft_putendl.c ft_putnbr_fd.c \
	  ft_putendl_fd.c ft_strsplit.c ft_lstnew.c \
 	  ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	  ft_lstiter.c ft_lstmap.c get_next_line.c \
	  ft_strjoin_all.c ft_strjoin_left.c ft_strjoin_right.c\
	  ft_itoal.c \
	  ft_itoal_u.c \
	  ft_printf.c \
	  printf_first_flags.c \
	  printf_second_flags.c \
	  printf_third_flags.c \
	  printf_def_percentage.c \
	  printf_handle_f.c \
	  printf_handle_d.c \
	  printf_handle_u.c \
	  printf_unicode.c \
	  printf_handle_c.c \
	  printf_handle_s.c \
	  printf_handle_lc.c \
	  printf_handle_ls.c \
	  printf_handle_x.c \
	  printf_handle_o.c \
	  printf_handle_lx.c \
	  printf_handle_p.c \
	  printf_types.c \


all: $(NAME)

OBJ = $(SRC:.c=.o)

HDRS = libft.h

$(NAME): 
	gcc $(FLAGS) -c $(SRC) -I $(HDRS)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re
