/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

int			calc_word_size(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_incr_sym(str[i]))
			break ;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (i);
		i++;
	}
	if ((str[i] == '+' && str[i + 1] == '-') ||
		(str[i] == '-' && str[i + 1] == '+'))
		return (i);
	if (is_incr_sym(str[i]) && is_incr_sym(str[i + 1]))
		return (i + 2);
	return (i);
}

t_calc_tkn	*calc_get_next_tkn(char *str, size_t pos)
{
	size_t	i;

	if (!str)
		return (NULL);
	str = str + pos;
	i = 0;
	while (str[i] == ' ')
		i++;
	return (calc_define_tkn(str + i, pos + i));
}

t_calc_tkn	*calc_define_tkn(char *str, size_t pos)
{
	if (!str)
		return (NULL);
	else if (!*str)
		return (calc_newtkn(NULL, CALC_END));
	else if (!ft_strncmp(str, "&&", 2) || !ft_strncmp(str, "||", 2))
		return (calc_get_log_tkn(str, pos));
	else if (!ft_strncmp(str, "==", 2) || !ft_strncmp(str, "!=", 2))
		return (calc_get_eq_tkn(str, pos));
	else if (*str == '<' || *str == '>')
		return (calc_get_com_tkn(str, pos));
	else if (!ft_strncmp(str, "++", 2) || !ft_strncmp(str, "--", 2))
		return (calc_get_inc_tkn(str, pos));
	else if (*str == '+' || *str == '-')
		return (calc_get_add_tkn(str, pos));
	else if (*str == '*' || *str == '/' || *str == '%')
		return (calc_get_mul_mod_tkn(str, pos));
	else
		return (calc_define_tkn_next(str, pos));
}

t_calc_tkn	*calc_define_tkn_next(char *str, size_t pos)
{
	t_calc_var	var;

	if (*str == '(' || *str == ')')
		return (calc_get_parent_tkn(str, pos));
	else if (ft_isdigit(*str))
		return (calc_get_number_tkn(str, pos));
	else if (calc_check_var(str, &var))
		return (calc_get_var_tkn(str, pos, &var));
	else
		return (NULL);
}
