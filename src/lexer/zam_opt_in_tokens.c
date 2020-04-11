/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zam_opt_in_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:45:44 by plettie           #+#    #+#             */
/*   Updated: 2020/02/06 11:45:52 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

char			**zam_opt_tokens_h(char **mas, char **newopt, int i, int iopt)
{
	while (mas[i])
	{
		if ((get_op_type(mas[i]) >= 3 && get_op_type(mas[i]) <= 10))
		{
			newopt[iopt] = ft_strdup((mas[i][0] == '<') ? "0" : "1");
			newopt[iopt + 1] = ft_strdup(mas[i]);
			newopt[iopt + 2] = ft_strdup(mas[i + 1]);
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

char			**zam_opt_tokens(char **mas)
{
	char		**newopt;
	int			i;
	int			iopt;

	i = 0;
	iopt = 0;
	if (!(newopt = (char **)ft_memalloc(sizeof(char *) *
			(ft_env_len(mas) * 2))))
		ft_error_q(15);
	return (zam_opt_tokens_h(mas, newopt, i, iopt));
}

void			do_zamena_opt_tokens(t_exectoken *tmp)
{
	char		**dop;

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
