/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:34:52 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 23:35:53 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipe_tab(t_data *data)
{
	int	i;

	i = 0;
	if (!data->pipe_tab)
		return ;
	while (data->pipe_tab[i] != NULL)
	{
		free(data->pipe_tab[i]);
		i++;
	}
	free(data->pipe_tab);
	data->pipe_tab = NULL;
}

void	free_pid_tab(t_data *data)
{
	if (data->pid_tab)
		free(data->pid_tab);
	data->pid_tab = NULL;
}

void	free_env_list(t_data *data)
{
	t_env	*ptr;
	t_env	*env;

	env = data->copy_env;
	while (env)
	{
		ptr = env;
		env = env->next;
		free_env(ptr);
	}
	free(data->home_env);
}
