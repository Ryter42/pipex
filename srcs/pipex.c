/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:51:39 by elias             #+#    #+#             */
/*   Updated: 2023/07/02 17:11:39 by elias            ###   ########.fr       */
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

t_data	*init(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->path = addslash(env);
	data->av = av;
	data->env = env;
	data->ac = ac;
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

int	loopfork(t_data *data)
{
	int	file;
	// int	i;

	// i = 0;
	file = findpath(data->path, data->av[1]);
	printf("%s\n", data->path[file]);
	// if (pipe(data->fd) < 0)
	// 	return (0);
	// while (i < ac - 1)
	// {

	// 	data->pid = fork();
	// 	if (data->pid == 0)
	// 	{
	// 		execve()
	// 	}
	// }
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

	//test

}
