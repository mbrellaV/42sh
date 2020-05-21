/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:45:44 by plettie           #+#    #+#             */
/*   Updated: 2020/05/12 22:36:31 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char	*ft_print_oct(char *str, int nb)
{
	while (nb > 777)
		nb /= 10;
	nb = ft_itoa_base(nb, 8);
	ft_putnbr_fd(nb, globals()->fd[1]);
	if (*(str + 4) >= '0' && *(str + 4) <= '7')
		str = str + 5;
	else if (*(str + 3) >= '0' && *(str + 3) <= '7')
		str = str + 4;
	else if (*(str + 2) >= '0' && *(str + 2) <= '7')
		str = str + 3;
	return (str);
}

int		ft_atoi_echo(const char *str)
{
	size_t		i;
	int			result;

	result = 0;
	i = 0;
	if (str[i] < '0' || str[i] > '7')
		return (-404);
	while (str[i] >= '0' && str[i] <= '7')
		result = (result * 10) + (str[i++] - '0');
	return (result);
}

char	*ft_slash_2(char *str, t_builtins *echo, int res)
{
	int			nb;

	nb = -404;
	if (res == 4)
		return (str + 2);
	if ((--res) && *(str + 1) == '0' && (++res))
		nb = ft_atoi_echo((str + 1));
	if ((--res) && *(str + 1) == 'x' && (++res))
		str = ft_hex(str + 1);
	if (!(--res) && *(str + 1) == 'c' && (++res) && (echo->echo_c = 1))
		return (NULL);
	if (nb > 0)
		str = ft_print_oct(str, nb);
	if (nb == 0)
		return (str + 2);
	if (res == 0)
	{
		ft_putchar_fd('\\', globals()->fd[1]);
		return (str + 2);
	}
	return (str);
}

char	*ft_slash(char *str, t_builtins *echo)
{
	int			res;

	res = 13;
	(*(str + 1) == '\\') ? ft_putchar_fd('\\', globals()->fd[1]) : --res;
	(*(str + 1) == 'a') ? ft_putchar_fd('\a', globals()->fd[1]) : --res;
	(*(str + 1) == 'b') ? ft_putchar_fd('\b', globals()->fd[1]) : --res;
	(*(str + 1) == 't') ? ft_putchar_fd('\t', globals()->fd[1]) : --res;
	(*(str + 1) == 'n') ? ft_putchar_fd('\n', globals()->fd[1]) : --res;
	(*(str + 1) == 'v') ? ft_putchar_fd('\v', globals()->fd[1]) : --res;
	(*(str + 1) == 'r') ? ft_putchar_fd('\r', globals()->fd[1]) : --res;
	(*(str + 1) == 'f') ? ft_putchar_fd('\f', globals()->fd[1]) : --res;
	(*(str + 1) == '\"') ? ft_putchar_fd('\"', globals()->fd[1]) : --res;
	(*(str + 1) == '\'') ? ft_putstr_fd("\\\'", globals()->fd[1]) : --res;
	return (ft_slash_2(str, echo, res));
}

int		ft_echo(char **str)
{
	int			k;
	t_builtins	echo;
	int			flag;
	char		*tmp;

	k = 0;
	flag = 0;
	echo.echo_n = 0;
	echo.echo_c = 0;
//	while (str && str[k])
//	{
//		dprintf(globals()->fd[1], "%s\n", str[k]);
//		k++;
//	}
	if (!vivod(1))
		return (-1);
	while (str[++k])
	{
		tmp = str[k];
		!echo.echo_n ? flag = 1 : 0;
		str[k] = distribute_echo(str, k, flag, &echo);
		str[k] = tmp;
		if (str[k + 1] && (*str[k] != '-' || (*str[k] == '-' && !echo.echo_n)))
			ft_dprintf(globals()->fd[1], " ");
	}
	if (!echo.echo_n && !echo.echo_c)
		ft_dprintf(globals()->fd[1], "\n");
	return (0);
}
