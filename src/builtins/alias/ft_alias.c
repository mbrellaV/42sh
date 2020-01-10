#include "../../../inc/fshell.h"

void	ft_alias()
{
	if (!(g_alias = (char **)ft_memalloc(3 * sizeof(char*))))
		ft_error(15, "malloc error alias");
	g_alias[0] = ft_strdup("ll=ls");
	g_alias[1] = ft_strdup("l=ls");
	g_alias[2] = NULL;
}

char			*ft_get_alias(char *dop)
{
	int		i;
	char	*dopd;

	i = 0;
	dopd = ft_strjoin(dop, "=");
	while (g_alias[i])
	{
		if (ft_strstr(g_alias[i], dopd) == g_alias[i])
		{
			if (!(dop = ft_strsub(g_alias[i], ft_strlen(dopd),
								  ft_strlen(g_alias[i]) - ft_strlen(dopd))))
				return (NULL);
			ft_strdel(&dopd);
			return (dop);
		}
		i++;
	}
	ft_strdel(&dopd);
	return (NULL);
}

int		ft_do_zam_alias(char **mas)
{
	int		i;
	char	*tmp;

	i = 0;
	if (mas == NULL)
		return (-1);
	while (mas[i])
	{
		if (ft_findenv(mas[i], g_alias) != -404 && ft_strcmp(mas[0], "unalias") != 0 && ft_strcmp(mas[0], "export") != 0 && ft_strcmp(mas[0], "unset") != 0 && ft_strcmp(mas[0], "unexport") != 0 && ft_strcmp(mas[0], "alias") != 0)
		{
			tmp = mas[i];
			if (!(mas[i] = ft_get_alias(mas[i])))
				return (-1);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (0);
}

void	ft_do_change_alias(char **mas)
{
	if (mas[1] == NULL && ft_strcmp(mas[0], "alias") == 0)
		return (ft_show_env(g_alias));
	else if (ft_findenv(mas[1], g_all_var) != -404 && mas[2] == NULL)
	{
		set_new_var(mas[1], ft_get_var(mas[1], g_all_var), &g_alias);
	}
	else if (ft_strcmp(mas[0], "unalias") == 0 && mas[1] != NULL && mas[2] == NULL)
	{
		unset_var(mas[1], &g_alias);
	}
	else if (mas[1] && mas[2] && mas[3] == NULL)
	{
		set_new_var(mas[1], mas[2], &g_alias);
		ft_show_env(g_alias);
	}
	else
		ft_error(15, "parse error");
}
