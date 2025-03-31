/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:09:26 by jpiquet           #+#    #+#             */
/*   Updated: 2025/03/26 19:46:23 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_tab_struct(t_cmd *cmd, int argc)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (i < argc - 3)
	{
		if (cmd[i].pathname)
		{
			free(cmd[i].pathname);
			cmd[i].pathname = NULL;
		}
		if (cmd[i].args)
		{
			free_all(cmd[i].args);
			cmd[i].args = NULL;
		}
		i++;
	}
	free(cmd);
}

void	checkfiles(int argc, char *argv[], t_fd *fd)
{
	int	infile;
	int	outfile;

	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	fd->outfile = outfile;
	infile = open(argv[1], O_RDONLY);
	fd->infile = infile;
}

void	wait_children(pid_t pid_last, t_cmd *cmd)
{
	waitpid(pid_last, &cmd->status, 0);
	if (WIFEXITED(cmd->status) != 0)
		cmd->error = WEXITSTATUS(cmd->status);
	while (1)
	{
		if (wait(NULL) == -1)
			break ;
	}
}

void	check_struct(t_cmd *cmd, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 3)
	{
		if (cmd[i].pathname == NULL)
		{
			free(cmd[i].args);
			cmd[i].pathname = ft_strdup("empty");
			if (!cmd[i].pathname)
				exit_tab(cmd, argc - 3, 1);
			cmd[i].args = ft_split("empty", ' ');
			if (!cmd[i].args)
				exit_tab(cmd, argc - 3, 1);
		}
		i++;
	}
}
