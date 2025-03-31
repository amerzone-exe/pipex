/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:03:45 by jpiquet           #+#    #+#             */
/*   Updated: 2025/03/26 19:27:44 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_pipe(t_cmd *cmd, char *envp[], t_fd *fd, int i)
{
	int	pid;
	int	pipex[2];

	if (pipe(pipex) == -1)
		exit_tab(cmd, fd->nb_cmd, 1);
	pid = fork();
	if (pid == -1)
		exit_pid_error(pipex, fd, cmd);
	if (pid == 0)
	{
		close_both_files(fd->outfile, pipex[0]);
		if (dup2(fd->infile, STDIN_FILENO) == -1)
			exit_fd(pipex[1], cmd, fd->nb_cmd);
		if (dup2(pipex[1], STDOUT_FILENO) == -1)
			exit_fd(fd->infile, cmd, fd->nb_cmd);
		close_both_files(fd->infile, pipex[1]);
		execve(cmd[i].pathname, cmd[i].args, envp);
		exit_tab(cmd, fd->nb_cmd, 1);
	}
	close_both_files(fd->infile, pipex[1]);
	fd->outpipe = pipex[0];
}

static void	last_pipe(t_cmd *cmd, char *envp[], t_fd *fd, int i)
{
	int	pid_last;
	int	pipex[2];

	if (pipe(pipex) == -1)
		exit_tab(cmd, fd->nb_cmd, 1);
	pid_last = fork();
	if (pid_last == -1)
		exit_pid_error(pipex, fd, cmd);
	if (pid_last == 0)
	{
		close(pipex[1]);
		if (dup2(fd->outpipe, STDIN_FILENO) == -1)
			exit_fd(pipex[0], cmd, fd->nb_cmd);
		close_both_files(fd->outpipe, pipex[0]);
		if (dup2(fd->outfile, STDOUT_FILENO) == -1)
			exit_fd(fd->outfile, cmd, fd->nb_cmd);
		close(fd->outfile);
		execve(cmd[i].pathname, cmd[i].args, envp);
		if (ft_memcmp(cmd[i].pathname, "empty", 5) == 0)
			exit_tab(cmd, fd->nb_cmd, 127);
		exit_tab(cmd, fd->nb_cmd, 1);
	}
	close_more_files(pipex[0], pipex[1], fd->outfile, fd->outpipe);
	wait_children(pid_last, cmd);
}

void	pipex(t_cmd *cmd, char *envp[], t_fd fd)
{
	first_pipe(cmd, envp, &fd, 0);
	last_pipe(cmd, envp, &fd, 1);
}
