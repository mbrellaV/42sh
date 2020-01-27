
#include "../../../inc/fshell.h"

int		ft_env_len(char **env)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (env[++i])
		count++;
	return (count);
}

void	ft_global_env(char **env, int argc)
{
	int		i;
	int		k;

	i = -1;
	k = argc;
	do_all_var(env, argc);
	if (!(g_env = (char **)ft_memalloc(sizeof(char *) * (ft_env_len(env) + 1))))
		ft_error_q(1);
	while (env[++i])
	{
		if (!(g_env[i] = ft_strdup(env[i])))
			ft_error_q(1);
		k++;
	}
	ft_global_dir(0, "HOME=");
	g_cp = ft_strnew(1);
}

void	ft_show_env(char **env)
{
	int		i;

	i = 0;
	if (env == NULL)
		return ;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
	ft_printf("\n\n\n\n\n");
}

void	ft_realloc_all(int k, char ***envl)
{
	char	**tmp;
	int		i;
	char	**env;

	i = 0;
	env = *envl;
	if (env == NULL)
		return ;
	if (!(tmp = (char **)ft_memalloc(sizeof(char *) *
									 (ft_env_len(env) + k))))
		ft_error_q(1);
	while (env[i])
	{
		//ft_printf("\n%s\n", env[i]);
		if (!(tmp[i] = ft_strdup(env[i])))
			ft_error_q(1);
		//ft_printf("sas");
		ft_strdel(&env[i]);
		//ft_printf("sas1");
		i++;
	}
	free(*envl);
	*envl = tmp;
}

int		ft_findenv(char *s, char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (ft_strcmp_start(env[i], s) == 1)
			return (i);
	}
	return (-404);
}

int		unset_var(char *str, char ***envl)
{
	int		i;
	char	**env;

	env = *envl;
	str = ft_strjoinch(str, '=');
	i = ft_findenv(str, env);
	if (i == -404)
		return (-1);
	else
	{
		free(env[i]);
		env[i] = NULL;
		while (env[i + 1])
		{
			if (!(env[i] = ft_strdup(env[i + 1])))
				return (-1);
			free(env[i + 1]);
			env[i + 1] = NULL;
			i++;
		}
	}
	return (0);
}

int		set_new_var(char *str1, char *str2, char ***envl)
{
	char	**env;
	int		i;
	char	*tmp;

	env = *envl;
	ft_printf("\n/////////////////////////////////////s1: %s", str1);
	ft_printf("\n/////////////////////////////////////s1: %s", str2);
	str1 = ft_strjoinch(str1, '=');
	i = ft_findenv(str1, env);
	tmp = str1;
	//ft_printf("\n////////////////////// %d /////\n", i);
	//ft_printf("s2");
	if (i != -404)
	{
		//ft_printf("s3");
		i = ft_findenv(str1, env);
		ft_strdel(&env[i]);
	//	ft_printf("s4");
		env[i] = ft_strjoin(str1, str2);
		ft_realloc_all(2, envl);
		ft_strdel(&tmp);
		//ft_printf("s5");
	}
	else
	{
		i = 0;
		while (env[i])
			i++;
		env[i] = ft_strjoin(str1, str2);
		ft_realloc_all(2, envl);
		ft_strdel(&tmp);
	}
	return (0);
}

char	**realloc_and_unset(int k, char **str)
{
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (i == k)
		{
			while (str[i])
			{
				if (!(str[i] = str[i + 1]))
					return (str);
				i++;
			}
		}
		i++;
	}
	return (str);
}

int		do_zam_ravno(char **str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		//ft_printf("\nroflan: |%s|", str[i]);
		//ft_printf("\nroflan: |%s|", str[i]);
		if (ft_strstr(str[i], "=") && ispar(str[i][ft_strfind_index(str[i], '=') + 1]) == 0)
		{
			//ft_printf("sass1: %d", issc(str[i][ft_strfind_index(str[i], '=') + 1]));
			set_new_var(ft_strsub(str[i], 0, ft_strstr(str[i], "=") - str[i]),
					ft_strsub(str[i], ft_strstr(str[i], "=") - str[i] + 1, ft_strlen(str[i])), &g_all_var);
			if (!(str = realloc_and_unset(i, str)))
				return (-1);
			i--;
		}
		if (ft_strstr(str[i], "=") && ispar(str[i][ft_strfind_index(str[i], '=') + 1]) == 1)
		{
			//ft_printf("sass2");
			set_new_var(ft_strsub(str[i], 0, ft_strstr(str[i], "=") - str[i]),
				ft_strsub(str[i], ft_strfind_index(str[i], '=') + 2, ft_strlen(str[i]) - ft_strfind_index(str[i], '=') - 3), &g_all_var);
			if (!(str = realloc_and_unset(i, str)))
				return (-1);
		}
		i++;
	}
	return (0);
}

void	do_all_var(char **env, int argc)
{
	int		i;
	int		k;

	i = -1;
	k = argc;
	if (!(g_all_var = (char **)ft_memalloc(sizeof(char *) *
			(ft_env_len(env) + 1))))
		ft_error_q(1);
	while (env[++i])
	{
		if (!(g_all_var[i] = ft_strdup(env[i])))
			ft_error_q(1);
		k++;
	}
}
