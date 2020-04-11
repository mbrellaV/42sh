/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:58:44 by mbrella           #+#    #+#             */
/*   Updated: 2020/01/28 14:58:57 by mbrella          ###   ########.fr       */
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
# include "../libft/libft.h"
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
# include "parser.h"
# include "nucleus.h"
# include "struct.h"
# include "hash.h"
# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define RESET	"\x1B[0m"

# define IS_E	0
# define IS_R	1
# define IS_W	2
# define IS_X	4
# define IS_D	8
# define IS_L	16

# define SHELL_NAME "42sh"
# define BIL_NUM 16

int					g_exit_code;
pid_t				g_shell_pgid;
struct termios		shell_tmodes;
int					g_shell_terminal;
int					g_shell_is_interactive;
char				**g_env;
char				*g_cp;
int					g_his_d;
char				**g_alias;
char				**g_all_var;
t_memory			*g_memory_head;
extern const char	*g_builtins[BIL_NUM];
t_job				*g_f_job;

int					is_builtin(char *str);
void				ft_alias();
t_lextoken			*do_zam_join_par(t_lextoken *h);
char				*ft_do_zam_alias(char *str);
int					ft_do_change_alias(char **mas);
char				*do_obr_zamena(char *line);
void				ft_realloc_all(int k, char ***envl);
void				ft_echo(char **str);
char				*ft_slash(char *str, t_builtins *echo);
char				*distribute_echo(char **str, int k, int flag,
						t_builtins *echo);
char				*ft_hex(char *str);
int					set_new_var(char *str1, char *str2, char ***envl);
int					ft_cd(char **str);
void				do_all_var(char **env);
int					do_cd(t_builtins *cd, char *str);
t_job				*get_last_job();
char				*get_pwd(t_builtins *cd);
char				*get_oldpwd(t_builtins *cd);
int					ft_cd_error(char *tmp, int err, int to_free);
int					change_path(char *path, t_builtins *cd);
char				*create_full_path(char *path, t_builtins *cd);
char				*ft_strjoin_cd(char const *s1, char const *s2, int to_free);
char				*ft_get_var(char *dop, char **env);
int					issc(char c);
t_lextoken			*do_zam_ravno(t_lextoken *h, t_lextoken **htmp);
void				ft_global_env(char **env, int argc);
int					unset_var(char *str, char ***envl);
void				ft_fun_fork(char *path, char **arg, pid_t pgid,
						int foreground);
int					ft_findenv(char *s, char **env);
void				ft_do_export(char **mas);
int					ft_signal(int signo, t_readline *p);
void				ft_fork_signal(int signo);
int					ft_main_what(t_exectoken *tmp);
void				change_enters_in_sc(char *line);
void				ft_whatis(t_exectoken *tmp, t_memory *q);
void				ft_infinit_pipe(t_exectoken *head);
int					ft_distruct_tree(t_exectoken *q);
int					ft_distr_lex(t_lextoken	*tmp);
int					ft_distruct_memory(t_memory	*head);
void				ft_error_q(int er);
int					ft_norm_pipe(int p1, int *fd_in, int p0,
						t_exectoken **head);
int					ft_error_args(t_exectoken *tmp);
void				ft_file_create(t_exectoken *head);
int					ft_what_flag(char *opt);
int					ft_put_info(void);
int					ft_env_len(char **env);
char				*do_reverse_zamena(char *str);
void				ft_show_env(char **env);
char				*do_zam_str_with_tilda(char *str);
int					check_file(char *file, unsigned check);
int					is_cmp(char *s1, char *s2);
int					is_add_str_tab(t_readline *p);
void				ft_add_tab(t_readline *p, char *str);
void				ft_find_dir(char *dir, char *name, t_readline *p);
char				*ft_directory(char *str, int *flag_dir);
char				*ft_name(char *str);
void				ft_type(char **argv);
void				ft_find_path(t_readline *p, char *name);
int					save_history(t_memory *q);
void				do_count_shell_lvl(void);
char				*ft_do_zam_eval(char *mas);
int					sc_size(char *str, char b);
char				find_pair_sc(char c);
int					check_bracket(char *str);
void				do_obr_zamena_slash(t_exectoken *tmp);
void				ft_redirect(t_pipe *p, int new_infile_fd,
						int new_outfile_fd);

t_job				*get_job_by_number(int n);
int					do_fg(char **mas);
int					do_bg(char **mas);
int					launch_process(t_process *p, pid_t pgid,
						int infile, int outfile, int errfile,
						int foreground, char *rt);
int					launch_job(t_job *j, int foreground);
int					needs_something_before(int n);
int					do_job_del();

void				ft_change_all_sc(char *str);
void				do_zamena_opt_tokens(t_exectoken *tmp);
int					check_all_errors(t_lextoken *tmp);
int					ft_fd_flag(char **av, int *infile, int *outfile,
						int *errfile);
void				put_job_in_foreground (t_job *j, int cont);
void				put_job_in_background (t_job *j, int cont);
int					mark_process_status (pid_t pid, int status);
void				update_status (void);
void				wait_for_job (t_job *j);
void				format_job_info (t_job *j, const char *status, int num);
void				do_job_notification (void);
void				continue_job (t_job *j, int foreground);
void				mark_job_as_running (t_job *j);
t_job				*find_job (pid_t pgid);
int					job_is_stopped (t_job *j);
int					job_is_completed (t_job *j);
int					ft_distruct_job(t_job *head);

void				ft_infinit_pipe2(t_exectoken *head, t_memory *q);
int					ft_whatis2(t_process *tmp);
int					ft_whatis4(t_exectoken *tmp);
void				init_shell(void);
t_job				*create_job(t_exectoken *head);

#endif
