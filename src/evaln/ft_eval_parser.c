#include "fshell.h"

int					is_incr(t_calc_tkntype type)
{
	return (type == CALC_PRE_INC || type == CALC_PRE_DEC || type == CALC_INC || type == CALC_DEC);
}

t_calc_token		*check_and_define_pre_incr(char *str, int *i, t_calc_token *prev_token)
{
	int				size;
	char			*tmp;
	t_calc_token	*tmp_token;

	size = calc_word_size(str, 0);
	tmp = ft_strsub(str, 0, size);
	//dprintf(2, "\nffffffff: |%s, %d, %d, %c, %s|\n", tmp, size, *i, str[*i + size], str);
	if ((!ft_strcmp("++", tmp) || !ft_strcmp("--", tmp)) && ft_isalpha(str[size]))
	{
		*i += size;
		tmp_token = ft_cr_new_calc_token(tmp,
				(str[0] == '+' ? CALC_PRE_INC : CALC_PRE_DEC));
		ft_strdel(&tmp);
		return (tmp_token);
	}
	ft_strdel(&tmp);
	return (NULL);
}

//t_calc_token		*check_and_define_pre_incr(char *str, int *i, t_calc_token *prev_token)
//{
//	int				size;
//	char			*tmp;
//	t_calc_token	*tmp_token;
//
//	size = calc_word_size(str, 0);
//	if (ft_isalpha(str[size + *i]) && (is_incr_sym(str[*i + size]) &&
//	is_incr_sym(str[*i + size + 1]) && str[*i + size] == str[*i + size + 1]))
//	{
//		*i += size;
//		tmp = ft_strsub(str, 0, size);
//		tmp_token = ft_cr_new_calc_token(tmp, CALC_ERROR);
//		ft_strdel(&tmp);
//		return (tmp_token);
//	}
//	return (NULL);
//}

t_calc_token		*check_calc_error(char *str, int *i, t_calc_token *prev_token)
{
	int				size;
	char			*tmp;
	t_calc_token	*tmp_token;

	if (prev_token && (prev_token->type == CALC_VAR ||
	prev_token->type == CALC_NUMBER) &&
		(ft_isdigit(str[0]) || ft_isalpha(str[0])))
	{
		size = calc_word_size(str, 0);
		*i += size;
		tmp = ft_strsub(str, 0, size);
		tmp_token = ft_cr_new_calc_token(tmp, CALC_ERROR);
		ft_strdel(&tmp);
		return (tmp_token);
	}
	else
		return (NULL);
}

t_calc_token		*check_calc_incr_after(char *str, int *i, t_calc_token *prev_token)
{
	int				size;
	char			*tmp;
	t_calc_token	*tmp_token;

	if (prev_token && (prev_token->type == CALC_VAR) && is_incr_sym(*str) && is_incr_sym(*(str + 1)))
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

t_calc_token		*check_if_incr_with_num(char *str, int *i, t_calc_token *prev_token)
{
	char			*tmp;
	t_calc_token	*tmp_token;
	char			*dopstr;
	int				d;

	tmp = ft_get_next_word(str, 0);
	//dprintf(2, "\nnext: |%s|\n", tmp);
	if ((!prev_token || (prev_token->type == CALC_PLUS ||
	prev_token->type == CALC_MINUS)) && is_incr_sym(str[0]) && !is_incr_sym(str[1]) &&
			ft_str_is_numeric(tmp))
	{
		if (!(dopstr = ft_strnew(ft_strlen(tmp) + 100)))
			ft_error_q(2);
		ft_strdel(&tmp);
		ft_strcat_char(dopstr, str[0]);
		d = 1;
		while (str[d] != '\0' && (str[d] == ' ' || str[d] == '\t'))
			d++;
		while (str[d] != '\0' && (str[d] != ' ' && str[d] != '\t'))
		{
			ft_strcat_char(dopstr, str[d]);
			d++;
		}
		//dprintf(2, "\nnum: |%s, %s, %d|\n", str, dopstr, d);
		tmp_token = ft_cr_new_calc_token(dopstr, CALC_NUMBER);
		*i += d;
		ft_strdel(&dopstr);
		//exit(0);
		return (tmp_token);
	}
	ft_strdel(&tmp);
	return (NULL);
}

t_calc_token		*check_calc_incr_after_incr(char *str, int *i, t_calc_token *prev_token)
{
	int				size;
	char			*tmp;
	t_calc_token	*tmp_token;

	if (prev_token && (prev_token->type == CALC_VAR ||
	prev_token->type == CALC_NUMBER) && !(*str != 0 && is_incr_sym(*str) && is_incr_sym(*(str + 1))))
	{
		size = calc_word_size(str, 1);
		*i += size;
		tmp = ft_strsub(str, 0, size);
		tmp_token = calc_define_token(tmp);
		ft_strdel(&tmp);
		return (tmp_token);
	}
	else
		return (NULL);
}

t_calc_token		*ft_make_token_from_str(char *str, int *i, t_calc_token *prev_token)
{
	int				size;
	char			*tmp;
	t_calc_token	*tmp_token;

	//dprintf(2, "\nrofl: |%d|\n", *i);
	if ((tmp_token = check_and_define_pre_incr(str, i, prev_token)))
		return (tmp_token);
	else if ((tmp_token = check_calc_incr_after(str, i, prev_token)))
		return (tmp_token);
	else if ((tmp_token = check_calc_error(str, i, prev_token)))
		return (tmp_token);
	else if ((tmp_token = check_if_incr_with_num(str, i, prev_token)))
		return (tmp_token);
//	else if ((tmp_token = check_calc_incr_after_incr(str, i, prev_token)))
//		return (tmp_token);
	else
	{
		size = calc_word_size(str, 0);
		if (is_incr_sym(str[0]))
			size = 1;
		tmp = ft_strsub(str, 0, size);
		tmp_token = calc_define_token(tmp);
		if (tmp_token == NULL)
		{
			size = 1;
			tmp = ft_strsub(str, 0, size);
			tmp_token = calc_define_token(tmp);
		}
		if (tmp_token == NULL)
			tmp_token = ft_cr_new_calc_token(tmp, CALC_ERROR);
		//dprintf(2, "\ntoken: |%s|\n",  tmp_token->var);
		ft_strdel(&tmp);
		*i += size;
		return (tmp_token);
	}
}

t_calc_token		*ft_eval_parse(char *str)
{
	int				i;
	t_calc_token	*first_token;
	t_calc_token	*tmp_token;

	i = 0;
	tmp_token = NULL;
	if (!(first_token = ft_cr_new_calc_token(NULL, CALC_START)))
		return (NULL);
	while (str[i] != '\0')
	{
		//dprintf(2, "\ntest: |%c|\n", str[i]);
		if (str[i] != ' ')
		{
			tmp_token = ft_make_token_from_str(&str[i], &i, tmp_token);
			if (tmp_token && tmp_token->type == CALC_ERROR)
				return (tmp_token);
			if (tmp_token)
			{
				add_token_cr(first_token, tmp_token);
			}
		}
		else
			i++;
	}
	return (first_token);
}

t_calc_token	*calc_define_token(char *str)
{
	if (!str)
		return (NULL);
	else if (!*str)
		return (ft_cr_new_calc_token(NULL, CALC_END));
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (ft_cr_new_calc_token(str, CALC_AND));
	else if (ft_strncmp(str, "||", 2) == 0)
		return (ft_cr_new_calc_token(str, CALC_OR));
	else if (!ft_strncmp(str, "==", 2))
		return (ft_cr_new_calc_token(str, CALC_EQ));
	else if (!ft_strncmp(str, "!=", 2))
		return (ft_cr_new_calc_token(str, CALC_DIFF));
	else if (*str == '<')
		return (ft_cr_new_calc_token(str, CALC_LESS));
	else if (*str == '>')
		return (ft_cr_new_calc_token(str, CALC_MORE));
	else if (!ft_strncmp(str, "++", 2))
		return (ft_cr_new_calc_token(str, CALC_INC));
	else if (!ft_strncmp(str, "--", 2))
		return (ft_cr_new_calc_token(str, CALC_DEC));
	else if (*str == '+')
		return (ft_cr_new_calc_token(str, CALC_PLUS));
	else if (*str == '-')
		return (ft_cr_new_calc_token(str, CALC_MINUS));
	else if (!ft_strcmp(str, "*"))
		return (ft_cr_new_calc_token(str, CALC_MUL));
	else if (!ft_strcmp(str, "/"))
		return (ft_cr_new_calc_token(str, CALC_DIV));
	else if (!ft_strcmp(str, "%"))
		return (ft_cr_new_calc_token(str, CALC_MOD));
	else
		return (calc_define_token_next(str));
}

t_calc_token	*calc_define_token_next(char *str)
{
	if (*str == '(')
		return (ft_cr_new_calc_token(str, CALC_FIR_SC));
	else if (*str == ')')
		return (ft_cr_new_calc_token(str, CALC_SEC_SC));
	else if (ft_isdigit(*str))
		return (ft_cr_new_calc_token(str,  CALC_NUMBER));
	else if (ft_isalpha(*str))
		return (ft_cr_new_calc_token(str, CALC_VAR));
	else
		return (NULL);
}
