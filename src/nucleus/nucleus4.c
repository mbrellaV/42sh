/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nucleus4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:21:39 by qmartina          #+#    #+#             */
/*   Updated: 2019/12/11 16:21:40 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_arrows(t_flag **flag, int len, int sum, char *input)
{
	if (sum == 297)
	{
		while ((*flag)->i-- > 0)
			write(2, "\b", 1);
		(*flag)->i = 0;
	}
	else if (sum == 298)
	{
		while (++(*flag)->i <= (*flag)->max)
		{
			if (ft_put_n(len, (*flag)->i, (*flag)->max) == -1)
				tputs(tgetstr("nd", NULL), 1, ft_c);
		}
		(*flag)->i--;
	}
	else if (sum == 190)
		ft_back_slovo(input, &flag);
	else if (sum == 188)
		ft_next_slovo(input, &flag, len);
}

int		show_history(t_memory *q)
{
	t_memory	*tmp;
	int			i;
	int			sum;
	t_memory	*dop;

	i = 0;
	sum = 0;
	tmp = q;
	//ft_printf("sasd0");
	while (tmp->back)
		tmp = tmp->back;
	dop = tmp;
	//ft_printf("sasd1");
	while (tmp != NULL)
	{
		ft_printf("ebl\n");
		sum++;
		tmp = tmp->next;
	}
	tmp = dop;
//	ft_printf("sasd2");
	while (tmp)
	{
		//ft_printf("%d\t%s\n", i, tmp->inp);
		if (sum - i < 16)
			ft_printf("%d\t%s\n", i, tmp->inp);
		tmp = tmp->next;
		i++;
	}
	return (1);
}

void	ft_cleanstr(int i)
{
	while (i > 0)
	{
		write(2, "\b", 1);
		i--;
	}
	tputs(tgetstr("cd", NULL), 1, ft_c);
}
