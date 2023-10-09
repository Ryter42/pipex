/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:38:55 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/25 11:18:01 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free(t_data *data)
{
	ft_wait(data);
	if (data->arg)
		free_tab(data->arg);
	if (data->cmd)
		free(data->cmd);
	if (data->path)
		free_tab(data->path);
	if (data)
		free(data);
}
