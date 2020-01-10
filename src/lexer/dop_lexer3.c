/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_lexer3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:10:43 by qmartina          #+#    #+#             */
/*   Updated: 2019/12/19 20:10:45 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char			*ft_zach_dop_str(char *tmp, t_dop_bax *t)
{
	if (t != NULL)
		free(t);
	return (tmp);
}

t_lextoken		*ft_zach_dop_str_orig(t_dop_str *t, t_lextoken *tmp)
{
	if (t != NULL)
		free(t);
	return (tmp);
}

t_exectoken		*ft_zach_yyy(t_exectoken *tmp, t_dop_str *t)
{
	if (t != NULL)
		free(t);
	return (tmp);
}
