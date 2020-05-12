/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:58:44 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/12 17:28:01 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSHELL_H
# define FSHELL_H

# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "../libft/inc/libft.h"
# include <signal.h>
# include "pwd.h"
# include "grp.h"
# include <sys/stat.h>
# include <sys/types.h>
# include "time.h"
# include <sys/wait.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <termcap.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <errno.h>
# include "parser.h"
# include "hash.h"
# include "calc.h"
# include "history.h"
# include "nucleus.h"
# include "lexer.h"
# include "struct.h"
#include "exec.h"
# include "../src/qft_printf/ft_printf.h"

# define RED		"\x1B[31m"
# define GRN		"\x1B[32m"
# define YEL		"\x1B[33m"
# define BLU		"\x1B[34m"
# define MAG		"\x1B[35m"
# define CYN		"\x1B[36m"
# define WHT		"\x1B[37m"
# define RESET		"\x1B[0m"

# define IS_E		0
# define IS_R		1
# define IS_W		2
# define IS_X		4
# define IS_D		8
# define IS_L		16

# define FC_VIM		2
# define FC_EMACS	4
# define FC_NANO	8

# define SHELL_NAME	"42sh"

# define FC_US "42sh: fc: error!\nusing: fc -[eslr] [editor] [range | number]\n"
# define SY_E_1	"42sh: Syntax error: newline unexpected (expecting \")\")\n"
# define SY_E_2	"42sh: Syntax error: \")\" unexpected\n"

typedef struct		s_fc
{
	int				l;
	int				r;
	int				hi_s;
	int				silent;
	int				editor;
	int				rng[3];
}					t_fc;

typedef struct		s_global
{
	t_hash			*g_hash[MAX_HASH];
	pid_t			g_shell_pgid;
	int				g_shell_terminal;
	int				g_shell_is_interactive;
	char			**g_env;
	char			*g_cp;
	int				g_his_d;
	char			**g_alias;
	char			**g_all_var;
	t_memory		*g_memory_head;
	t_job			*g_f_job;
	int				*fd;
	char			**g_builtins;
	char			**g_first_env;
}					t_global;

typedef struct		s_del
{
	t_job			*j;
	t_job			*jlast;
	t_job			*jnext;
	t_job			*jdop;
	int				d;
}					t_del;

typedef struct		s_zams
{
	int				i;
	int				dop;
	char			*dopstr;
	char			*str_for_del;
}					t_zams;

typedef struct		s_pstat
{
	t_job			*j;
	t_process		*p;
	t_process		*ptmp;
	int				job_count;
	char			*str_for_del;
}					t_pstat;

t_global			*globals(void);
int					is_builtin(char *str);
void				ft_alias();
int					check_flag(char **av, t_fc *f);
int					calc_h_size();
char				*read_fc(int fd);
int					check_flag_2(int *i, char **av, t_fc *f);
t_lextoken			*do_zam_join_par(t_lextoken *h);
int					ft_do_zam_alias(char **str);
int					ft_do_change_alias(char **mas);
char				*do_obr_zamena(char *line);
void				ft_realloc_all(int k, char ***envl);
void				ft_echo(char **str);
t_memory			*make_memmory_with_one_node(int fd, char *buf);
char				*get_hist_by_id(int id);
char				*ft_slash(char *str, t_builtins *echo);
void				del_one_node(t_lextoken *token_to_del,
						t_lextoken **first_token);
char				*distribute_echo(char **str, int k, int flag,
						t_builtins *echo);
char				*ft_hex(char *str);
void				delete_fc_command(void);
void				*ft_malloc(size_t size);
int					launch(char *str, int put_name);
int					set_new_var(char *str1, char *str2, char ***envl);
int					ft_cd(char **str);
void				do_all_var(char **env);
int					do_cd(t_builtins *cd, char *str);
int					do_fc(char **av);
int					do_authors(void);
char				*get_pwd(t_builtins *cd);
char				*get_oldpwd(t_builtins *cd);
int					ft_cd_error(char *tmp, int err, int to_free);
int					change_path(char *path, t_builtins *cd);
char				*create_full_path(char *path, t_builtins *cd);
char				*ft_strjoin_cd(char const *s1, char const *s2, int to_free);
char				*ft_get_var(char *dop, char **env);
int					issc(char c);
char				init_shell_builtins();
t_lextoken			*do_zam_ravno(t_lextoken *h, t_lextoken **first_token);
void				ft_global_env(char **env, int argc);
int					unset_var(char *str, char ***envl);
void				ft_fun_fork(char *path, char **arg, pid_t pgid,
						int foreground);
int					ft_findenv(char *s, char **env);
void				ft_do_export(char **mas);
void				ft_free_split(char **split);
int					ft_signal(int signo, t_readline *p);
void				ft_fork_signal(int signo);
int					ft_main_what(t_exectoken *tmp);
int					ft_distruct_tree(t_exectoken *q);
int					ft_distr_lex(t_lextoken	*tmp);
int					ft_distruct_memory(t_memory	*head);
void				ft_error_q(int er);
int					ft_ck_addline(t_readline *p);
int					ft_what_flag(char *opt);
int					calc_h_size();
int					ft_put_info(void);
int					ft_env_len(char **env);
char				*do_reverse_zamena(char *str);
int					strdelr(char **str);
void				ft_show_env(char **env);
char				*do_zam_str_with_tilda(char *str);
int					check_file(char *file, unsigned check);
int					is_cmp(char *s1, char *s2);
int					is_add_str_tab(t_readline *p);
void				ft_add_tab(t_readline *p, char *str);
void				ft_find_dir(char *dir, char *name, t_readline *p);
char				*ft_directory(char *str, int *flag_tab);
char				*ft_name(char *str, t_readline *p);
int					ft_type(char **argv);
void				ft_find_path(t_readline *p, char *name);
void				ft_find_env(char *name, t_readline *p);
void				ft_add_builtins_in_tab(char *name, t_readline *p);
int					save_history(t_memory *q);
void				do_count_shell_lvl(void);
char				*ft_do_zam_eval(char *mas);
int					sc_size(char *str, char b);
char				find_pair_sc(char c);
int					check_bracket(char *str);
int					set_redirects_for_builtins(char **av);
int					ft_open_flag_in_builtins(char *opt, int flag, int *infile,
						int *outfile);
t_job				*get_job_by_number(int n);
int					do_fg(char **mas);
int					check_if_in_par(char *line, int i);
int					do_bg(char **mas);
int					return_with_close(int *opened_fds, int int_to_return,
						char *dopline, int marker);
int					ft_heredoc(char *tmp);
int					ft_open_flag(char *opt, t_pipe *p);
int					ft_what_flag(char *opt);
void				ft_redirect_error(int marker, char *dopline);
int					ft_fd_flag(char **av, int infile, int outfile,
						int errfile);
void				put_job_in_foreground (t_job *j, int cont);
void				put_job_in_background (t_job *j, int cont);
int					mark_process_status(pid_t pid, int status, t_job *job);
void				update_status (void);
void				wait_for_job (t_job *j);
t_job				*create_job(t_exectoken *head);
void				format_job_info (t_job *j, const char *status, int num);
int					check_file_args(t_process *tmp);
void				dop_to_check_tab(t_readline *p, char **str, int *i);
void				dop_to_check_tab_delete(t_readline *p,
						char **name, char **str, char **dir);
void				do_job_notification (void);
void				continue_job (t_job *j, int foreground);
void				mark_job_as_running (t_job *j);
int					job_is_stopped (t_job *j);
int					job_is_completed (t_job *j);
int					ft_find_in_fds(int *opened_fds, int fd_to_find);
int					ft_add_to_fds(int *opened_fds, int fd_to_add);
int					ft_remove_from_fds(int *opened_fds, int fd_to_remove);
int					*ft_create_opened_fds();
void				disable_shell_signals();
void				recover_normal_shell_signals();
int					ft_whatis2(t_process *tmp);
void				init_shell(void);
int					do_builtin(char **file_args, char **file_opt, int type);
int					ck_br(const char *str);
void				put_error_to_shell(int error);
char				*ft_do_zam_eval(char *mas);
uint_least32_t		crc_32(unsigned char *buf, size_t len);
int					ft_error(int error, char *dopline);
int					alias_error(int error, char *tmp1, char *tmp2);
int					ft_error_d(t_readline *p);
char				*ft_get_prev_word(char *str, int i);
int					exit_builtin(char **args);
int					is_first_word(char *str, int i);


#endif
