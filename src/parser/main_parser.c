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
		t->prev_c = ft_cr_new_exectoken(tmp, NULL, -2, t);
	else
	{
		if (!(t->prev_c = ft_memalloc(sizeof(t_exectoken))))
			return (NULL);
		t->prev_c->file_args = NULL;
		t->prev_c->file_opt = NULL;
		t->prev_c->left = NULL;
		t->prev_c->right = NULL;
	}
	if (t->prev_c == NULL)
		return (NULL);
	t->start_c = t->prev_c;
	t->prevdot_c = t->prev_c;
	while (tmp != NULL && !is_cmd_delim(tmp->operator_type))
		tmp = tmp->next;
	if (tmp == NULL)
		return (t->start_c);
	return (t->prev_c);
}

t_exectoken		*do_parser(t_lextoken *tmp)
{
	t_dop_str	*t;

	if (!(t = cr_dop_str_par()) ||
	!(t->prev_c = do_parser_dop(t, tmp)))
		ft_error_q(5);
	while (tmp != NULL)
	{
		if (is_cmd_delim(tmp->operator_type))
			t->i_c = tmp->operator_type;
		else if (t->i_c != -1)
		{
			//dprintf(2, "\nsas: |%d|\n", t->i_c);
			if (t->i_c == 2)
				if (!(t->prev_c = ft_cr_new_exectoken(tmp,
						t->prev_c, t->i_c, t)))
					return (NULL);
			if ((t->i_c == 1 || t->i_c >= 9) && (t->prevdot_c = ft_cr_new_exectoken(tmp,
					t->prevdot_c, t->i_c, t)))
				t->prev_c = t->prevdot_c;
			t->i_c = -1;
		}
		tmp = tmp->next;
	}
	return (ft_kill_str_dop_exec(t, t->start_c));
}

t_exectoken		*all_parse(char *cmd)
{
	t_lextoken	*tmp;
	t_exectoken	*extmp;
	t_dop_str	*t;
	t_lextoken	*dop_tmp;
	char		*char_for_cat;
	//t_exectoken	*exdop;
	t_lextoken	*token_for_del;
	char		*str_for_del;


	t = NULL;
	//change_enters_in_sc(cmd);
//	dprintf(2, "\n1|%s|\n", cmd);
	if (!(tmp = do_lexer(cmd)))
		return (NULL);
//	dop_tmp = tmp;
//	while (dop_tmp)
//	{
//		dprintf(2, "\n|%d, %s|\n", dop_tmp->is_near_word, dop_tmp->line);
//		dop_tmp = dop_tmp->next;
//	}
//	dprintf(2, "\n10|%s|\n", cmd);
	tmp = do_zam_bax_and_hist_full(tmp);
	dop_tmp = tmp;
	//ft_strdel(&cmd);
	if ((cmd = (char *)ft_memalloc(13000)) == NULL)
		ft_error_q(15);
	while (dop_tmp)
	{
		char_for_cat = "";
//		dprintf(2, "|%s|\n", dop_tmp->line);
		if (dop_tmp->inhibitor_lvl != 0)
			char_for_cat = dop_tmp->inhibitor_lvl == 1 ? "\"" : "\'";
		if (*char_for_cat != '\0')
			ft_strcat(cmd, char_for_cat);
		if (dop_tmp->line != NULL)
			ft_strcat(cmd, dop_tmp->line);
		if (*char_for_cat != '\0')
			ft_strcat(cmd, char_for_cat);
		if (dop_tmp->next != NULL && dop_tmp->is_near_opt != 1 && *char_for_cat == '\0')
			ft_strcat(cmd, " ");
		ft_strdel(&dop_tmp->line);
		token_for_del = dop_tmp;
		dop_tmp = dop_tmp->next;
		free(token_for_del);
	}
//	dprintf(2, "\n2|%s|\n", cmd);
	str_for_del = cmd;
	cmd = ft_do_zam_eval(cmd);
	if (!(tmp = do_lexer(cmd)))
		return (NULL);
//	dprintf(2, "/////");
	dop_tmp = tmp;
	while (dop_tmp)
	{
//		dprintf(2, "\n|%d, %s|\n", dop_tmp->is_near_opt, dop_tmp->line);
		dop_tmp = dop_tmp->next;
	}
	if (str_for_del != cmd)
		ft_strdel(&str_for_del);
	ft_strdel(&cmd);
	free(t);
	extmp = do_parser(tmp);
	//exdop = extmp;
//	while (exdop)
//	{
//		dprintf(2, "\n//");
//		ft_show_env(exdop->file_args);
//		dprintf(2, "\n//");
//		ft_show_env(exdop->file_opt);
//		dprintf(2, "\n//");
//		exdop = exdop->right;
//	}
	ft_distr_lex(tmp);
	return (extmp);
}
