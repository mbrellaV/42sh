/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:54:23 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int				check_open(char **str, int i, int j)
{
	if ((j == 0 && i == 0) || (j == 0 && (str[i - 1][ft_strlen(str[i - 1]) - 1]
	== ';' || str[i - 1][ft_strlen(str[i - 1]) - 1] == '|' ||
	str[i - 1][ft_strlen(str[i - 1]) - 1] == '(')))
		return (1);
	if (str[i][j - 1] == ';' || str[i][j - 1] == '|' || str[i][j - 1] ==
	'(' || str[i][j - 1] == '$' || (str[i][j - 1] > 41 && str[i][j - 1] < 58))
		return (1);
	return (-1);
}

int				check_close(char **str, int i, int j)
{
	if (j == 0 && i != 0 && (str[i - 1][ft_strlen(str[i - 1]) - 1] == '<' ||
	str[i - 1][ft_strlen(str[i - 1]) - 1] == '|' || str[i - 1][ft_strlen(str[i -
	1]) - 1] == '>' || str[i - 1][ft_strlen(str[i - 1]) - 1] == '('))
		return (-1);
	if (j != ft_strlen(str[i]) - 1 && str[i][j + 1] != ';' && str[i][j + 1] !=
	'|' && str[i][j + 1] != ')' && str[i][j + 1] != '$' && str[i][j + 1] < 42
	&& str[i][j + 1] > 57)
		return (-1);
	return (1);
}

static int		cycle(int i, int j, char **spl)
{
	static int	flag = 0;

	if (spl[i][j] == '(')
	{
		flag++;
		if (check_open(spl, i, j) == -1)
		{
			ft_free_str(spl);
			return (-1);
		}
	}
	else if (spl[i][j] == ')')
	{
		if (flag == 0 || check_close(spl, i, j) == -1)
		{
			ft_free_str(spl);
			return (-2);
		}
		flag--;
	}
	return (0);
}

int				check_bracket(char *str)
{
	int			i;
	int			j;
	int			ret;
	char		**spl;

	i = -1;
	spl = ft_strsplit(str, " \t");
	while (spl && spl[++i])
	{
		j = -1;
		while (spl[i] && spl[i][++j])
			if ((ret = cycle(i, j, spl)))
				return (ret);
	}
	ft_free_str(spl);
	return (1);
}
