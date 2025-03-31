/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:10:14 by jpiquet           #+#    #+#             */
/*   Updated: 2025/03/26 17:29:51 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*pathcmd_join(char *s1, char *s2)
{
	size_t	tlen;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	tlen = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (tlen + 2));
	if (!str)
		return (NULL);
	while (s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	str[i++] = '/';
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

static char	**get_envp_path(char *envp[])
{
	static int		i;
	char			*all_path;
	char			**tab_path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_memcmp(envp[i], "PATH=", 5) == 0)
		{
			all_path = ft_strdup(envp[i] + 5);
			if (!all_path)
				return (NULL);
			tab_path = ft_split(all_path, ':');
			free(all_path);
			return (tab_path);
		}
		i++;
	}
	return (NULL);
}

static char	*find_cmd_path(char *cmd, char	*envp[])
{
	int		i;
	char	**path_tab;
	char	*path_cmd;

	i = 0;
	path_tab = get_envp_path(envp);
	if (!path_tab)
		return (NULL);
	while (path_tab[i] != NULL)
	{
		path_cmd = pathcmd_join(path_tab[i], cmd);
		if (!path_cmd)
		{
			free_all(path_tab);
			return (NULL);
		}
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			free_all(path_tab);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	return (free_all(path_tab));
}

static t_cmd	get_pathnames(char *argv, char *envp[])
{
	t_cmd	cmd;
	int		i;

	i = 0;
	cmd.args = NULL;
	cmd.pathname = NULL;
	cmd.args = ft_split(argv, ' ');
	if (!cmd.args || cmd.args[0] == NULL)
		return (cmd);
	if (ft_strchr(cmd.args[0], '/') != 0)
	{
		cmd.pathname = ft_strdup(cmd.args[0]);
		return (cmd);
	}
	cmd.pathname = find_cmd_path(cmd.args[0], envp);
	if (!cmd.pathname)
	{
		cmd.pathname = ft_strdup("empty");
		return (cmd);
	}
	return (cmd);
}

t_cmd	*fill_struct(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmd;
	int		i;
	int		j;

	i = 0;
	j = 2;
	cmd = malloc(sizeof(t_cmd) * (argc - 3));
	if (!cmd)
		exit_error("Malloc error\n");
	while (i < argc - 3)
	{
		cmd[i] = get_pathnames(argv[j], envp);
		i++;
		j++;
	}
	return (cmd);
}
