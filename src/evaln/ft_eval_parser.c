#include "eval_expr.h"

int					is_incr(t_calc_tkntype type)
{
	return (type == CALC_PRE_INC || type == CALC_PRE_DEC || type == CALC_INC || type == CALC_DEC);
}

t_calc_token		*ft_make_token_from_str(char *str, int *i, t_calc_token *prev_token)
{
	int		size;
	char	*tmp;

//is_incr_sym(str[0])
	size = calc_word_size(str);
	if (prev_token && (prev_token->type == CALC_VAR ||
	prev_token->type == CALC_NUMBER || is_incr(prev_token->type)) && (ft_isdigit(str[0]) || ft_isalpha(str[0])))
	{
		tmp = ft_strsub(str, 0, size);
		*i += size;
		return (ft_cr_new_calc_token(tmp, CALC_ERROR));
	}
	tmp = ft_strsub(str, 0, size);
	*i += size;
	return (calc_define_token(tmp));
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
		if (str[i] != ' ')
		{
			tmp_token = ft_make_token_from_str(&str[i], &i, tmp_token);
			if (tmp_token && tmp_token->type == CALC_ERROR)
				return (tmp_token);
			//dprintf(2, "\n2: |%s, %d|\n", tmp_token->var, tmp_token->type);
			if (tmp_token)
			{
				add_token_cr(first_token, tmp_token);
				if (tmp_token->type == CALC_NUMBER && tmp_token->prev->type == CALC_NUMBER)
					return (NULL);
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
	else if (*str == '*')
		return (ft_cr_new_calc_token(str, CALC_MUL));
	else if (*str == '/')
		return (ft_cr_new_calc_token(str, CALC_DIV));
	else if (*str == '%')
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
