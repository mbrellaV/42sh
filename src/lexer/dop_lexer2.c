/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_lexer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:57:38 by mbrella           #+#    #+#             */
/*   Updated: 2019/12/16 18:57:39 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int				operator_size(char *str)
{
	int i;

	i = 0;
	while (*str != 0 && isoperator(*str) > 0)
	{
		str++;
		i++;
	}
	return (i);
}

int				word_size(char *str)
{
	int i;

	i = 0;
	if (isoperator(*str) > 0)
		return (operator_size(str));
	if (isword(*str) == 2)
		return (c_size(str, *str));
	if (isword(*str) == 3)
		return (sc_size(str, *str));
	while (*str)
	{
		if (isword(*str) == 3)
			return (i + sc_size(str, *str));
		if (isword(*str) == 0)
			return (i);
		i++;
		str++;
	}
	return (i);
}

t_lextoken		*ft_cr_new_token(char *line, int word_type, int op_type)
{
	t_lextoken	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_lextoken))))
		return (NULL);
	tmp->next = NULL;
	tmp->line = line;
	tmp->word_type = word_type;
	tmp->operator_type = op_type;
	tmp->is_near_opt = 0;
	return (tmp);
}

int				get_op_type(char *operator)
{
	int			i;
	static char	operators[9][5] = {";;", ";", "|",\
		"<<", "<", ">>", ">", ">&", "<&"};

	i = 0;
	if (ft_strstr(operator, operators[i]) != NULL)
		return (-1);
	else if (ft_strstr(operator, "<>") != NULL)
		return (-1);
	else if (ft_strstr(operator, "<<-") != NULL)
		return (-1);
	else if (ft_strstr(operator, "||") != NULL)
		return (-1);
	else if (ft_strstr(operator, ">|") != NULL)
		return (-1);
	else if (ft_strstr(operator, ">>>") != NULL)
		return (-1);
	i++;
	while (i < 10)
	{
		if (ft_strcmp(operator, operators[i]) == 0)
			return (i);
		i++;
	}
	return (-2);
}

t_lextoken		*add_token(t_lextoken *start, char *line, int word_type)
{
	t_lextoken	*tmp;

	if (start == NULL)
	{
		tmp = ft_cr_new_token(line, word_type, get_op_type(line));
		tmp->prev = NULL;
		return (tmp);
	}
	tmp = start;
	while (tmp->next != NULL)
		tmp = tmp->next;
	start = tmp;
	tmp = ft_cr_new_token(line, word_type, get_op_type(line));
	start->next = tmp;
	tmp->prev = start;
	return (tmp);
}
