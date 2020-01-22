#include "../../inc/fshell.h"

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