/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:21:40 by jpiquet           #+#    #+#             */
/*   Updated: 2025/03/26 19:52:35 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_cmd
{
	char	*pathname;
	char	**args;
	int		nb_cmd;
	int		error;
	int		status;
}					t_cmd;

typedef struct s_fd
{
	int		infile;
	int		outfile;
	int		outpipe;
	int		nb_cmd;
}					t_fd;

void	exit_error(char *str);
void	exit_fd(int fd, t_cmd *cmd, int nb_cmd);
void	exit_both_fd(int fd, int fd2, t_cmd *cmd, int nb_cmd);
void	exit_tab(t_cmd *cmd, int nb_cmd, int code);
void	exit_pid_error(int *pipex, t_fd *fd, t_cmd *cmd);

void	close_both_files(int fd1, int fd2);
void	close_more_files(int fd1, int fd2, int fd3, int fd4);

t_cmd	*fill_struct(int argc, char *argv[], char *envp[]);
void	free_tab_struct(t_cmd *cmd, int argc);
void	checkfiles(int argc, char *argv[], t_fd *fd);
void	wait_children(pid_t pid_last, t_cmd *cmd);
void	check_struct(t_cmd *cmd, int argc);

void	pipex(t_cmd *cmd, char *envp[], t_fd fd);

#endif