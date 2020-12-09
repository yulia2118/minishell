#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2020/11/19 19:09:10 by wsallei           #+#    #+#             *#
#*   Updated: 2020/11/19 19:09:12 by wsallei          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

.PHONY: all clean fclean

NAME = minishell

LIBFT = -L libft -lft

SRCS = src/parser/main.c \
		src/parser/toks.c \
		src/parser/tool.c \
		src/parser/env.c \
		src/parser/redir.c \
		src/exec/exec.c \
		src/exec/redirect.c \
		src/exec/tool.c \
		src/exec/ex.c \
		src/exec/fd.c \
		src/exec/prerdir.c \
		src/exec/pipe.c \
		src/exec/execute.c \
		src/builtin/exbuiltin.c \
		src/builtin/ft_cd.c \
		src/builtin/ft_echo.c \
		src/builtin/ft_env.c \
		src/builtin/ft_env_utils.c \
		src/builtin/ft_export.c \
		src/builtin/ft_unset.c \
		src/builtin/ft_pwd.c \
		src/builtin/ft_signal.c \
		src/exit/exit.c

O = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	clang $(FLAG) -g -c $< -o $@

$(NAME): $(O)
		make -C libft
		clang -o $(NAME) $(O) $(LIBFT)

clean:
		make -C libft clean
		rm -f $(O)

fclean:
		make -C libft fclean
		rm -f $(O)
		rm -f $(NAME)

re: fclean all