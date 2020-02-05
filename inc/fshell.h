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

char			**g_env;
char			*g_cp;
int				g_his_d;

void			ft_realloc_all(int k, char ***envl);
void			ft_echo(char **str);
char			*ft_slash(char *str);
char			*ft_hex(char *str);
int				set_new_var(char *str1, char *str2, char ***envl);
void			ft_cd(char **str);
char			*ft_get_var(char *dop, char **env);
int				issc(char c);
void			ft_global_env(char **env, int argc);
int				unset_var(char *str, char ***envl);
void			ft_fun_fork(char *path, char **arg, pid_t pid);
int				ft_findenv(char *s, char **env);
void			ft_do_export(char **mas);
void			ft_global_dir(int flag, char *str);
char			*ft_cd_home(char *str);
int				ft_main_norm(int flag);
int				ft_signal(int signo, t_readline *p);
void			ft_fork_signal(int signo);
int				ft_main_what(t_exectoken *tmp, t_memory *q);
void			ft_whatis(t_exectoken *tmp, t_memory *q);
void			ft_infinit_pipe(t_exectoken *head);
int				ft_distruct_tree(t_exectoken *q);
int				ft_distr_lex(t_lextoken	*tmp);
int				ft_distruct_memory(t_memory	*head);
void			ft_error_q(int er);
int				ft_norm_pipe(int p1, int *fd_in, int p0, t_exectoken **head);
int				ft_error_args(t_exectoken *tmp);
void			ft_file_create(t_exectoken *head);
int				ft_what_flag(char *str, int *b);
void			ft_open_flag(char *str, int *flag, int **ff, int *fd);
int				ft_put_info(void);
int				ft_env_len(char **env);
void			ft_show_env(char **env);
void			do_zam_str_with_tilda(char **mas);
int				check_file(char *file, unsigned check);
int				is_cmp(char *s1, char *s2);
int				is_add_str_tab(t_readline *p);
void			ft_add_tab(t_readline *p, char *str);
void			ft_find_dir(char *dir, char *name, t_readline *p);
char			*ft_directory(char *str, int *flag_dir);
char			*ft_name(char *str);
void			ft_find_path(t_readline *p, char *name);
int				save_history(t_memory *q);
void			do_count_shell_lvl(void);

#endif
