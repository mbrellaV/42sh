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

typedef struct				s_dop_str
{
	///////////////s_dop_str_for
	int						f_a;
	int						dopi_a;
	t_lextoken				*dop_a;
	t_exectoken				*tmp1_a;
	///////////////////////////////////////dop_bax
	int						i_b;
	char					*new_b;
	char					*tmp_b;
	char					*tmp1_b;
	int						c_b;
	char					*str_b;
	/////////////////////////////////////////////
	int						i_c;
	t_exectoken				*prevdot_c;
	t_exectoken				*prev_c;
	t_exectoken				*start_c;
	char					*tmp_c;
	int						dop_c;
	int						d_c;
	t_lextoken				*tail_c;
	t_lextoken				*doptail_c;
}							t_dop_str;

t_lextoken					*ft_kill_str_dop(t_dop_str *t, t_lextoken *tmp);
t_lextoken					*do_lexer(char *line);
void						ft_printf(const char *fmt, ...);
t_exectoken					*all_parse(char *cmd);
t_exectoken					*do_parser(t_lextoken *tmp);
char						*do_zam_str_hist_var(char *str1, t_memory *q);
int							get_op_type(char *operator);
t_dop_str					*cr_dop_str_par(void);
int							isoperator(char c);
int							isword(char c);
int							get_op_type(char *operator);
char						*do_zamena_sp(char *line);
int							ispar(char c);
t_exectoken					*ft_cr_new_exectoken(t_lextoken *tmp,
							t_exectoken *prev, int op_type, t_dop_str *t);
int							c_size(char *str, char b);
int							word_size(char *str);
t_lextoken					*add_token(t_lextoken *start,
							char *line, int word_type);
char						*do_obr_zamena_sp(char *line);
char						*do_zam_str_bax(char *str1, t_dop_str	*t);
int							do_zam_bax_and_hist_full(char **mas, t_memory *t);
void						dop_cr_new_exec(t_dop_str *t,
							t_exectoken *prev, int op_type, int type);
t_dop_str					*cr_dop_str_par1(t_lextoken *tmp1);
int							ft_error(int error, char *dopline);
int							is_cmd_delim(int i);

#endif
