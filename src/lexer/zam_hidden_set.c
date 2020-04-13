#include "fshell.h"

t_lextoken		*do_zam_ravno(t_lextoken *h)
{
	char		*tmp1;
	char		*tmp2;
	t_lextoken	*dop;

	if (h != NULL && h->line != NULL && ft_strstr(h->line, "=") &&
		((h->next == NULL || is_cmd_delim(get_op_type(h->next->line))) && h->prev == NULL))
	{
		tmp1 = ft_strsub(h->line, 0, ft_strstr(h->line, "=") - h->line);
		tmp2 = ft_strsub(h->line, ft_strstr(h->line, "=") - h->line + 1, ft_strlen(h->line));
		set_new_var(tmp1, tmp2, &g_all_var);
		ft_strdel(&tmp1);
		ft_strdel(&tmp2);
		dop = h->next;
		del_one_node_in_lextokens(h);
		return (dop);
	}
	else if (h != NULL && h->line != NULL && ft_strstr(h->line, "=") && h->prev == NULL)
	{
		dop = h->next;
		del_one_node_in_lextokens(h);
		return (dop);
	}
	if (h != NULL)
		return (h->next);
	return (NULL);
}