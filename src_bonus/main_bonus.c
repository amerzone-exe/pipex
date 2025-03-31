/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:30:24 by jpiquet           #+#    #+#             */
/*   Updated: 2025/03/26 19:32:54 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmd;
	t_fd	fd;
	int		error_temp;

	if (argc < 5)
		exit_error("Not enought arguments\n");
	checkfiles(argc, argv, &fd);
	cmd = fill_struct(argc, argv, envp);
	check_struct(cmd, argc);
	fd.nb_cmd = argc - 3;
	cmd->error = 0;
	pipex(cmd, envp, fd);
	if (cmd->error != 0)
	{
		error_temp = cmd->error;
		free_tab_struct(cmd, argc);
		exit(error_temp);
	}
	free_tab_struct(cmd, argc);
	return (0);
}
