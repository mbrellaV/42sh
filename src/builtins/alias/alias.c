/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:29:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void		ft_alias(void)
{
	if (!(globals()->g_alias = (char **)ft_memalloc(4 * sizeof(char *))))
		ft_error(15, "malloc error alias", NULL);
	globals()->g_alias[0] = ft_strdup("ll=ls -la");
	globals()->g_alias[1] = ft_strdup("l=ls");
	globals()->g_alias[2] = NULL;
}

int			alias_dop(char *dop, char *prev_word, char *dopstr)
{
	ft_strdel(&prev_word);
	ft_strdel(&dopstr);
	ft_strdel(&dop);
	return (1);
}

static int	do_zam_alias(char *str, int *i, char *newstr, char **remaining_aliases)
{
	char	*dop;
	int		size;
	char	*prev_word;
	char	*dopstr;

	prev_word = NULL;
	size = word_size(&str[*i]);
	dop = ft_strsub(str, *i, size);
	if (str[*i] != '$' && (dopstr = ft_get_var(dop, remaining_aliases)) &&
	((!(prev_word = ft_get_prev_word(str, *i)) ||
	is_cmd_delim(get_op_type(prev_word)))
	|| is_first_word(str, *i)))
	{
		ft_strcat(newstr, dopstr);
		unset_var(dop, &remaining_aliases);
		(*i) += size;
		return (alias_dop(dop, prev_word, dopstr));
	}
	else
	{
		ft_strcat(newstr, dop);
		(*i) += size;
		alias_dop(dop, prev_word, dopstr);
		return (0);
	}
}

static int	alias_cycle(char *str, int *i, char *newstr, char **remaining_aliases)
{
	char	*dop;
	int		size;

	size = word_size(&str[*i]);
	if (size > 0 && ispar(str[*i]))
	{
		dop = ft_strsub(str, *i, size + 2);
		ft_strcat(newstr, dop);
		*i += size + 2;
	}
	else if (size > 0 && (str[*i] != '$' || isword(str[*i]) == 1))
		return (do_zam_alias(str, i, newstr, remaining_aliases));
	else
	{
		dop = ft_strdup(" ");
		dop[0] = str[*i];
		ft_strcat(newstr, dop);
		(*i)++;
	}
	ft_strdel(&dop);
	return (2);
}

int		ft_do_main_zam_alias(char **str, int *semaphore, char **remaining_aliases)
{
	int		i;
	int		dop;
	char	*newstr;

	i = 0;
	newstr = *str;
	*semaphore = 0;
	if (!(*str = ft_strnew(130000)))
		ft_error_q(2);
	while (i < (int)ft_strlen(newstr) && newstr[i] != '\0')
	{
		dop = alias_cycle(newstr, &i, *str, remaining_aliases);
		if (dop == -1)
		{
			ft_strdel(&newstr);
			*semaphore = 0;
			return (-1);
		}
		else if (dop == 1)
			*semaphore = 1;
	}
	ft_strdel(&newstr);
	return (ft_strlen(*str));
}

char		**copy_char_mas(char **env)
{
	int		i;
	char	**newenv;

	i = 0;
	if (!(newenv = (char **)ft_memalloc(sizeof(char *) *
			(ft_env_len(env) + 2))))
		ft_error_q(1);
	while (env[i])
	{
		if (!(newenv[i] = ft_strdup(env[i])))
			ft_error_q(1);
		i++;
	}
	return (newenv);
}

int			ft_do_zam_alias(char **str)
{
	char	**remaining_aliases;
	int		semaphore;
	int		res;

	semaphore = 1;
	res = 0;
	remaining_aliases = copy_char_mas(globals()->g_alias);
	while (semaphore == 1)
	{
		semaphore = 0;
		res = ft_do_main_zam_alias(str, &semaphore, remaining_aliases);
	}
	ft_free_str(remaining_aliases);
	return (res);
}
