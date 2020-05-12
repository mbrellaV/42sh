/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nucleus.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:27:41 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 23:47:38 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUCLEUS_H
# define NUCLEUS_H

# include "history.h"

struct termios		saved_attributes;

typedef	struct				s_nline
{
	int						*i_arr;
	char					**arr;
	int						i;
	int						j;
	int						k;
}							t_nline;

/*
** del_readline.c
*/

int							del_readline(t_readline *p);

/*
** do_add.c
*/

void						ft_do_addstr(t_readline *p, char *str);
void						ft_do_addch(t_readline *p, char c);

/*
** dop_tab_funs.c
*/

void						ft_add_builtins_in_tab(char *name, t_readline *p);
void						ft_find_path(t_readline *p, char *name);
int							is_cmp(char *s1, char *s2);
char						*ft_name(char *str, t_readline *p);

/*
** ft_add_input_que.c
*/

void						ft_add_intput_que(t_readline *p,
							t_memory *head, int mod);

/*
** ft_add_sumchar.c
*/

int							ft_add_sumchar(char *str, int rt);

/*
** ft_arrdel.c
*/

void						ft_arrdel(char **arr);

/*
** ft_arrnew.c
*/

char						**ft_arrnew(size_t size);

/*
** ft_arrows.c
*/

void						ft_arrows(t_readline *p);

/*
** ft_back_slovo.c
*/

void						ft_back_slovo(t_readline *p);

/*
** ft_c.c
*/

int							ft_c(int c);

/*
** ft_check_quote.c
*/

char						ft_cheak_quote_c(char *input);
int							ft_cheak_quote(char *input);

/*
** ft_cheak_tab.c
*/

void						ft_check_tab_addstr(t_readline *p, int i);
void						ft_cheak_tab(t_readline *p);

/*
** ft_cleanstr.c
*/

void						ft_cleanstr(int i, t_readline *p);

/*
** ft_cut.c
*/

void						ft_cut(t_readline *p);

/*
** ft_cut_copy.c
*/

void						ft_cut_copy(t_readline *p);

/*
** ft_directory.c
*/

void						ft_find_dir(char *dir, char *name, t_readline *p);
char						*ft_directory(char *str, int *flag_tab);

/*
** ft_do_copy.c
*/

void						ft_do_copy(t_readline *p);

/*
** ft_do_delch.c
*/

void						ft_do_delch(t_readline *p);

/*
** ft_leftright.c
*/

void						do_up_ifn(t_nline *l, t_readline *p);
void						do_up_if_izero(t_readline *p);
void						do_down_if_iwscol(t_readline *p);
void						do_left(t_readline *p);
void						do_right(t_readline *p);
void						ft_do_leftright(t_readline *p);

/*
** ft_downcursor.c
*/

void						ft_downcursor(t_readline *p);

/*
** ft_find_env.c
*/

void						add_dopstr(char *goodstr, t_readline *p);
void						ft_find_env(char *name, t_readline *p);

/*
** ft_next_slovo.c
*/

void						ft_next_slovo(t_readline *p);

/*
** ft_print_tab.c
*/

void						ft_print_tab(t_readline *p);

/*
** ft_printf_helper.c
*/

int							ft_printf_helper(int flag);

/*
** ft_put_n.c
*/

int							ft_put_n(int len, int i, int max);

/*
** ft_putcut.c
*/

void						ft_putcut(t_readline *p);

/*
** ft_read_8.c
*/

void						ft_cheak_sum(t_readline *p, t_memory **h);
void						ft_add_his(t_readline *p, t_memory *h);
void						do_hist_add_with_slash_n(int mod, t_readline *p);
void						ft_read_8(t_readline *p, t_memory *head, int mod);

/*
** ft_realloc_buff.c
*/

void						ft_realloc_buff(t_readline *p);

/*
** ft_realloc_tab.c
*/

void						ft_realloc_tab(t_readline *p);

/*
** ft_setcursor.c
*/

void						ft_setcursor(int i, int max, t_readline *p);

/*
** ft_start_read.c
*/

void						ft_start_read(t_readline *p);

/*
** ft_strsplit1.c
*/

char						**ft_strsplit1(char const *s, char c);

/*
** ft_upcursor.c
*/

void						ft_upcursor(t_readline *p);

/*
** input_mode.c
*/

void						reset_input_mode(void);
void						error_term(int error);
int							set_input_mode(void);
int							ft_read_helper(t_readline *p,
						t_memory **h, int rt, char *buf);

/*
** nline.c
*/

void						init_nline(t_readline *p,
										t_nline *l);

/*
** tab.c
*/

void						ft_add_tab(t_readline *p, char *str);
int							is_add_str_tab(t_readline *p);
void						dop_to_check_tab(t_readline *p, char **str, int *i);
void						dop_to_check_tab_delete(t_readline *p,
							char **name, char **str, char **dir);

#endif
