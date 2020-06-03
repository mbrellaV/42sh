/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_tab_funs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:36:44 by mbrella           #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_add_builtins_in_tab(char *name, t_readline *p)
{
	char	**mas;
	int		i;
	char	*goodstr;

	i = 0;
	mas = globals()->g_builtins;
	while (mas[i] != NULL)
	{
		goodstr = mas[i];
		if (is_cmp(name, goodstr))
			ft_add_tab(p, goodstr);
		i++;
	}
}

void	ft_find_path(t_readline *p, char *name)
{
	char	**path;
	int		i;
	char	*tmp;

	if (!*name)
	{
		return ;
	}
	if (!(tmp = ft_get_var("PATH", globals()->g_env)))
		return ;
	path = ft_strsplit1(tmp, ':');
	if (path == NULL)
		return ;
	i = -1;
	while (path[++i])
		ft_find_dir(path[i], name, p);
	ft_strdel(&tmp);
	ft_arrdel(path);
}

int		is_cmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	if (s1[0] == '\0')
		return (1);
	while (s1[++i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
	}
	if (!s2[i] && s1[i])
		return (0);
	return (1);
}

char	*ft_name(char *str, t_readline *p)
{
	int		k;

	k = (int)ft_strlen(str) - 1;
	if (k < 0)
		return (NULL);
	while (k > 0 && str[k] != '/' && (isword(str[k]) == 1) &&
		str[k] != '$')
	{
		k--;
	}
	if (k >= 0 && str[k] == '$' && str[k + 1] != '{')
		p->flag_tab = 2;
	else if (k >= 0 && str[k] == '$' && str[k + 1] == '{')
		p->flag_tab = 3;
	return (ft_strdup(&str[k + (str[k] == '/' ? 1 : 0)]));
}
