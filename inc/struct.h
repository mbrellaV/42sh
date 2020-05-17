/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:33:44 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define BIL_NUM			21

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
	int						flag_tab;
	int						flag_left_word;
	int						i_dop;
	char					c;
}							t_readline;

typedef	struct				s_builtins
{
	int						cd_p;
	int						link;
	int						echo_n;
	int						echo_c;
}							t_builtins;

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

typedef	struct				s_stack
{
	unsigned int			index;
	unsigned int			capacity;
	char					array[1000];
}							t_stack;

#endif
