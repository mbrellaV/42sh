#include "eval_expr.h"

t_calc_token		*ft_cr_new_calc_token(char *line, t_calc_tkntype type)
{
	t_calc_token	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_calc_token))))
		return (NULL);
	tmp->var = ft_strdup(line);
	tmp->type = type;
	tmp->next = NULL;
	return (tmp);
}

t_calc_token		*add_token_cr(t_calc_token *start, t_calc_token *token_to_add)
{
	t_calc_token	*tmp;

	tmp = start;
	while (tmp->next != NULL)
		tmp = tmp->next;
	start = tmp;
	tmp = token_to_add;
	start->next = tmp;
	tmp->prev = start;
	return (tmp);
}