/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pro <pro@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:35:46 by pro               #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int		exit_builtin(char **args)
{
	if (ft_strcmp(args[0], "exit") == 0 && ((args[1] == NULL)
		|| (args[1] != NULL && args[2] == NULL)))
	{
		if (args[1] && !ft_str_is_numeric(args[1]))
		{
			vivod(2) ? ft_dprintf(globals()->fd[2],
					"42sh: exit: %s: numeric argument required\n", args[1]) : 0;
			put_error_to_shell(2);
			save_history(globals()->g_memory_head);
			reset_input_mode();
			exit(127);
		}
		else
		{
			reset_input_mode();
			save_history(globals()->g_memory_head);
			exit(args[1] ? ft_atoi(args[1]) : 0);
		}
	}
	else
	{
		vivod(2) ? ft_dprintf(globals()->fd[2], "too many arguments\n") : 0;
		put_error_to_shell(2);
		return (1);
	}
}
