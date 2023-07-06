/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:51:39 by elias             #+#    #+#             */
/*   Updated: 2023/07/05 19:56:14 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*pathenv(char **env)
{
	int	i;

	i = 0;
	
	while (strncmp(env[i], "PATH", 4) != 0)
		i++;
	return (env[i]);
}

char	*suppath(char **env)
{
	char	*path;
	char	*tmp;
	int	i;
	int	d;

	d = 0;
	i = 5;
	tmp = pathenv(env);
	path = malloc(sizeof(char) * ft_strlen(tmp) - 5);
	while (tmp[i])
	{
		path[d] = tmp[i];
		i++;
		d++;
	}
	return (path);
}

int	strllen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**addslash(char **env)
{
	char	**path;
	char	**tmp;
	int		i;
	int		size;

	i = 0;
	tmp = ft_split(suppath(env), ':');
	path = malloc(sizeof(char *) * strllen(tmp));
	while (tmp[i])
	{
		size = ft_strlen(tmp[i]);
		path[i] = malloc(sizeof(char) * size + 1);
		ft_strlcpy(path[i], tmp[i], size + 1);
		path[i][size] = '/';
		// path[i][size + 1] = '\n';
		i++;
	}
	return (path);
}

int	**create_tab_fd(int size)
{
	int	**fd;
	int	i;

	i = 0;
	fd = malloc(sizeof(int **) * (size + 1));
	if (!fd)
		return (NULL);
	while (i < size)
	{
		fd[i] = malloc(sizeof(int *) * 2);
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

t_data	*init(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->fd = create_tab_fd(ac - 3);
	data->path = addslash(env);
	data->av = av;
	data->env = env;
	data->ac = ac;
	data->index = 2;
	return (data);
}

int	findpath(char **path, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while(path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, F_OK) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	get_cmd(t_data *data)
{
	data->file = findpath(data->path, data->av[data->index]);
	data->cmd = ft_strjoin(data->path[data->file], data->av[data->index]);
	data->arg = ft_split(data->av[data->index], ' ');
}

void	firstcmd(t_data *data)
{
	int fd;

	data->file = findpath(data->path, data->av[data->index]);
	data->cmd = ft_strjoin(data->path[data->file], data->av[data->index]);
	data->arg = ft_split(data->av[data->index], ' ');
	fd = open(data->av[1], O_RDONLY);
	close(data->fd[data->index - 2][0]);
	dup2(fd, STDIN_FILENO);
	dup2(data->fd[data->index - 2][1], STDOUT_FILENO);
	dprintf(2, "arg = %s\n", data->arg[0]);
	dprintf(2, "arg = %s\n", data->arg[1]);
	dprintf(2, "data->cmd = %s\n", data->cmd);
	execve(data->cmd, data->arg, data->env);	
}

void	midlecmd(t_data *data)
{
	data->file = findpath(data->path, data->av[data->index]);
	data->cmd = ft_strjoin(data->path[data->file], data->av[data->index]);
	data->arg = ft_split(data->av[data->index], ' ');
	close(data->fd[data->index - 3][1]);
	close(data->fd[data->index - 2][0]);
	dup2(data->fd[data->index - 1][0], STDIN_FILENO);
	dup2(data->fd[data->index - 2][1], STDOUT_FILENO);
	dprintf(2, "%s\n", data->arg[0]);
	dprintf(2, "%s\n", data->arg[1]);
	dprintf(2, "data->cmd = %s\n", data->cmd);
	execve(data->cmd, data->arg, data->env);
}

void	lastcmd(t_data *data)
{
	int fd;

	data->file = findpath(data->path, data->av[data->index]);
	data->cmd = ft_strjoin(data->path[data->file], data->av[data->index]);
	data->arg = ft_split(data->av[data->index], ' ');
	fd = open(data->av[data->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(data->fd[data->index - 3][1]);
	close(data->fd[data->index - 2][0]);
	dup2(data->fd[data->index - 1][0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dprintf(2, "test");
	dprintf(2, "arg = %s\n", data->arg[0]);
	dprintf(2, "arg = %s\n", data->arg[1]);
	dprintf(2, "data->cmd = %s\n", data->cmd);
	execve(data->cmd, data->arg, data->env);	
}

void	exec(t_data *data)
{
	get_cmd(data);
	printf("index = %d\n", data->index);
	// printf("commande numero %d\n", data->ac - 3);
	// printf("nombre commande %d\n", data->ac - 3);
	if (data->index == 2)
	{
		printf("firstcmd\n");
		firstcmd(data);
	}
	else if (data->index <= data->ac - 3)
	{
		printf("midlecmd\n");
		midlecmd(data);
	}
	else
	{
		printf("lastcmd\n");
		lastcmd(data);
	}
}


int	loopfork(t_data *data)
{
	int	status;

	while (data->index <= data->ac - 2)
	{
		if (pipe(data->fd[data->index - 2]) < 0)
			return (0);
		data->pid = fork();
		if (data->pid < 0)
			return (0);
		if (data->pid == 0)
		{
			// printf("fork ok\n");
			exec(data);
		}
		else
		{
			close(data->fd[data->index - 2][1]);
			if (data->index != 2)
				close(data->fd[data->index - 3][0]);
			waitpid(data->pid, &status, 0);
			data->index++;
		}

	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = init(ac, av, env);
	loopfork(data);
	// file = findpath(data->path, av[1]);
	// printf("%s\n", data->path[file]);
	// int i = 0;
	// while(data->path[i])
	// {
	// 	printf("%s\n", data->path[i]);
	// 	i++;
	// }

	//test1n

}
