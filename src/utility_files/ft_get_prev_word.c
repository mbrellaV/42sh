/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prev_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pro <pro@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:21:36 by pro               #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int			is_first_word(char *str, int i)
{
	while (i > 0 && isword(str[i]) == 1)
	{
		i--;
	}
	if (i == 0)
		return (1);
	else
		return (0);
}

char		*ft_get_prev_word(char *str, int i)
{
	char	*newstr;

	if (!str)
		return (NULL);
	i--;
	while (i > 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	while (i > 0 && (isword(str[i]) == 1))
		i--;
	if (i < 0)
		i = 0;
	newstr = ft_strsub(str, i, word_size(&str[i]));
	return (newstr);
}

char		*ft_get_next_word(char *str, int i)
{
	char	*newstr;
	int		d;

	d = 0;
	if (!str)
		return (NULL);
	i++;
	while (str[i] != '\0' && isword(str[i]) == 1)
		i++;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] != '\0' && (isword(str[i]) == 1))
	{
		i++;
		d++;
	}
	newstr = ft_strsub(str, i - d, d);
	return (newstr);
}
