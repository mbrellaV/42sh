/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cypher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:06:33 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	cypher_char(char *c)
{
	*c ^= KEYCODE;
}

void	uncypher_char(char *c)
{
	*c ^= KEYCODE;
}

void	cypher_str(char *str_to_cypher)
{
	int		i;

	i = 0;
	while (str_to_cypher[i] != '\0')
	{
		cypher_char(&str_to_cypher[i]);
		i++;
	}
}

void	uncypher_str(char *str_to_cypher)
{
	int		i;

	i = 0;
	while (str_to_cypher[i] != '\0')
	{
		uncypher_char(&str_to_cypher[i]);
		i++;
	}
}

void	uncypher_hist(t_memory *head)
{
	while (head != NULL)
	{
		uncypher_str(head->inp);
		head = head->back;
	}
}
