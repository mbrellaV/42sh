/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 19:01:04 by qmartina          #+#    #+#             */
/*   Updated: 2019/12/19 19:01:06 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct				s_lextoken
{
	struct s_lextoken		*prev;
	struct s_lextoken		*next;
	int						is_near_opt;
	char					*line;
	int						operator_type;
	int						word_type;
}							t_lextoken;

typedef struct				s_exectoken
{
	struct s_exectoken		*left;
	struct s_exectoken		*right;
	char					**file_args;
	char					**file_opt;
}							t_exectoken;

typedef struct				s_dop_str_for_cr_new
{
	int						f;
	int						dopi;
	t_lextoken				*dop;
	t_exectoken				*tmp1;
}							t_dop_str_for_cr_new;

typedef struct				s_dop_bax
{
	int						i;
	char					*new;
	char					*tmp;
	char					*tmp1;
	int						c;
	char					*str;
}							t_dop_bax;

typedef struct				s_dop_str
{
	int						i;
	t_exectoken				*prevdot;
	t_exectoken				*prev;
	t_exectoken				*start;
	char					*tmp;
	int						dop;
	int						d;
	t_lextoken				*tail;
	t_lextoken				*doptail;
}							t_dop_str;

void						ft_printf(const char *fmt, ...);
t_exectoken					*all_parse(char *cmd);
t_exectoken					*do_parser(t_lextoken *tmp);
int							get_op_type(char *operator);
t_lextoken					*do_lexer(char *line, t_dop_str *tmp);
t_lextoken					*ft_zach_dop_str_orig(t_dop_str *t,
							t_lextoken *tmp);
t_dop_str					*cr_dop_str_par(void);
int							isoperator(char c);
int							isword(char c);
int							get_op_type(char *operator);
char						*do_zamena_sp(char *line);
int							ispar(char c);
t_exectoken					*ft_zach(t_exectoken *tmp,
							t_dop_str_for_cr_new *t_dop);
int							c_size(char *str, char b);
char						*ft_zach_dop_str(char *tmp, t_dop_bax *t);
int							word_size(char *str);
t_lextoken					*add_token(t_lextoken *start,
							char *line, int word_type);
char						*do_zam_str_bax(char *str1);
char						*do_obr_zamena_sp(char *line);
char						*do_zam_str_bax(char *str1);
t_exectoken					*ft_zach_yyy(t_exectoken *tmp, t_dop_str *t);
void						dop_cr_new_exec(t_dop_str_for_cr_new *t,
							t_exectoken *prev, int op_type, int type);
t_dop_str_for_cr_new		*cr_dop_str_par1(t_lextoken *tmp1);
t_exectoken					*ft_cr_new_exectoken(t_lextoken *tmp,
							t_exectoken *prev, int op_type);
char						*find_var(char *dop);
int							ft_error(int error, char *dopline);
int							is_cmd_delim(int i);

#endif
