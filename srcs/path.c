/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:41:05 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/25 13:22:48 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*pathenv(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	return (env[i] + 5);
}

int	is_there_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	**addslash(char **env)
{
	char	**path;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(pathenv(env), ':');
	path = malloc(sizeof(char *) * (strllen(tmp) + 1));
	while (tmp[i])
	{
		path[i] = ft_strjoin(tmp[i], "/");
		i++;
	}
	path[i] = NULL;
	free_tab(tmp);
	return (path);
}

int	findpath(char **path, char *cmd, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, F_OK) == 0)
			return (free(tmp), i);
		free(tmp);
		i++;
	}
	ft_printf("%s : command not found\n", cmd);
	close(data->fd[1]);
	close(data->fd[0]);
	close(data->fd_tmp);
	ft_free(data);
	exit(EXIT_FAILURE);
	return (-1);
}
