/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 19:19:45 by mbrella           #+#    #+#             */
/*   Updated: 2019/12/11 19:19:46 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

t_exectoken		*do_parser_dop(t_dop_str *t, t_lextoken *tmp)
{
	if (tmp == NULL)
		return (NULL);
	if (tmp->operator_type == -2)
		t->prev = ft_cr_new_exectoken(tmp, NULL, -2);
	else
	{
		if (!(t->prev = ft_memalloc(sizeof(t_exectoken))))
			return (NULL);
		t->prev->file_args = NULL;
		t->prev->file_opt = NULL;
		t->prev->left = NULL;
		t->prev->right = NULL;
	}
	if (t->prev == NULL)
		return (NULL);
	t->start = t->prev;
	t->prevdot = t->prev;
	while (tmp != NULL && !is_cmd_delim(tmp->operator_type))
		tmp = tmp->next;
	if (tmp == NULL)
		return (t->start);
	return (t->prev);
}

t_exectoken		*do_parser(t_lextoken *tmp)
{
	t_dop_str	*t;

	if (!(t = cr_dop_str_par()) || !(do_parser_dop(t, tmp)))
		return (NULL);
	while (tmp != NULL)
	{
		if (is_cmd_delim(tmp->operator_type))
			t->i = tmp->operator_type;
		else if (t->i != -1)
		{
			if (t->i == 2)
				if (!(t->prev = ft_cr_new_exectoken(tmp, t->prev, t->i)))
					return (NULL);
			if (t->i == 1)
			{
				if (!(t->prevdot = ft_cr_new_exectoken(tmp, t->prevdot, t->i)))
					return (NULL);
				t->prev = t->prevdot;
			}
			t->i = -1;
		}
		tmp = tmp->next;
	}
	return (ft_zach_yyy(t->start, t));
}

t_exectoken		*all_parse(char *cmd)
{
	t_lextoken	*tmp;
	t_exectoken	*extmp;
	t_dop_str	*t;

	t = NULL;
	if (!(tmp = do_lexer(cmd, t)))
		return (NULL);
	//ft_printf("\n%s\n", tmp->line);
	//ft_printf("\n%s\n", tmp->next->line);
	free(t);
	extmp = do_parser(tmp);
	//ft_printf("\n%s\n", extmp->file_args[0]);
	//ft_printf("\n%s\n", extmp->file_args[1]);
	ft_distr_lex(tmp);
	return (extmp);
}
