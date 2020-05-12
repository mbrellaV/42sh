/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_hist_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:12:00 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/12 15:40:48 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

char				*history_error(char *dopline)
{
	put_error_to_shell(2);
	ft_dprintf(globals()->fd[2], "42sh: %s: event not found\n", dopline);
	ft_strdel(&dopline);
	return (NULL);
}

void				zm_history_numbers(int i, char **str1,
		char type, t_memory *q)
{
	int		c;
	char	*tmp;
	char	*str;

	str = *str1;
	c = i + type;
	while (isword(str[c]) != 0 && str[c])
		c++;
	if (type == 0)
		tmp = get_num_from_hist_begin(q, ft_atoi(str + i + 1));
	if (type == 2)
		tmp = get_num_from_hist_end(q, ft_atoi(str + i + 1));
	if (tmp == NULL)
	{
		*str1 = history_error(ft_strsub(*str1, 0, word_size(*str1)));
		return ;
	}
	str = do_zam_str_by_str(i, c, str, tmp);
	*str1 = str;
}

void				zm_history_name(int i, char **str1, char type, t_memory *q)
{
	int		c;
	char	*tmp;
	char	*str;
	char	*str_for_del;

	str = *str1;
	c = i + type;
	while (isword(str[c]) != 0 && str[c])
		c++;
	if (type == 1 && (str_for_del = ft_strsub(str + i + type, 0,
			word_size(str + i + 1))))
		tmp = get_num_from_hist_starting(q, str_for_del);
	if (type == 2)
	{
		str_for_del = ft_strsub(str + i + 2, 0, word_size(str + i + 2));
		tmp = get_num_from_hist_cons(q, str_for_del);
	}
	ft_strdel(&str_for_del);
	if (tmp == NULL)
	{
		*str1 = history_error(ft_strsub(*str1, 0, word_size(*str1)));
		return ;
	}
	str = do_zam_str_by_str(i, c, str, tmp);
	*str1 = str;
}

char				*do_zam_cycle(char *str1, t_memory *q, int i)
{
	if (str1[i + 1] == '!')
		str1 = do_zam_str_by_str(i, i + 2, str1, ft_strdup(q->inp));
	else if (ft_atoi(str1 + i + 1) > 0)
		zm_history_numbers(i, &str1, 0, q);
	else if (ft_atoi(str1 + i + 1) < 0)
		zm_history_numbers(i, &str1, 2, q);
	else if (isword(str1[i + 1]) != 0 &&
	str1[i + 1] != '?' && str1[i + 1] != '-')
		zm_history_name(i, &str1, 1, q);
	else if (str1[i + 1] == '?' || str1[i + 1] == '-')
		zm_history_name(i, &str1, 2, q);
	return (str1);
}

char				*do_zam_str_hist_var(char *str1, t_memory *q)
{
	int			i;

	if (str1 == NULL)
		return (NULL);
	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] == '!')
			str1 = do_zam_cycle(str1, q, i);
		if (str1 == NULL)
			return (NULL);
		i++;
	}
	return (str1);
}
