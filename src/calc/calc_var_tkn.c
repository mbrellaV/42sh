/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_var_tkn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fshell.h>
#include "calc.h"

static void	calc_fill_var(t_calc_var *var, char *value, size_t size)
{
	if (!var)
		return ;
	var->size = size;
	var->value = value;
}

int			calc_var_is_valid(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}

int			calc_check_var(char *str, t_calc_var *var)
{
	size_t	i;
	char	temp;
	char	*value;

	if (!str || !var)
		return (0);
	if (!(i = calc_var_is_valid(str)))
		return (0);
	temp = str[i];
	str[i] = '\0';
	value = ft_get_var(str, globals()->g_all_var);
	calc_fill_var(var, value, i);
	str[i] = temp;
	return (1);
}

t_calc_tkn	*calc_get_var_tkn(char *str, size_t pos, t_calc_var *var)
{
	t_calc_tkn		*token;
	t_calc_var		*new_var;

	if (!str || !var)
		return (NULL);
	if (!(token = calc_newtkn(NULL, CALC_VAR)))
		return (NULL);
	if (!(new_var = (t_calc_var *)ft_memalloc(sizeof(t_calc_var))))
	{
		calc_del_tkn(&token);
		return (NULL);
	}
	new_var = ft_memcpy((void *)new_var, (void *)var, sizeof(t_calc_var));
	token->value = (void *)new_var;
	token->start_pos = pos;
	token->end_pos = pos + var->size;
	return (token);
}
