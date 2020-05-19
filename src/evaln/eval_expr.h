/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:38:28 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/04 13:44:12 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_EXPR_H
# define EVAL_EXPR_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"

typedef enum			e_calc_tkntype
{
	CALC_START = 0,
	CALC_ERROR = 1,
	CALC_END = 2,
	CALC_NUMBER = 3,
	CALC_PLUS = 4,
	CALC_MINUS = 5,
	CALC_MUL = 6,
	CALC_DIV = 7,
	CALC_MOD = 8,
	CALC_INC = 9,
	CALC_DEC = 10,
	CALC_LESS = 11,
	CALC_MORE = 12,
	CALC_LESSOREQ = 13,
	CALC_MOREOREQ = 14,
	CALC_EQ = 15,
	CALC_DIFF = 16,
	CALC_AND = 17,
	CALC_OR = 18,
	CALC_VAR = 19,
	CALC_PRE_INC = 20,
	CALC_PRE_DEC = 21,
	CALC_FIR_SC = 22,
	CALC_SEC_SC = 23
}						t_calc_tkntype;

typedef struct		s_calc_token
{
	t_calc_tkntype			type;
	char					*var;
	struct s_calc_token		*next;
	struct s_calc_token		*prev;
}					t_calc_token;


typedef struct		s_int
{
	int				ol;
	int				zl;
	int				d;
	int				*stackos;
	int				*stackzn;
	int				i;
	int				last_token;
	char			*s;
}					t_int;

typedef struct		s_calc
{
	int				*stackos;
	int				*stackzn;
	t_int			*str;
	int				*error;
	char			*delstr;
}					t_calc;

int					is_znak(int c);
int					eval_expr(char *s, int *error);
void				dostack(int *stackos, int *stackzn, t_calc_tkntype c, t_int *lastint);
int					calcend(int **stackos, int **stackzn, t_int **str);
char				*ft_main_calc_rec(char *mas, int *error);
int					prior(int c);
int					ft_atoi_with(char *str, int *marker);
int					is_znak_type(t_calc_tkntype type);
t_int				*cr_new_el(char *s, int *error);
void				calc(int *stackos, t_int *str, t_calc_tkntype c);
void				addos(int *stackos, int c, t_int *lastint);
void				subos(int *stackos, t_int *lastint);
void				addzn(int *stackzn, t_calc_tkntype c, t_int *lastint);
void				subzn(int *stackzn, t_int *lastint);
void				ft_putchar(char c);
int					opr_znak(char *dstr);
void				ft_putnbr(int nb);
int					sizeint(int nb);
int					check_calc_str(char *str);
int					c_e(t_calc calce);
int					check_calc_sc(char *str);
t_int				*tmp_0(t_int *tmp, char *s);
t_calc_token		*ft_cr_new_calc_token(char *line, t_calc_tkntype type);
char					*calc_ltoa(long long num);
int						is_incr_sym(char c);
int						calc_word_size(char *str);
char					*change_vars(char *evalstr);
t_calc_token			*calc_define_token(char *str);
t_calc_token		*add_token_cr(t_calc_token *start, t_calc_token *token_to_add);
t_calc_token		*ft_make_token_from_str(char *str, int *i, t_calc_token *prev_token);
t_calc_token		*ft_eval_parse(char *str);
int					issc(char c);

/*
** calc_lexer.c
*/

char					*ft_main_calc_rec(char *mas, int *error);
t_calc_token				*calc_get_next_tkn(char *str, size_t pos);
t_calc_token				*calc_define_token_next(char *str);


#endif
