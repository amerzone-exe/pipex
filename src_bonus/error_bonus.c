/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:03:40 by jpiquet           #+#    #+#             */
/*   Updated: 2025/03/26 19:52:21 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	exit_fd(int fd, t_cmd *cmd, int nb_cmd)
{
	if (fd > 0)
		close(fd);
	free_tab_struct(cmd, nb_cmd + 3);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	exit_both_fd(int fd, int fd2, t_cmd *cmd, int nb_cmd)
{
	if (fd > 0)
		close(fd);
	if (fd2 > 0)
		close(fd2);
	free_tab_struct(cmd, nb_cmd + 3);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	exit_tab(t_cmd *cmd, int nb_cmd, int code)
{
	free_tab_struct(cmd, nb_cmd + 3);
	exit(code);
}

void	exit_pid_error(int *pipex, t_fd *fd, t_cmd *cmd)
{
	if (pipex[0] > 0)
		close(pipex[0]);
	if (pipex[1] > 0)
		close(pipex[1]);
	if (fd->infile > 0)
		close(fd->infile);
	if (fd->outfile > 0)
		close(fd->outfile);
	free_tab_struct(cmd, fd->nb_cmd + 3);
	perror("Error");
	exit(EXIT_FAILURE);
}
