/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 23:28:12 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	t_printf	p;
	char		*s;

	init_printf(&p, format, 1);
	s = NULL;
	va_start(p.li, format);
	while (*p.str)
	{
		if (*p.str == '%')
		{
			if (*(++p.str) == '\0')
				break ;
			s = p.str;
			if (ft_parser(&p) == -1)
			{
				p.str = s;
				ft_add_buff(&p);
			}
		}
		else
			ft_add_buff(&p);
		p.str++;
	}
	va_end(p.li);
	return (return_print(&p));
}

int				ft_dprintf(int fd, const char *format, ...)
{
	t_printf	p;
	char		*s;

	init_printf(&p, format, fd);
	s = NULL;
	va_start(p.li, format);
	while (*p.str)
	{
		if (*p.str == '%')
		{
			if (*(++p.str) == '\0')
				break ;
			s = p.str;
			if (ft_parser(&p) == -1)
			{
				p.str = s;
				ft_add_buff(&p);
			}
		}
		else
			ft_add_buff(&p);
		p.str++;
	}
	va_end(p.li);
	return (return_print(&p));
}

int				ft_sprintf(char *buffer, const char *format, ...)
{
	t_printf	p;
	char		*s;

	init_printf(&p, format, 1);
	va_start(p.li, format);
	while (*p.str)
	{
		if (*p.str == '%')
		{
			if (*(++p.str) == '\0')
				break ;
			s = p.str;
			if (ft_parser(&p) == -1)
			{
				p.str = s;
				ft_add_buff(&p);
			}
		}
		else
			ft_add_buff(&p);
		p.str++;
	}
	va_end(p.li);
	buffer = ft_strcat(buffer, p.buff);
	return (p.buff_index);
}

int				ft_strprintf(char **str, const char *format, ...)
{
	t_printf	p;
	char		*s;

	init_printf(&p, format, 1);
	va_start(p.li, format);
	while (*p.str)
	{
		if (*p.str == '%')
		{
			if (*(++p.str) == '\0')
				break ;
			s = p.str;
			if (ft_parser(&p) == -1)
			{
				p.str = s;
				ft_add_buff(&p);
			}
		}
		else
			ft_add_buff(&p);
		p.str++;
	}
	va_end(p.li);
	*str = p.buff;
	return (p.buff_index);
}
