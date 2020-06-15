/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error_to_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:13:19 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	put_error_to_shell(int error)
{
	char	*str_for_del;

	if (error < 0)
		error = -error;
	str_for_del = ft_itoa(error);
	set_new_var("?", str_for_del, &globals()->g_all_var);
	ft_strdel(&str_for_del);
}
