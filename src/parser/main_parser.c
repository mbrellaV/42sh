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
	if ((tmp->operator_type >= 3 && tmp->operator_type <= 10) || tmp->operator_type == -2)
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

char			**zam_opt_tokens(char **mas)
{
	char	**newopt;
	int		i;
	int		iopt;

	i = 0;
	iopt = 0;
	if (!(newopt = (char **)ft_memalloc(sizeof(char *) * (ft_env_len(mas) * 2))))
		ft_error_q(15);
	while (mas[i])
	{
		if ((get_op_type(mas[i]) >= 3 && get_op_type(mas[i]) <= 10))
		{
			newopt[iopt] = ft_strdup((mas[i][0] == '<') ? "0" : "1");
			newopt[iopt + 1] = ft_strdup(mas[i]);
			newopt[iopt + 2] = ft_strdup(mas[i + 1]);
			//dprintf(2, "\nsas: |%s, %s, %s, %d, %d|\n", mas[i], mas[i + 1], mas[i + 2], i, iopt);
			iopt += 3;

			i += 2;
		}
		else if (mas[i][0] >= '0' && mas[i][0] <= '9')
		{
			newopt[iopt] = ft_strdup(mas[i]);
			newopt[iopt + 1] = ft_strdup(mas[i + 1]);
			newopt[iopt + 2] = ft_strdup(mas[i + 2]);
			iopt += 3;
			i += 3;
		}
		else
			return (NULL);
	}
	newopt[iopt] = NULL;
	return (newopt);
}

void			do_zamena_opt_tokens(t_exectoken *tmp)
{
	char **dop;
	if (tmp == NULL)
		return ;
	if (tmp->file_opt != NULL)
	{
		dop = tmp->file_opt;
		tmp->file_opt = zam_opt_tokens(tmp->file_opt);
		ft_free_str(dop);
	}
	do_zamena_opt_tokens(tmp->right);
	do_zamena_opt_tokens(tmp->left);
}

void			ft_change_all_sc(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(' || str[i] == ')')
			str[i] = ' ';
		i++;
	}
}

int				check_all_errors(t_lextoken *tmp)
{
	while (tmp)
	{
		if (tmp->is_near_opt && tmp->line && get_op_type(tmp->line) >= 3 &&
		get_op_type(tmp->line) <= 10 && (tmp->next == NULL || tmp->next->is_near_opt != 1))
			return (-1);

		tmp = tmp->next;
	}
	return (1);
}

t_exectoken		*all_parse(char *cmd)
{
	t_lextoken	*tmp;
	t_exectoken	*extmp;
	t_dop_str	*t;
	//t_lextoken	*dop_tmp;

	t = NULL;
	if (*cmd == '\0')
		return (NULL);
	ft_change_all_sc(cmd);
	//dprintf(2, "\ncmd|%s|\n", cmd);
	if (!(tmp = do_lexer(cmd)))
		return (NULL);
	//ft_strdel(&str_for_del);
//	dprintf(2, "\n10|%s|\n", cmd);
//	dop_tmp = tmp;
//	while (dop_tmp)
//	{
//		dprintf(2, "\n|%d, %s|\n", dop_tmp->is_near_opt, dop_tmp->line);
//		dop_tmp = dop_tmp->next;
//	}
	tmp = do_zam_bax_and_hist_full(tmp);
	if (tmp == NULL)
		return (NULL);
	if (check_all_errors(tmp) != 1)
	{
		ft_error(5, "\\n");
		ft_distr_lex(tmp);
		return (NULL);
	}

//	dop_tmp = tmp;
//	while (dop_tmp)
//	{
//		dprintf(2, "\n|%d, %s|\n", dop_tmp->is_near_opt, dop_tmp->line);
//		dop_tmp = dop_tmp->next;
//	}
	//exit(0);
	free(t);
	extmp = do_parser(tmp);
	do_zamena_opt_tokens(extmp);
	do_obr_zamena_slash(extmp);
//	t_exectoken *exdop = extmp;
//	while (exdop)
//	{
//		dprintf(2, "\n//");
//		ft_show_env(exdop->file_args);
//		dprintf(2, "\n//");
//		ft_show_env(exdop->file_opt);
//		dprintf(2, "\n//");
//		exdop = exdop->right;
//	}
	//exit(0);
	ft_distr_lex(tmp);
	return (extmp);
}
