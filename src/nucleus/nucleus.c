/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nucleus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:29:27 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/25 17:29:29 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char	*ft_strdelch(char *str, int i, int max)
{
	char	*new;
	int		k;

	k = -1;
	new = (char *)malloc(sizeof(char) * max);
	while (++k < i)
		new[k] = str[k];
	while (str[k + 1])
	{
		new[k] = str[k + 1];
		k++;
	}
	new[k] = '\0';
	return (new);
}

void	ft_back_slovo(char *input, t_flag ***flag)
{
	if (input[(**flag)->i] == ' ')
	{
		(**flag)->i--;
		write(2, "\b", 1);
	}
	while ((**flag)->i > 0 && input[(**flag)->i] == ' ')
	{
		(**flag)->i--;
		write(2, "\b", 1);
	}
	while ((**flag)->i > 0 && input[(**flag)->i] != ' ')
	{
		(**flag)->i--;
		write(2, "\b", 1);
	}
	while ((**flag)->i > 0 && input[(**flag)->i] == ' ')
	{
		(**flag)->i--;
		write(2, "\b", 1);
	}
	if ((**flag)->i != 0)
	{
		tputs(tgetstr("nd", NULL), 1, ft_c);
		(**flag)->i++;
	}
}

void	ft_next_slovo(char *input, t_flag ***flag, int len)
{
	if (input[(**flag)->i] == ' ')
	{
		(**flag)->i++;
		if (ft_put_n(len, (**flag)->i, (**flag)->max) == -1)
			tputs(tgetstr("nd", NULL), 1, ft_c);
	}
	while (input[(**flag)->i] == ' ' && (**flag)->i < (**flag)->max)
	{
		(**flag)->i++;
		if (ft_put_n(len, (**flag)->i, (**flag)->max) == -1)
			tputs(tgetstr("nd", NULL), 1, ft_c);
	}
	while (input[(**flag)->i] != ' ' && (**flag)->i < (**flag)->max)
	{
		(**flag)->i++;
		if (ft_put_n(len, (**flag)->i, (**flag)->max) == -1)
			tputs(tgetstr("nd", NULL), 1, ft_c);
	}
}

void	ft_upcursor(t_flag **flag)
{
	struct winsize	wins;
	int				i;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	if ((*flag)->i <= wins.ws_col)
	{
		while ((*flag)->i-- > 0)
			write(2, "\b", 1);
		(*flag)->i = 0;
	}
	else
	{
		i = (*flag)->i - wins.ws_col;
		while ((*flag)->i-- > i)
			write(2, "\b", 1);
		(*flag)->i++;
	}
}

void	ft_downcursor(t_flag **flag, int len)
{
	struct winsize	wins;
	int				i;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	if (((*flag)->max - (*flag)->i) > wins.ws_col)
	{
		i = -1;
		while (++i < wins.ws_col)
		{
			if (ft_put_n(len, (*flag)->i + 1, (*flag)->max) == -1)
				tputs(tgetstr("nd", NULL), 1, ft_c);
			(*flag)->i++;
		}
	}
	else
	{
		while ((*flag)->i < (*flag)->max)
		{
			if (ft_put_n(len, (*flag)->i + 1, (*flag)->max) == -1)
				tputs(tgetstr("nd", NULL), 1, ft_c);
			(*flag)->i++;
		}
	}
}
