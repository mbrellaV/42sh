/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_calc_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/03 20:13:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_calc_token		*check_and_define_pre_incr(char *str, int *i,
		t_calc_token *prev_token)
{
	int				size;
	char			*tmp;
	t_calc_token	*tmp_token;

	size = calc_word_size(str, 0);
	tmp = ft_strsub(str, 0, size);
	if ((!ft_strcmp("++", tmp) || !ft_strcmp("--", tmp)) &&
	ft_isalpha(str[size]))
	{
		*i += size;
		tmp_token = ft_ntoken(tmp,
				(str[0] == '+' ? CALC_PRE_INC : CALC_PRE_DEC));
		ft_strdel(&tmp);
		return (tmp_token);
	}
	ft_strdel(&tmp);
	return (NULL);
}

t_calc_token		*check_calc_error(char *str, int *i,
		t_calc_token *prev_token)
{
	int				size;
	char			*tmp;
	t_calc_token	*tmp_token;

	if (prev_token && (calc_prev_mean_calc_token(prev_token)->type == CALC_VAR ||
	calc_prev_mean_calc_token(prev_token)->type == CALC_NUMBER) && (ft_isdigit(str[0]) ||
	ft_isalpha(str[0])))
	{
		size = calc_word_size(str, 0);
		*i += size;
		tmp = ft_strsub(str, 0, size);
		tmp_token = ft_ntoken(tmp, CALC_ERROR);
		ft_strdel(&tmp);
		return (tmp_token);
	}
	else
		return (NULL);
}

t_calc_token		*check_calc_incr_after(char *str, int *i,
		t_calc_token *prev_token)
{
	int				size;
	char			*tmp;
	t_calc_token	*tmp_token;

	if (prev_token && (prev_token->type == CALC_VAR) && is_incr_sym(*str)
	&& is_incr_sym(*(str + 1)))
	{
		size = 2;
		tmp = ft_strsub(str, 0, size);
		tmp_token = calc_define_token(tmp);
		ft_strdel(&tmp);
		*i += size;
		return (tmp_token);
	}
	else
		return (NULL);
}

t_calc_token		*check_if_incr_with_num(char *str, int *i,
		t_calc_token *prev_token)
{
	char			*tmp;
	t_calc_token	*tmp_token;
	char			*dopstr;
	int				d;

	tmp = ft_get_next_word(str, 0);
	if ((!prev_token || (is_znak_type(prev_token->type))) && is_incr_sym(str[0])
	&& !is_incr_sym(str[1]) && ft_str_is_numeric(tmp))
	{
		!(dopstr = ft_strnew(ft_strlen(tmp) + 100)) ? ft_error_q(2) : 0;
		ft_strdel(&tmp);
		ft_strcat_char(dopstr, str[0]);
		d = 1;
		while (str[d] != '\0' && (str[d] == ' ' || str[d] == '\t'))
			d++;
		while (str[d] != '\0' && (str[d] != ' ' && str[d] != '\t'))
			ft_strcat_char(dopstr, str[d++]);
		tmp_token = ft_ntoken(dopstr, CALC_NUMBER);
		*i += d;
		ft_strdel(&dopstr);
		return (tmp_token);
	}
	ft_strdel(&tmp);
	return (NULL);
}
