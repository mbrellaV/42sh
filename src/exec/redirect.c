/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:33:28 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/14 13:34:16 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	ft_redirect(t_pipe *p, int new_infile_fd, int new_outfile_fd)
{
	if (*p->infile != new_infile_fd)
	{
		ft_redirect_one(*p->infile, new_infile_fd);
	}
	if (*p->outfile != new_outfile_fd)
	{
		ft_redirect_one(*p->outfile, new_outfile_fd);
	}
	if (*p->errfile != STDERR_FILENO)
	{
		dup2(*p->errfile, STDERR_FILENO);
		close(*p->errfile);
	}
}

void	do_redir_into_file(t_pipe *p, char *file, int new_infile_fd,
		int new_outfile_fd)
{
	ft_open_flag(file, p);
	ft_redirect(p, new_infile_fd, new_outfile_fd);
}

int		return_with_close(int *opened_fds, int int_to_return, char *dopline, int marker)
{
	if (marker != 0)
		ft_redirect_error(marker, dopline);
	free(opened_fds);
	return (int_to_return);
}
