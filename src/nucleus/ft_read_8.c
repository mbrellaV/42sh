/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:15:41 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/29 17:15:43 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_do_leftright(t_flag **flag, int len, int sum)
{
	if (sum == 186 && (*flag)->i > 0)
	{
		write(2, "\b", 1);
		(*flag)->i--;
	}
	else if (sum == 185 && (*flag)->i < (*flag)->max)
	{
		if (ft_put_n(len, (*flag)->i + 1, (*flag)->max) == -1)
			tputs(tgetstr("nd", NULL), 1, ft_c);
		(*flag)->i++;
	}
}

char	*ft_do_addch(t_flag *flag, char *input, char buf, int *len)
{
	char	*tmp;

	tmp = input;
	input = ft_strjoinch_i(tmp, buf, flag->i, flag->max + 1);
	free(tmp);
	flag->i++;
	flag->max = ft_strlen(input);
	ft_cleanstr(flag->i + 1 + *len);
	*len = ft_main_norm(flag->mod);
	ft_putstr_fd(input, 2);
	ft_setcursor(flag->i, flag->max);
	return (input);
}

int		ft_add_sumchar(char *str, int rt)
{
	int i;
	int sum;

	i = -1;
	sum = 0;
	while (++i < rt)
	{
		sum += str[i];
	}
	return (sum);
}

void	ft_do_moving(t_flag *flag, char **input, t_memory **mem, int len)
{
	flag->sum == 186 || flag->sum == 185 ? ft_do_leftright(&flag,
		len, flag->sum) : NULL;
	flag->sum == 183 || flag->sum == 184 ? ft_putmemory(&mem, flag->sum,
		&input, &flag) : NULL;
	flag->sum == 341 ? ft_upcursor(&flag) : NULL;
	flag->sum == 342 ? ft_downcursor(&flag, len) : NULL;
	flag->sum == 297 || flag->sum == 298 || flag->sum == 190 ||
		flag->sum == 188 ? ft_arrows(&flag, len, flag->sum, *input) : NULL;
}

char	*ft_read_8(int len, t_memory *head, int mod)
{
	char		*input;
	t_flag		f;
	char		buf[8];
	t_memory	*mem;

	input = ft_strnew(1);
	mem = head;
	f = (t_flag){0, 0, 0, 0, 0, mod};
	while ((f.rt = read(0, buf, 8)) && buf[0] != '\n')
	{
		if ((f.sum = ft_add_sumchar(buf, f.rt)) && f.rt > 1)
			ft_do_moving(&f, &input, &mem, len);
		else
		{
			if (f.sum == 25 || f.sum == 23 || f.sum == 21 || f.sum == 127)
				input = ft_cut_copy(input, &f, &len, f.sum);
			else if (ft_signal(f.sum, &input) == 1)
				return (input);
			else if (f.sum == 27 || (f.sum == 119 && f.a == 1))
				ft_do_copy(input, &f);
			else if (ft_signal(f.sum, &input) == 404)
				input = ft_do_addch(&f, input, buf[0], &len);
		}
	}
	return (input);
}
