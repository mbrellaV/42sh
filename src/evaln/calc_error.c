/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

t_int	*tmp_0(t_int *tmp, char *s)
{
	tmp->ol = 0;
	tmp->zl = 0;
	tmp->i = 0;
	tmp->d = 0;
	tmp->last_token = 0;
	tmp->s = s;
	return (tmp);
}

int		calc_error(int *stackos, int *stackzn, t_int *str, int *error, char *delstr)
{
	if (stackos != NULL)
		free(stackos);
	if (stackzn != NULL)
		free(stackzn);
	if (str != NULL)
		free(str);
	ft_strdel(&delstr);
	*error = 1;
	return (-1);
}
