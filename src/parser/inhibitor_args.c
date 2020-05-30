#include "fshell.h"

int			*create_inhibitor_args(t_lextoken *tmp)
{
	int		*new_args;
	int		size;
	int		i;

	size = 0;
	i = 0;
	if (tmp == NULL)
		return (NULL);
	while (tmp != NULL && !is_cmd_delim(tmp->operator_type))
	{
		size++;
		tmp = tmp->next;
	}
	if (!(new_args = ft_memalloc(sizeof(int) * (size + 1))))
		ft_error_q(2);
	while (i < size)
	{
		new_args[i] = 0;
		i++;
	}
	new_args[i] = -1;
	return (new_args);
}