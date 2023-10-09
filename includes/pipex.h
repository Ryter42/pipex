/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:30:36 by elias             #+#    #+#             */
/*   Updated: 2023/09/25 13:27:58 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/includes/libft.h"
# include <sys/wait.h>

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**env;
	char	**path;
	int		fd[2];
	pid_t	*pid;
	int		index;
	int		file;
	char	*cmd;
	char	**arg;
	int		fd_tmp;
	int		heredoc;
	char	*limiteur;
}	t_data;

t_data	*init(int ac, char **av, char **env);
int		loopfork(t_data *data);
void	get_cmd(t_data *data);
void	firstcmd(t_data *data);
void	midlecmd(t_data *data);
void	lastcmd(t_data *data);
void	exec(t_data *data);
char	*pathenv(char **env);
int		is_there_slash(char *str);
char	**addslash(char **env);
int		findpath(char **path, char *cmd, t_data *data);
void	ft_free(t_data *data);
void	free_tab(char **tab);
int		is_heredoc(char *str);
void	heredoc(t_data *data, int fd);
int		ft_open(t_data *data);
int		ft_open_heredoc(t_data *data);
void	ft_wait(t_data *data);

#endif
