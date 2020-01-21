#include "../../inc/fshell.h"

char				*get_num_from_hist_begin(t_memory *t, int num)
{
	int		i;

	i = 0;
	while (t->back->back != NULL)
		t = t->back;
	while (t->next != NULL)
	{
		if (i == num)
			return (t->inp);
		t = t->next;
		i++;
	}
	return (NULL);
}

char				*get_num_from_hist_end(t_memory *t, int num)
{
	int		i;

	i = 0;
	num = -num;
	while (t->back != NULL)
	{
		if (i == num)
			return (t->inp);
		t = t->back;
		i++;
	}
	return (NULL);
}

char				*get_num_from_hist_starting(t_memory *t, char *name)
{
	int		i;

	i = 0;
	while (t->back != NULL)
	{
		if (t->inp != NULL && ft_strstr(t->inp, name) == t->inp)
			return (t->inp);
		t = t->back;
		i++;
	}
	return (NULL);
}

char				*get_num_from_hist_cons(t_memory *t, char *name)
{
	int		i;

	i = 0;
	t = t->back;
	while (t->back != NULL)
	{
		if (ft_strstr(t->inp, name) != NULL)
			return (t->inp);
		t = t->back;
		i++;
	}
	return (NULL);
}

char				*do_zam_str_hist_var(char *str1, t_memory *q)
{
	int			i;
	int			c;
	char		*tmp;

	if (str1 == NULL)
		return (NULL);
	i = 0;
	c = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] == '!')
		{
			if (str1[i + 1] == '!')
				str1 = do_zam_str_by_str(i, i + 2, str1, ft_strdup(q->back->inp));
			else if (ft_atoi(str1 + i + 1) > 0)
			{
				c = i;
				while (isword(str1[c]) != 0 && str1[c])
					c++;
				if (!(tmp = ft_strdup(get_num_from_hist_begin(q, ft_atoi(str1 + i)))))
					return (NULL);
				str1 = do_zam_str_by_str(i, c, str1, tmp);
			}
			else if (ft_atoi(str1 + i + 1) < 0)
			{
				c = i + 2;
				while (isword(str1[c]) != 0 && str1[c])
					c++;
				if (!(tmp = ft_strdup(get_num_from_hist_end(q, ft_atoi(str1 + i + 1)))))
					return (NULL);
				str1 = do_zam_str_by_str(i, c, str1, tmp);
			}
			else if (isword(str1[i + 1]) != 0 && str1[i + 1] != '?')
			{
				c = i + 1;
				while (isword(str1[c]) != 0 && str1[c] != '\0')
					c++;
				if (!(tmp = ft_strdup(get_num_from_hist_starting(q, ft_strsub(str1 + i + 1, 0, c - i - 1)))))
					return (NULL);
				str1 = do_zam_str_by_str(i, c, str1, tmp);
			}
			else if (str1[i + 1] == '?')
			{
				c = i + 2;
				while (isword(str1[c]) != 0 && str1[c] != '\0')
					c++;
				if (!(tmp = ft_strdup(get_num_from_hist_cons(q, ft_strsub(str1 + i + 2, 0, c - i)))))
					return (NULL);
				str1 = do_zam_str_by_str(i, c, str1, tmp);
			}
		}
		i++;
	}
	return (str1);
}