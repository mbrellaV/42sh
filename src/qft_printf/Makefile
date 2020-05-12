# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmartina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 16:01:11 by qmartina          #+#    #+##   Updated: 202#    Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

PATH_LIBFT = libft

SRC = ft_printf.c\
		ft_add_c_s_d.c\
		add_char.c\
		add_str.c\
		ft_oxu.c\
		ft_pars.c\
		ft_pars2.c\
		ft_pr_help.c\
		add_buff.c\
		add_d.c\
		ft_itoa_base_c.c\
		ft_add_double.c\
		ft_okr_double.c\
		ft_pointer.c\
		ft_math.c\
		ft_dtoa.c\

OBJ = $(patsubst %.c,%.o,$(SRC))

all: $(NAME)

$(NAME): $(PATH_LIBFT)/libft.a $(OBJ)
	$(CC) $(CFLAGS) -I libftprintf.h -c $(SRC)
	@cp $(PATH_LIBFT)/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(PATH_LIBFT)/libft.a:
	make -C $(PATH_LIBFT)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)
	make -C $(PATH_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(PATH_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re