/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 23:38:12 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/03 20:13:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <termcap.h>
# include <termios.h>
# include "parser.h"

typedef struct			s_process
{
	struct s_process	*next;
	char				**file_args;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					status;
	char				**file_opt;
	int					*inhibitor_args;
}						t_process;

typedef struct			s_job
{
	struct s_job		*next;
	char				*command;
	t_process			*first_process;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	int					stdinc;
	int					stdoutc;
	int					stderrc;
	int					foreground;
}						t_job;

typedef struct			s_jobl
{
	t_process			*p;
	pid_t				pid;
	char				*rt;
	int					mypipe[2];
	int					sempipe[2];
	int					infile;
	int					outfile;
}						t_jobl;

/*
** continuing_jobs.c
*/

void					continue_job(t_job *j, int foreground);
void					make_job_completed(t_job *job);

/*
** create_jobs_and_proc.c
*/

t_job					*create_job(t_exectoken *head);

/*
** find_jobs.c
*/

t_job					*get_job_by_number(int n);
t_job					*get_last_job(void);
t_job					*get_prev_last_job(void);
t_job					*get_job_by_start_str(char *str);
t_job					*get_job_by_cont_str(char *str);

/*
** free_job_list.c
*/

int						do_job_del(void);

/*
** ft_create_file.c
*/

int						check_file_args(t_process *tmp);
void					ft_open_f(char *str, int *flag, int *fd);

/*
** ft_do_open_flags.c
*/

int						ft_what_flag(char *opt);
int						ft_open_flag(char *opt, t_pipe *p);
int						ft_heredoc(char *tmp);
void					ft_redirect_one(int old_file_fd, int new_infile_fd);

/*
** ft_do_redirects.c
*/

void					do_heredoc(t_pipe *p, char **av);
int						do_simple_redirects(t_pipe *p, int *opened_fds,
								char **av, int type);
int						do_hard_redirects(t_pipe *p, int *opened_fds,
										char **av);
int						ft_fd_flag(char **av, int infile, int outfile,
									int errfile);

/*
** ft_redirect_error.c
*/

void					ft_redirect_error(int marker, char *dopline);

/*
** job_info.c
*/

int						format_job_info(t_job *j, const char *status, int num);
int						do_job_notification(void);

/*
** launch_job.c
*/

int						launch_job(t_job *j, int foreground);

/*
** launch_process.c
*/

void					standart_redirect(int infile, int outfile, int errfile);
int						launch_process(t_process *p, t_job *j,
		t_jobl *jobl, int fg);

/*
** operating_jobs.c
*/

t_job					*find_job(pid_t pgid);
int						job_is_stopped(t_job *j);
int						job_is_completed(t_job *j);
int						num_of_the_job(t_job *j);

/*
** put_job_in_background.c
*/

void					put_job_in_background(t_job *j, int cont);

/*
** put_job_in_foreground.c
*/

void					put_job_in_foreground(t_job *j, int cont);

/*
** redirect.c
*/

void					ft_redirect(t_pipe *p, int new_infile_fd,
									int new_outfile_fd);
void					do_redir_into_file(t_pipe *p, char *file,
									int new_infile_fd, int new_outfile_fd);
int						return_with_close(int *opened_fds, int int_to_return,
										char *dopline, int marker);

/*
** stopped_and_terminated_jobs.c
*/

int						mark_process_status(pid_t pid, int status, t_job *job);
void					update_status(void);
void					wait_for_job(t_job *j);

/*
** working_with_fds.c
*/

int						ft_find_in_fds(int *opened_fds, int fd_to_find);
int						ft_add_to_fds(int *opened_fds, int fd_to_add);
int						ft_remove_from_fds(int *opened_fds, int fd_to_remove);
int						*ft_create_opened_fds(void);

#endif
