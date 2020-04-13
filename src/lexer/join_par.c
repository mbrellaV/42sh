#include "fshell.h"

t_lextoken		*do_zam_join_par(t_lextoken *h)
{
	char        *tmp;
	t_lextoken  *lextmp;
	t_lextoken  *lextmp1;

	lextmp1 = h;
	while (h)
		if (h->next && h->next->is_near_word == 1)
		{
			tmp = h->next->line;
			lextmp = h->next;
			h->next->inhibitor_lvl = h->inhibitor_lvl;
			h->next->line = ft_strjoin(h->line, h->next->line);
			ft_strdel(&tmp);
			del_one_node_in_lextokens(h);
			h = lextmp;
			if (h == NULL)
				continue ;
			if (h->prev == NULL)
				lextmp1 = h;
			h->is_near_word = 0;
			h->inhibitor_lvl = 2;
		}
		else
			h = h->next;
	return (lextmp1);
}