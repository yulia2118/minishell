#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2020/05/05 18:56:09 by wsallei           #+#    #+#             *#
#*   Updated: 2020/05/15 00:20:40 by wsallei          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

.PHONY: all clean fclean re bonus

NAME = libft.a

SRC =  ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
		ft_memccpy.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	  ft_strlcat.c \
		ft_strlcpy.c  ft_strmapi.c ft_strncmp.c \
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
		ft_toupper.c ft_strnstr.c ft_split.c get_next_line.c get_next_line_utils.c\
		ft_skipspace.c ft_strcmp.c ft_frstsplit.c \
        ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c

O = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror -I. -g -c

all: $(NAME)

%.o: %.c
	clang $(FLAG) $<

$(NAME):$(O)
		ar rc $(NAME) $(O)
		ranlib $(NAME)

clean:
		rm -f $(O)

fclean: clean
		rm -f $(NAME)

re: fclean all
