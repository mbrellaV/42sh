/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:37:15 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/27 17:37:16 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_putcut(t_readline *p)
{
//	char	*tmp;
//
//	tmp = *input;
//	*input = ft_strjoin_i(tmp, g_cp, (*flag)->i, (*flag)->max);
//	(*flag)->i += ft_strlen(g_cp);
//	(*flag)->max = ft_strlen(*input);
	if (g_cp[0] != '\0')
		ft_do_addstr(p, g_cp);
//	free(tmp);
//	ft_cleanstr((*flag)->i + 1 + **len);
//	**len = ft_main_norm((*flag)->mod);
//	ft_putstr_fd(*input, 2);
//	ft_setcursor((*flag)->i, (*flag)->max);
}
