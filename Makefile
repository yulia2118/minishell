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
		src/parser/syntaxerr.c \
		src/parser/toks.c \
		src/parser/toks2.c \
		src/parser/tool.c \
		src/parser/chredir.c \
		src/parser/tool2.c \
		src/parser/env.c \
		src/parser/slh.c \
		src/parser/redir.c \
		src/exec/exec.c \
		src/exec/hub.c \
		src/exec/bin.c \
		src/exec/redirect.c \
		src/exec/tool.c \
		src/exec/ex.c \
		src/exec/fd.c \
		src/exec/prerdir.c \
		src/exec/pipe.c \
		src/exec/slhs.c \
		src/exec/pipe2.c \
		src/exec/execute.c \
		src/exec/speclen.c \
		src/exec/funcname.c \
		src/exec/string.c \
		src/builtin/exbuiltin.c \
		src/builtin/ft_cd.c \
		src/builtin/ft_echo.c \
		src/builtin/ft_env.c \
		src/builtin/ft_env_utils.c \
		src/builtin/ft_export.c \
		src/builtin/ft_unset.c \
		src/builtin/ft_pwd.c \
		src/builtin/ft_signal.c \
		src/builtin/ecpu.c \
		src/builtin/unsutils.c \
		src/builtin/exportutils.c \
		src/exit/exit.c

O = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	clang -g -c $(FLAGS) $< -o $@

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