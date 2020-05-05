/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:54:23 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

char		isEmpty(t_stack *mys)
{
	if(mys->index == 0 )
		return 1;
	else
		return 0;
}

void		push(t_stack *mys, char element)
{
	if(mys->index < mys->capacity)
		mys->array[mys->index++] = element;
}

char		pop(t_stack* mys)
{
	if(!isEmpty(mys))
		return mys->array[--mys->index];
}


int			check_bracket(char *str)
{
	t_stack			temp;
	char			tmpChar;
	unsigned int	i;

	temp.capacity = 10;
	temp.index = 0;
	i = 0;
	while(str[i] != '\0')
	{

		if(str[i] == '{' || str[i] == '[' || str[i] == '(')
			push(&temp, str[i]); //open bracket detected
		if(str[i] == '}' || str[i] == ']' || str[i] == ')') //closed bracket detected
		{
			if(isEmpty(&temp))
				return 0; //no open bracket for the closed bracket, not balanced
			else
			{
				tmpChar = pop(&temp);
				if((str[i] == ']' && tmpChar != '[') ||
				(str[i] == '}' && tmpChar != '{') ||
				(str[i] == ')' && tmpChar != '('))
					return 0;  //not balanced
			}
		}
		i++; //increment the loop
	}
	if(isEmpty(&temp))
		return 1; // if there are no remaining open brackets
	else
		return 0;
}