/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 20:32:18 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/02 13:20:10 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	do_count_shell_lvl(void)
{
	char	*dop;
	char	*dop1;

	if (!(dop = ft_get_var("SHLVL", globals()->g_env)))
	{
		set_new_var("?", "0", &globals()->g_all_var);
		set_new_var("SHLVL", "1", &globals()->g_env);
		set_new_var("SHLVL", "1", &globals()->g_all_var);
		return ;
	}
	set_new_var("?", "0", &globals()->g_all_var);
	dop1 = ft_itoa(ft_atoi(dop) + 1);
	set_new_var("SHLVL", dop1, &globals()->g_env);
	set_new_var("SHLVL", dop1, &globals()->g_all_var);
	ft_strdel(&dop);
	ft_strdel(&dop1);
}
