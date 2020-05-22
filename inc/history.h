/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 23:44:44 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 23:45:08 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "struct.h"
# include "../libft/inc/libft.h"
# include <unistd.h>
# include "nucleus.h"

typedef struct				s_memory
{
	char					*inp;
	struct s_memory			*back;
	struct s_memory			*next;
}							t_memory;

/*
** change_hist_exp.c
*/

char						*history_error(char *dopline);
void						zm_history_numbers(int i, char **str1,
												char type, t_memory *q);
void						zm_history_name(int i, char **str1, char type,
												t_memory *q);
char						*do_zam_cycle(char *str1, t_memory *q, int i);
char						*do_zam_str_hist_var(char *str1, t_memory *q);

/*
** dop_memory.c
*/

t_memory					*make_memmory_with_one_node(int fd, char *buf);

/*
** find_history.c
*/

void						find_history(t_readline *p, t_memory *q);

/*
** ft_add_to_history.c
*/

t_memory					*ft_add_to_history(t_memory *back, char **str);

/*
** ft_putmemory.c
*/

void						ft_putmemory(t_memory **q, t_readline *p);

/*
** init_history.c
*/

t_memory					*ft_head_memory(void);

/*
** save_hist.c
*/

int							save_history(t_memory *q);

/*
** show_history.c
*/

int							show_history(t_memory *q);

/*
** history_search.c
*/

char						*get_num_from_hist_begin(t_memory *t, int num);
char						*get_num_from_hist_end(t_memory *t, int num);
char						*get_num_from_hist_starting(t_memory *t,
														char *name);
char						*get_num_from_hist_cons(t_memory *t, char *name);

/*
** open_hist_file.c
*/

int			open_hist_file(int type);

#endif
