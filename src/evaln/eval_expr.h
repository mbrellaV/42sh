/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:38:28 by mbrella           #+#    #+#             */
/*   Updated: 2020/04/14 11:27:20 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_EXPR_H
# define EVAL_EXPR_H

# include "../../inc/fshell.h"

typedef struct		s_int
{
	int				ol;
	int				zl;
	int				i;
}					t_int;

int					is_znak(int c);
int					eval_expr(char *s);
void				dostack(int *stackos, int *stackzn, int c, t_int *lastint);
int					calcend(int **stackos, int **stackzn, t_int **str);
char				*ft_main_calc_rec(char *mas);
int					prior(int c);
int					ft_atoi_with(char *str, int *marker);
t_int				*cr_new_el();
void				calc(int *stackos, t_int *str, int c);
void				addos(int *stackos, int c, t_int *lastint);
void				subos(int *stackos, t_int *lastint);
void				addzn(int *stackzn, int c, t_int *lastint);
void				subzn(int *stackzn, t_int *lastint);
void				ft_putchar(char c);
void				ft_putnbr(int nb);
int					sizeint(int nb);

#endif
