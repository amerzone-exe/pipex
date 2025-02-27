/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:30:24 by jpiquet           #+#    #+#             */
/*   Updated: 2025/02/27 17:08:29 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void	write_error(void)
{
	perror("Error");
	exit (1);
}

void	free_tab_struct(t_cmd *cmd, int argc)
{
	int i;

	i = 0;
	while (i < argc - 3) 
	{
		if (cmd[i].pathname)
			free(cmd[i].pathname);
		if (cmd[i].args)
			free_all(cmd[i].args);
		i++;
	}
	if (cmd)
		free(cmd);
}

/*----Join le path avec la commande----*/

char	*pathcmd_join(char *s1, char *s2)
{
	size_t	tlen;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	tlen = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (tlen + 2));
	if (str == 0)
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

/*----Récuperer et stocker dans un tableau de string de chaque path independament----*/

char **get_envp_path(char *envp[])
{
	static int		i;
	char			*all_path;
	char			**tab_path;

	i = 0;
	while(envp[i] != NULL)
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

/*----III.Tester la commande avec chaques path recupéré et renvoyer une string contenant "path/cmd" | 
			Renvoyer NULL si aucun path ne fonctionne avec la commande ----*/

char	*find_cmd_path(char *cmd, char	*envp[])
{
	int		i;
	char	**path_tab;
	char	*path_cmd;

	i = 0;
	path_tab = get_envp_path(envp);
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
	free_all(path_tab);
	return (NULL);
}

/*----II.Récuperer et stocker dans une structure 
1/ le bon path de la commande dans "pathname" 
2/ La commande + ses options dans "args"----*/

t_cmd	get_pathnames(char *argv, char *envp[])
{
	t_cmd	cmd;
	int		i;

	i = 0;
	cmd.args = NULL;
	cmd.pathname = NULL;
	cmd.args = ft_split(argv, ' ');
	if (!cmd.args)
		return (cmd);
	cmd.pathname = find_cmd_path(cmd.args[0], envp);
	if (!cmd.pathname)
		return (cmd);
	return (cmd);
}

/*----I.Remplir chaques structures de mon tableau de struct, en faisant une commande une structure----*/

t_cmd	*fill_struct(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmd;
	int		i;
	int		j;

	i = 0;
	j = 2;
	cmd = malloc(sizeof(t_cmd) * argc - 3);
	cmd[argc - 2] = (t_cmd){.pathname = NULL, .args = NULL};
	if (!cmd)
		write_error();
	while (i < argc - 3) 
	{
		cmd[i] = get_pathnames(argv[j], envp);
		if (!cmd || !cmd[i].args || !cmd[i].pathname)
		{
			free_tab_struct(cmd, argc);
			write_error();
		}
		i++;
		j++;
	}
	return (cmd);
}

/*Récuperer le fd de chaques files et verifier son accessibilité*/

void	checkfiles(int argc, char *argv[])
{
	int	infile;
	int	outfile;

	outfile = open(argv[argc - 1], O_WRONLY);
	if (outfile < 1)
	{
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT, 00444 | 00244);
		if (outfile < 1)
		{
			perror("Open error");
			return ;
		}
	}
	infile = open(argv[1], O_RDONLY);
	if (infile < 1)
	{
		perror("Open error");
		close(outfile);
		return ;
	}
}

//int	pipex();

int main(int argc, char *argv[], char *envp[]) 
{
	t_cmd	*cmd;

	if (argc < 5)
	 	write_error();
	cmd = fill_struct(argc, argv, envp);
	for (int i = 0; i < argc - 3; i++)
	{
		printf("cmd[%d] pathname = %s\n", i, cmd[i].pathname);
	}
	for (int i = 0; i < argc - 3; i++)
	{
		int j = 0;
		while (cmd[i].args[j] != NULL)
		{
			printf("cmd[%d] args[%d] = %s\n", i, j, cmd[i].args[j]);
			j++;
		}
	}
	free_tab_struct(cmd, argc);
	// checkfiles(argc, argv);
	// argv[argc] = NULL;
	// argv += 2;
	//execve(tab_path[0], tab_path, envp);
	// printf("argv[0] = %s\n", argv[0]);
	// printf("argv[1] = %s\n", argv[1]);
	// printf("argv[2] = %s\n", argv[2]);
	// for (int i = 0; i < argc - 3; i++)
	// 	printf("cmd %d = %s\n", i, tab_path[i]);
	// printf("tab_path[0] = %s\n", tab_path[0]);
	//printf("execve = %d\n", execve(tab_path[0], tab_path, envp));
	return 0;
}

/*-------------------------------------------------------*/


// int	main(int argc, char *argv[])
// {
// 	int fd_old;
// 	int fd_new;
// 	int fd_dup;
// 	char *line_old;
// 	char *line_new;

// 	//char *line_dup;

// 	(void)argc;
// 	fd_old = open(argv[1], O_RDONLY);
// 	fd_new = open(argv[2], O_RDONLY);
// 	//test = access("test.txt", R_OK);
// 	printf("---------------------\n");

// 	printf("fd original : %d\n", fd_old);
// 	printf("fd_new : %d\n\n", fd_new);

// 	printf("---------------------\n");

// 	line_old = get_next_line(fd_old);
// 	printf("line original fd : %s\n", line_old);

// 	line_new = get_next_line(fd_new);
// 	printf("line_new fd : %s\n\n", line_new);

// 	printf("---------MAKE DUP2------------\n\n");

// 	fd_dup = dup2(fd_old, fd_new);
// 	line_new = get_next_line(fd_new);
// 	printf("line_new fd : %s\n\n", line_new);
// 	//fd_dup = dup2(fd_old, fd_new);

// 	// printf("fd dup : %d\n\n", fd_old);

// 	// line_dup = get_next_line(fd_dup);
// 	// printf("line_dup fd : %s\n", line_dup);

// 	return 0;
// }

/*-------------------------------------------------------*/

// int main(int argc, char *argv[])
// {
//     (void)argc;
//     (void)argv;

//     int fd_old = open("oldfd.txt", O_RDWR);
//     if (fd_old == -1) {
//         perror("open");
//         return 1;
//     }

//     printf("Avant dup2 : Ceci va s'afficher dans le terminal.\n");

//     // Rediriger stdout (1) vers fd_old
//     dup2(fd_old, STDOUT_FILENO);

//     // Maintenant, tout ce qui est écrit sur stdout va dans "oldfd.txt"
//     printf("ALLO\n");

//     close(fd_old);
//     return 0;
// }
