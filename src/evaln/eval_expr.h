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
# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdlib.h>

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

typedef struct		s_calce
{
	int				*stackos;
	int				*stackzn;
	t_int			*str;
	int				*error;
	char			*delstr;
}					t_calce;

int					is_znak(int c);
int					eval_expr(char *s, int *error);
void				dostack(int *stackos, int *stackzn, int c, t_int *lastint);
int					calcend(int **stackos, int **stackzn, t_int **str);
char				*ft_main_calc_rec(char *mas, int *error);
int					prior(int c);
int					ft_atoi_with(char *str, int *marker);
t_int				*cr_new_el(char *s, int *error);
void				make_request(int *stackos, t_int *str, int c);
void				addos(int *stackos, int c, t_int *lastint);
void				subos(int *stackos, t_int *lastint);
void				addzn(int *stackzn, int c, t_int *lastint);
void				subzn(int *stackzn, t_int *lastint);
void				ft_putchar(char c);
void				ft_putnbr(int nb);
int					sizeint(int nb);
int					check_calc_str(char *str);
char				*change_vars(char *evalstr);
int					c_e(t_calce calce);
int					check_calc_sc(char *str);
t_int				*tmp_0(t_int *tmp, char *s);

#endif
