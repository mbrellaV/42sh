/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_calc_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 22:42:15 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

t_calc_token	*define_standart_token(char *str, int *i)
{
	int				size;
	char			*tmp;
	t_calc_token	*tmp_token;

	size = calc_word_size(str, 0);
	if (is_incr_sym(str[0]))
		size = 1;
	tmp = ft_strsub(str, 0, size);
	tmp_token = calc_define_token(tmp);
	if (tmp_token == NULL)
	{
		size = 1;
		ft_strdel(&tmp);
		tmp = ft_strsub(str, 0, size);
		tmp_token = calc_define_token(tmp);
	}
	if (tmp_token == NULL)
		tmp_token = ft_ntoken(tmp, CALC_ERROR);
	ft_strdel(&tmp);
	*i += size;
	return (tmp_token);
}

t_calc_token	*calc_define_token(char *str)
{
	if (!str)
		return (NULL);
	else if (!*str)
		return (ft_ntoken(NULL, CALC_END));
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (ft_ntoken(str, CALC_AND));
	else if (ft_strncmp(str, "||", 2) == 0)
		return (ft_ntoken(str, CALC_OR));
	else if (!ft_strncmp(str, "==", 2))
		return (ft_ntoken(str, CALC_EQ));
	else if (!ft_strncmp(str, "!=", 2))
		return (ft_ntoken(str, CALC_DIFF));
	else if (!ft_strncmp(str, "<=", 2))
		return (ft_ntoken(str, CALC_LESSOREQ));
	else if (!ft_strncmp(str, ">=", 2))
		return (ft_ntoken(str, CALC_MOREOREQ));
	else if (*str == '<')
		return (ft_ntoken(str, CALC_LESS));
	else if (*str == '>')
		return (ft_ntoken(str, CALC_MORE));
	else if (!ft_strncmp(str, "++", 2))
		return (ft_ntoken(str, CALC_INC));
	else if (!ft_strncmp(str, "--", 2))
		return (ft_ntoken(str, CALC_DEC));
	else
		return (calc_define_token_next(str));
}

t_calc_token	*calc_define_token_next(char *str)
{
	if (*str == '+')
		return (ft_ntoken(str, CALC_PLUS));
	else if (*str == '-')
		return (ft_ntoken(str, CALC_MINUS));
	else if (!ft_strcmp(str, "*"))
		return (ft_ntoken(str, CALC_MUL));
	else if (!ft_strcmp(str, "/"))
		return (ft_ntoken(str, CALC_DIV));
	else if (!ft_strcmp(str, "%"))
		return (ft_ntoken(str, CALC_MOD));
	else if (*str == '(')
		return (ft_ntoken(str, CALC_FIR_SC));
	else if (*str == ')')
		return (ft_ntoken(str, CALC_SEC_SC));
	else if (ft_isdigit(*str))
		return (ft_ntoken(str, CALC_NUMBER));
	else if (ft_isalpha(*str))
		return (ft_ntoken(str, CALC_VAR));
	else
		return (NULL);
}
