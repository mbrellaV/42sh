/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:29:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 22:36:31 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void		ft_alias(void)
{
	if (!(globals()->g_alias = (char **)ft_memalloc(4 * sizeof(char *))))
		ft_error(15, "malloc error alias");
	globals()->g_alias[0] = ft_strdup("ll=ls -la");
	globals()->g_alias[1] = ft_strdup("l=ls");
	globals()->g_alias[2] = NULL;
}

static int	do_zam_alias(char *str, int *i, char *newstr, char *dopstr)
{
	char	*dop;
	int		size;
	char	*prev_word;

	prev_word = NULL;
	size = word_size(&str[*i]);
	dop = ft_strsub(str, *i, size);
	if (str[*i] != '$' && (dopstr = ft_get_var(dop, globals()->g_alias)) &&
	((!(prev_word = ft_get_prev_word(str, *i)) ||
	is_cmd_delim(get_op_type(prev_word)))
	|| is_first_word(str, *i)))
		ft_strcat(newstr, dopstr);
	else
		ft_strcat(newstr, dop);
	ft_strdel(&prev_word);
	(*i) += size;
	ft_strdel(&dopstr);
	ft_strdel(&dop);
	return (1);
}

static int	alias_cycle(char *str, int *i, char *newstr)
{
	char	*dopstr;
	char	*dop;
	int		size;

	dopstr = NULL;
	size = word_size(&str[*i]);
	if (size > 0 && ispar(str[*i]))
	{
		dop = ft_strsub(str, *i, size + 2);
		ft_strcat(newstr, dop);
		*i += size + 2;
	}
	else if (size > 0 && (str[*i] == '$' || isword(str[*i]) == 1))
		return (do_zam_alias(str, i, newstr, dopstr));
	else
	{
		dop = ft_strdup(" ");
		dop[0] = str[*i];
		ft_strcat(newstr, dop);
		(*i)++;
	}
	ft_strdel(&dopstr);
	ft_strdel(&dop);
	return (1);
}

int			ft_do_zam_alias(char **str)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = *str;
	if (!(*str = ft_strnew(130000)))
		ft_error_q(2);
	while (i < (int)ft_strlen(newstr) && newstr[i] != '\0')
		if (alias_cycle(newstr, &i, *str) == -1)
		{
			ft_strdel(&newstr);
			return (-1);
		}
	ft_strdel(&newstr);
	return (ft_strlen(*str));
}
