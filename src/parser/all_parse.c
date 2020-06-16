/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:54:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static t_exectoken	*return_with_del(char *del, t_exectoken *ret)
{
	ft_strdel(&del);
	return (ret);
}

int					return_check(char *str, int i)
{
	if (i == -1)
	{
		ft_dprintf(globals()->fd[2],
				"%s: unexpected EOF while looking for matching \"'\n", str);
		return (0);
	}
	if (ck_br(str) <= 0)
	{
		ft_dprintf(globals()->fd[2],
				"%s: unexpected EOF while looking for matching ()\n", str);
		return (0);
	}
	return (1);
}

int					check_par_and_brackets(char *str)
{
	int		i;
	int		size;

	i = 0;
	while (str[i] != '\0')
	{
		if (ispar(str[i]))
		{
			if ((size = c_size(&str[i], str[i])) == -1)
				return (return_check(str, -1));
			if (size == -2)
				i += 2;
			else
				i += size + 2;
		}
		else
			i++;
	}
	return (return_check(str, i));
}

int					check_opt_tokens(t_lextoken *tmp)
{
	while (tmp != NULL)
	{
		if (tmp->next && tmp->line && tmp->next->line &&
			is_cmd_redirect(get_op_type(tmp->line)) &&
			is_cmd_redirect(get_op_type(tmp->next->line)))
		{
			ft_error(5, tmp->line, NULL);
			return (-1);
		}
		if (tmp->line && is_cmd_redirect(get_op_type(tmp->line)) &&
				tmp->next->line == NULL)
		{
			ft_error(5, tmp->line, NULL);
			return (-1);
		}
		if (tmp->next && tmp->line && tmp->next->line &&
			is_cmd_redirect(get_op_type(tmp->line)) &&
			get_op_type(tmp->next->line) >= 0)
		{
			ft_error(5, tmp->line, NULL);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}

t_exectoken			*all_parse(char *cmd)
{
	t_lextoken	*tmp;
	t_exectoken	*extmp;
	t_lextoken	*dop_tmp;

	if (*cmd == '\0' || check_par_and_brackets(cmd) == 0)
		return (NULL);
	cmd = ft_change_all_sc(cmd);
	if (!(tmp = do_lexer(cmd)))
		return (return_with_del(cmd, NULL));
	if (check_all_errors(tmp) != 1)
	{
		ft_error(5, "\\n", NULL);
		ft_distr_lex(tmp);
		return (return_with_del(cmd, NULL));
	}
	if (!(tmp = do_zam_bax_and_hist_full(tmp, &dop_tmp)) &&
		ft_distr_lex(dop_tmp))
		return (return_with_del(cmd, NULL));
	if (check_opt_tokens(tmp) == -1 && ft_distr_lex(tmp))
		return (return_with_del(cmd, NULL));
	extmp = do_parser(tmp);
	do_zamena_opt_tokens(extmp);
	do_obr_zamena_slash(extmp);
	ft_distr_lex(tmp);
	return (return_with_del(cmd, extmp));
}
