/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:54:23 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 17:20:26 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

char		isempty(t_stack *mys)
{
	if (mys->index == 0)
		return (1);
	else
		return (0);
}

void		push(t_stack *mys, char element)
{
	if (mys->index < mys->capacity)
		mys->array[mys->index++] = element;
}

char		pop(t_stack *mys)
{
	if (!isempty(mys))
		return (mys->array[--mys->index]);
	return ('\0');
}

int			norm_return(char tmpchar, t_stack *temp, char str)
{
	tmpchar = pop(temp);
	if ((str == ']' && tmpchar != '[') ||
			(str == '}' && tmpchar != '{') ||
			(str == ')' && tmpchar != '('))
		return (1);
	return (0);
}

int			check_bracket(char *str)
{
	t_stack			temp;
	char			tmpchar;
	unsigned int	i;

	temp.capacity = 10;
	temp.index = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '{' || str[i] == '[' || str[i] == '(')
			push(&temp, str[i]);
		if (str[i] == '}' || str[i] == ']' || str[i] == ')')
		{
			if (isempty(&temp))
				return (0);
			else if (norm_return(tmpchar, &temp, str[i]))
				return (0);
		}
		i++;
	}
	if (isempty(&temp))
		return (1);
	return (0);
}
