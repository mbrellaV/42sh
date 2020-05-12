/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:04:19 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static void	print_wstygg(void)
{
	ft_printf("77 73 74 79 67 67\n");
}

static void	print_mbrella(void)
{
	ft_printf("6D 62 72 65 6C 6C 61\n");
}

static void	print_plettie(void)
{
	ft_printf("70 6C 65 74 74 69 65\n");
}

static void	print_qmartina(void)
{
	ft_printf("71 6D 61 72 74 69 6E 61\n");
}

int			do_authors(void)
{
	print_qmartina();
	print_mbrella();
	print_plettie();
	print_wstygg();
	return (1);
}
