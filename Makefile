# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmartina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 16:01:11 by qmartina          #+#    #+#              #
#    Updated: 2019/10/17 16:01:15 by qmartina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 21sh

SRC = src/main.c src/ft_error_q.c src/ft_distruct.c src/errors/errror_handler.c \
src/builtins/ft_echo.c src/builtins/ft_cd.c src/ft_take_arg.c \
src/exec/ft_fun_fork.c src/exec/ft_create_file.c src/builtins/ft_echo2.c src/ft_signal.c \
src/lexer/lexer.c src/lexer/dop_lexer0.c src/lexer/dop_lexer1.c src/lexer/dop_lexer2.c src/lexer/dop_lexer3.c\
src/parser/main_parser.c src/parser/dop_parser.c src/parser/dop_parser1.c\
src/nucleus/ft_cutcopy.c src/nucleus/ft_read_8.c \
src/exec/ft_do_pipe.c src/nucleus/nucleus.c src/nucleus/nucleus2.c src/nucleus/nucleus3.c src/nucleus/nucleus4.c src/builtins/allenv/main_env.c src/builtins/allenv/ft_env.c src/builtins/alias/ft_alias.c src/eval/atoimy.c src/eval/calc.c src/eval/dop.c src/eval/ft_do_zam_eval.c src/eval/inftopost.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(OBJ) -I inc -o $(NAME) -L libft/ -lft -ltermcap
	@echo "\033[32m21sh: Built.\033[0m"

%.o:%.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@make -C libft/ clean
	@/bin/rm -rf $(OBJ)
	@echo "\033[32m21sh: Cleaned up object files.\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME) $(OBJ)
	@echo "\033[32m21sh: Cleaned up compiled files.\033[0m"

re: fclean $(NAME)
