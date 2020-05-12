/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 19:01:04 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

/*
** word_sizes.c
*/

t_exectoken		*all_parse(char *cmd);

/*
** change_tilda.c
*/

char			*do_zam_str_with_tilda(char *str);

/*
** check_bracket.c
*/

int				check_bracket(char *str);

/*
** create_dop_struct.c
*/

t_dop_str		*cr_dop_str_par(void);
t_dop_str		*cr_dop_str_par1(t_lextoken *tmp1);

/*
** dop_parser.c
*/

int						is_cmd_delim(int i);
int						is_cmd_redirect(int i);
void					dop_cr_new_exec(t_dop_str *t,
						t_exectoken *prev, int op_type, int type);
t_exectoken				*ft_cr_new_exectoken(t_lextoken *tmp,
						t_exectoken *prev, int op_type, t_dop_str *t);

/*
** is_system_symbol.c
*/

int		is_system_symbol(char c);

/*
** main_parser.c
*/

t_exectoken		*do_parser(t_lextoken *tmp);

#endif
