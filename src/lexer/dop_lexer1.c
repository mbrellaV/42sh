/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_lexer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:57:32 by mbrella           #+#    #+#             */
/*   Updated: 2019/12/16 18:57:33 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char				*do_zam_str_by_str(int start, int end, char *str, char *zam_str)
{
	char	*newstr;
	int		i;
	int		dopi;

	i = 0;
	dopi = 0;
	if (zam_str == NULL)
		zam_str = ft_strdup("\0");
	if (!(newstr = ft_memalloc((ft_strlen(str) + ft_strlen(zam_str) + 2) * sizeof(char))))
		return (NULL);
	while (str[i] != '\0' && i < start - 1)
	{
		newstr[i] = str[i];
		i++;
	}
	while (zam_str[dopi] != '\0')
	{
		newstr[i] = zam_str[dopi];
		dopi++;
		i++;
	}
	while (str[end] != '\0')
	{
		newstr[i] = str[end];
		end++;
		i++;
	}
	ft_strdel(&str);
	ft_strdel(&zam_str);
	return (newstr);
}

int					dop_subshell(char *str, t_memory *head)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = NULL;
	if (!ft_strstr(str, "("))
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			newstr = ft_strsub(str, i + 1, sc_size(str, '(') - i - 3);
			break ;
		}
		i++;
	}
//	ft_printf("fevsavafsv///////////////// %s ", newstr);
	if (newstr != NULL)
	{
	//	ft_printf("\n///////// %s\n", newstr);
		do_cmd(newstr, head);
	//	ft_printf("fevsavafsv/////////////////123");
		return (1);
	}
	else
		return (-1);
}

int					do_work_subshell(char **mas, t_memory *head)
{
	int		i;

//	ft_printf("sas");
	i = dop_subshell(mas[0], head);
///	ft_printf("\nfff: %d \n rofler: %s\n", i, mas[0]);
	if (i == 0)
		return (0);
	else if (i == -1)
		return (-1);
	if (mas[1] != NULL)
		return (-1);
	ft_printf("sas1");
	return (1);
}

char				*do_zam_str_bax(char *str1, t_dop_str *t)
{
	int			start;
	int			end;
	int			dop;

	dop = 0;
	t->c_b = 0;
	t->i_b = 0;
	end = 0;
	t->str_b = str1;
	if (!(t->new_b = ft_strnew(1)))
		return (NULL);
	while (t->str_b[t->i_b])
	{

		if (t->str_b[t->i_b] == '$' && t->str_b[t->i_b - 1] != '\\' && t->str_b[t->i_b + 1] != '(')
		{
			if (t->str_b[t->i_b + 1] == '{')
				dop++;
			start = t->i_b + 1;
			while (t->str_b[t->i_b] != '\0' && isword(t->str_b[t->i_b]) != 0 && t->str_b[t->i_b] != '}')
				t->i_b++;
			end += t->i_b + (t->str_b[t->i_b] == '}');
			str1 = ft_strsub(t->str_b, start + (dop > 0 ? 1 : 0), end - (dop > 0 ? 2 : 0) - start);
			t->str_b = do_zam_str_by_str(start, end, t->str_b, ft_get_var(str1, g_all_var));
			ft_strdel(&str1);
			return (t->str_b);
		}
		t->i_b++;
	}
	return (t->str_b);
}

char				*do_zam_str_hist_var(char *str1, t_memory *q)
{
	char		*dop;

	ft_printf("adadf\n");
	while ((dop = ft_strstr(str1, "!!")))
	{
		str1 = do_zam_str_by_str(dop - str1, dop - str1 + 2, str1, ft_strdup(q->back->inp));
		ft_printf("\n%s\n", str1);
	}
	ft_printf("\n////////////////////// :    %s\n", str1);
	return (str1);
}

char				*do_obr_zamena_sp(char *line)
{
	int		i;
	int		d;
	int		size;
	char	*new;

	i = 0;
	d = 0;
	size = 0;
	while (line[i++] != '\0')
		size++;
	if (!(new = ft_memalloc(size * sizeof(char) + 1)))
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] < 0)
			new[d++] = -1 * (line[i++]);
		else
			new[d++] = line[i++];
	}
	new[d] = '\0';
	ft_strdel(&line);
	return (new);
}

char				*do_zamena_sp(char *line)
{
	int		i;
	int		d;
	char	*new;

	i = 0;
	d = 0;
	if (!(new = ft_memalloc(ft_strlen(line) * sizeof(char) + 1)))
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\\' && line[i + 1] != '\0')
		{
			new[d] = -1 * (line[i + 1]);
			i++;
		}
		else
			new[d] = line[i];
		i++;
		d++;
	}
	new[d] = '\0';
	return (new);
}

int					c_size(char *str, char b)
{
	int i;

	i = 0;
	str++;
	if (*str == b)
		return (-2);
	while (*str && *str != b)
	{
		i++;
		str++;
	}
	return (i);
}
