#include "../../inc/fshell.h"

void 	init_nline(t_readline *p, t_nline *l)
{
	int		i;
	int		len_str;

	i = p->index;
	while (p->buff[i] && p->buff[i] != '\n')
		i--;
	len_str = 0;
	while (p->buff[++i] && p->buff != '\n')
		len_str++;

}
