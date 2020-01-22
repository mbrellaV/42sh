/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nucleus.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:27:41 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/25 17:27:43 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUCLEUS_H
# define NUCLEUS_H

struct termios		saved_attributes;

typedef struct		s_flag
{
	int				i;
	int				max;
	int				rt;
	int				sum;
	int				a;
	int				mod;
}					t_flag;

typedef struct		s_memory
{
	char			*inp;
	struct s_memory	*back;
	struct s_memory *next;
}					t_memory;

int					ft_c(int c);
void				reset_input_mode(void);
void				set_input_mode(void);
int					ft_put_n(int len, int i, int max);
t_memory			*ft_memory(t_memory *back, char **str);
void				ft_cleanstr(int i);
void				ft_putmemory(t_memory ***q, int sum,
					char ***input, t_flag **flag);
void				ft_setcursor(int i, int max);
char				*ft_strdelch(char *str, int i, int max);
void				ft_back_slovo(char *input, t_flag ***flag);
void				ft_next_slovo(char *input, t_flag ***flag, int len);
void				ft_upcursor(t_flag **flag);
void				ft_downcursor(t_flag **flag, int len);
int					show_history(t_memory *q);
char				*ft_read_8(int len, t_memory *head, int mod);
t_memory			*ft_head_memory(void);
void				set_input_mode_t(void);
void				ft_cut(char **input, t_flag **flag, int **len);
void				ft_putcut(char **input, t_flag **flag, int **len);
char				*ft_cut_copy(char *input, t_flag *flag,
					int *len, int buf);
void				ft_do_copy(char *input, t_flag *flag);
void				ft_arrows(t_flag **flag, int len, int sum, char *input);

#endif
