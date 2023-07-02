/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:30:36 by elias             #+#    #+#             */
/*   Updated: 2023/07/02 17:09:53 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/includes/libft.h"

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**env;
	char	**path;
	int		fd[2];
	pid_t	pid;
}	t_data;

#endif
