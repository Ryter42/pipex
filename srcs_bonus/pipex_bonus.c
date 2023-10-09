/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:51:39 by elias             #+#    #+#             */
/*   Updated: 2023/09/25 13:47:59 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_data	*init(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->fd_tmp = 0;
	data->arg = NULL;
	data->cmd = NULL;
	data->path = addslash(env);
	data->av = av;
	data->env = env;
	data->ac = ac;
	data->heredoc = is_heredoc(av[1]);
	if (data->heredoc == 1)
	{
		data->limiteur = av[2];
		heredoc(data, ft_open_heredoc(data));
	}
	data->index = 2 + data->heredoc;
	return (data);
}

int	loopfork(t_data *data)
{
	data->pid = malloc(sizeof(pid_t) * (data->ac - 2));
	while (data->index <= data->ac - 2)
	{
		if (pipe(data->fd) < 0)
			return (0);
		data->pid[data->index - 2 - data->heredoc] = fork();
		if (data->pid[data->index - 2 - data->heredoc] < 0)
			return (0);
		if (data->pid[data->index - 2 - data->heredoc] == 0)
			exec(data);
		if (data->fd[1])
			close(data->fd[1]);
		if (data->fd_tmp)
			close(data->fd_tmp);
		data->fd_tmp = data->fd[0];
		waitpid(data->pid[data->index - 2 - data->heredoc], NULL, 0);
		data->index++;
	}
	close(data->fd_tmp);
	return (0);
}

void	ft_wait(t_data *data)
{
	while (data->index-- > 2 + data->heredoc)
	{
		waitpid(data->pid[data->index - 2 - data->heredoc], NULL, 0);
	}
	free(data->pid);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (ac < 5)
		return (ft_printf("Error arg\n"), 1);
	data = init(ac, av, env);
	loopfork(data);
	ft_free(data);
	unlink(".heredoc_tmp");
	return (0);
}
