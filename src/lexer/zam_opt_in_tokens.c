/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zam_opt_in_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:53:37 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 15:40:48 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static void	norm_help(char ***nopt, int *iopt, char **mas, int *i)
{
	(*nopt)[*iopt] = ft_strdup(mas[*i]);
	(*nopt)[*iopt + 1] = ft_strdup(mas[*i + 1]);
	(*nopt)[*iopt + 2] = ft_strdup(mas[*i + 2]);
	*iopt += 3;
	*i += 3;
}

char		**zam_opt_tokens(char **mas)
{
	char	**nopt;
	int		i;
	int		iopt;

	i = 0;
	iopt = 0;
	if (!(nopt = (char **)ft_memalloc(sizeof(char *) * (ft_env_len(mas) * 2))))
		ft_error_q(15);
	while (mas[i])
	{
		if ((get_op_type(mas[i]) >= 3 && get_op_type(mas[i]) <= 10))
		{
			nopt[iopt] = ft_strdup((mas[i][0] == '<') ? "0" : "1");
			nopt[iopt + 1] = ft_strdup(mas[i]);
			nopt[iopt + 2] = ft_strdup(mas[i + 1]);
			iopt += 3;
			i += 2;
		}
		else if (mas[i][0] >= '0' && mas[i][0] <= '9')
			norm_help(&nopt, &iopt, mas, &i);
		else
			return (NULL);
	}
	nopt[iopt] = NULL;
	return (nopt);
}

void		do_zamena_opt_tokens(t_exectoken *tmp)
{
	char	**dop;

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
