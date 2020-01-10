/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:53:40 by mbrella           #+#    #+#             */
/*   Updated: 2019/12/11 18:53:42 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

t_dop_str		*cr_dop_str(char **line1)
{
	t_dop_str	*tmp;
	char		*line;

	line = *line1;
	if (line == NULL)
		return (NULL);
	if (line[0] == '\0')
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(t_dop_str))))
		return (NULL);
	tmp->tmp = NULL;
	tmp->dop = 0;
	tmp->d = 0;
	tmp->i = 0;
	tmp->doptail = NULL;
	tmp->tail = NULL;
	line = do_zamena_sp(line);
	line = do_zam_str_bax(line);
	line = do_zam_str(line);
	*line1 = line;
	return (tmp);
}

int				dop_lexer2(t_dop_str *tmp, char *line)
{
	tmp->tmp = ft_strsub(line, tmp->i, word_size(line + tmp->i));
	if (is_cmd_delim(get_op_type(tmp->tmp)) == 0 && tmp->i != 0 &&
		isword(line[tmp->i - 1]) && (get_op_type(tmp->tmp) > 6))
		tmp->tail->is_near_opt = 1;
	if (!(tmp->tail = add_token(tmp->tail, tmp->tmp, 0)))
		return (-1);
	tmp->tail->is_near_opt = 1;
	if (tmp->tail->operator_type == 2 && tmp->tail->prev == NULL)
		return (ft_error(5, "\\n") == -1);
	tmp->i += word_size(line + tmp->i);
	return (0);
}

int				dop_lexer(t_dop_str *tmp, char *line)
{
	if (isword(line[tmp->i]))
	{
		tmp->tmp = ft_strsub(line, tmp->i + (ispar(line[tmp->i]) == 1 ? 1 : 0),
			word_size(line + tmp->i));
		if (tmp->tail != NULL && tmp->tail->operator_type > 2)
			tmp->d = 1;
		if (!(tmp->tail = add_token(tmp->tail, tmp->tmp, 1)))
			return (-1);
		tmp->tail->is_near_opt = tmp->d;
		tmp->i += word_size(line + tmp->i) + (ispar(line[tmp->i]) == 1 ? 2 : 0);
		tmp->d = 0;
	}
	else if (isoperator(line[tmp->i]))
	{
		if (dop_lexer2(tmp, line) == -1)
			return (-1);
	}
	else
		tmp->i++;
	if (tmp->dop == 0 && tmp->tail != NULL)
	{
		tmp->doptail = tmp->tail;
		tmp->dop = 1;
	}
	return (0);
}

t_lextoken		*do_lexer(char *line, t_dop_str *tmp)
{
	if (!(tmp = cr_dop_str(&line)))
		return (NULL);
	while (line[tmp->i] != '\0')
	{
		if (dop_lexer(tmp, line) == -1)
			return (NULL);
	}
	if (tmp->tail != NULL && tmp->tail->operator_type == 2)
		return (ft_error(5, "\\n") == -1 ? NULL : 0);
	tmp->tail = tmp->doptail;
	while (tmp->tail)
	{
		if (tmp->tail->operator_type == -1)
			return (ft_error(5, tmp->tail->line) == -1 ? NULL : 0);
		tmp->tail->line = do_obr_zamena_sp(tmp->tail->line);
		tmp->tail = tmp->tail->next;
	}
	ft_strdel(&line);
	return (ft_zach_dop_str_orig(tmp, tmp->doptail));
}
