/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_distruct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 07:05:42 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		ft_distruct_tree(t_exectoken *q)
{
	if (q != NULL)
	{
		ft_distruct_tree(q->left);
		ft_distruct_tree(q->right);
		ft_arrdel(q->file_args);
		ft_arrdel(q->file_opt);
		free(q->inhibitor_args);
		free(q);
	}
	return (1);
}

int		ft_distruct_memory(t_memory *head)
{
	if (head != NULL)
	{
		ft_distruct_memory(head->back);
		free(head->inp);
		free(head);
	}
	return (1);
}

int		ft_distr_lex(t_lextoken *tmp)
{
	if (tmp != NULL)
	{
		ft_distr_lex(tmp->next);
		free(tmp->line);
		free(tmp);
	}
	return (1);
}

int		ft_dist_str(char *input)
{
	ft_free_str(globals()->g_env);
	free(input);
	free(globals()->g_cp);
	return (1);
}
