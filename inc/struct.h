/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:33:44 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/16 10:22:06 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef	struct				s_builtins
{
	int						cd_p;
	int						link;
	int						echo_n;
	int						echo_c;
}							t_builtins;

typedef struct				s_memory
{
	char					*inp;
	struct s_memory			*back;
	struct s_memory			*next;
}							t_memory;

typedef struct				s_readline
{
	char					*buff;
	int						buff_size;
	int						index;
	int						len;
	int						len_hint;
	int						sum_read;
	int						esc;
	int						mod;
	char					**tab;
	int						tab_size;
	int						tab_i;
	int						tab_max;
	int						flag_dir;
	int						flag_left_word;
	int						i_dop;
}							t_readline;

typedef struct				s_pipe
{
	int						flag;
	int						i;
	int						st;
	int						fd;
	int						b;
	int						j;
	int						*infile;
	int						*outfile;
	int						*errfile;
}							t_pipe;

typedef struct				s_lextoken
{
	struct s_lextoken		*prev;
	struct s_lextoken		*next;
	int						is_near_opt;
	char					*line;
	int						operator_type;
	int						inhibitor_lvl;
	int						is_near_word;
}							t_lextoken;

typedef struct				s_exectoken
{
	int						should_wait_and;
	int						should_wait_or;
	struct s_exectoken		*left;
	struct s_exectoken		*right;
	char					**file_args;
	char					**file_opt;
	int						foreground;
}							t_exectoken;

typedef struct				s_dop_str
{
	int						f_a;
	int						dopi_a;
	t_lextoken				*dop_a;
	t_exectoken				*tmp1_a;
	int						i_b;
	char					*new_b;
	char					*tmp_b;
	char					*tmp1_b;
	int						c_b;
	char					*str_b;
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

typedef struct				s_process
{
	struct s_process		*next;
	char					**file_args;
	pid_t					pid;
	char					completed;
	char					stopped;
	int						status;
	char					**file_opt;
	int						foreground;
}							t_process;

typedef struct				s_job
{
	struct s_job			*next;
	char					*command;
	t_process				*first_process;
	pid_t					pgid;
	char					notified;
	struct termios			tmodes;
	int						stdinc;
	int						stdoutc;
	int						stderrc;
	int						foreground;
}							t_job;

typedef struct				s_all_global_variables
{
	int					g_exit_code;
	pid_t				g_shell_pgid;
	int					g_shell_terminal;
	int					g_shell_is_interactive;
	char				**g_env;
	char				*g_cp;
	int					g_his_d;
	char				**g_alias;
	char				**g_all_var;
	t_memory			*g_memory_head;
	const char	*g_builtins[BIL_NUM];
	t_job				*g_f_job;

}							t_all_global_variables;

#endif
