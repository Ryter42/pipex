/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:43:37 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/25 13:21:42 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_cmd(t_data *data)
{
	data->arg = ft_split(data->av[data->index], ' ');
	if (is_there_slash(data->av[data->index]) == 0)
	{
		data->file = findpath(data->path, data->arg[0], data);
		data->cmd = ft_strjoin(data->path[data->file], data->arg[0]);
	}
	else
		data->cmd = ft_strdup(data->av[data->index]);
}

void	firstcmd(t_data *data)
{
	int	fd;

	fd = ft_open(data);
	close(data->fd[0]);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("redir in");
		exit (EXIT_FAILURE);
	}
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		perror("redir out");
		exit(EXIT_FAILURE);
	}
	if (execve(data->cmd, data->arg, data->env) == -1)
	{
		perror(data->cmd);
		exit(EXIT_FAILURE);
	}
}

void	midlecmd(t_data *data)
{
	close(data->fd[0]);
	if (dup2(data->fd_tmp, STDIN_FILENO) == -1)
	{
		perror("redir in");
		exit (EXIT_FAILURE);
	}
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		perror("redir out");
		exit (EXIT_FAILURE);
	}
	if (execve(data->cmd, data->arg, data->env) == -1)
	{
		perror("data->cmd");
		exit(EXIT_FAILURE);
	}
}

void	lastcmd(t_data *data)
{
	int	fd;

	fd = open(data->av[data->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(data->fd[1]);
	if (dup2(data->fd_tmp, STDIN_FILENO) == -1)
	{
		perror("redir in");
		exit (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("redir out");
		exit (EXIT_FAILURE);
	}
	if (execve(data->cmd, data->arg, data->env) == -1)
	{
		perror(data->cmd);
		exit(EXIT_FAILURE);
	}
}

void	exec(t_data *data)
{
	get_cmd(data);
	if (data->index == 2 + data->heredoc)
		firstcmd(data);
	else if (data->index <= data->ac - 3)
		midlecmd(data);
	else
		lastcmd(data);
}
