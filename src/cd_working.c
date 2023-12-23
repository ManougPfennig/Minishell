/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_working.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:04:09 by nicolas           #+#    #+#             */
/*   Updated: 2023/12/23 14:11:55 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_tild_cd(t_data *data, char *s)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(s, ' ');
	while (tab[i])
		i++;
	if (i == 2 && ft_strcmp(tab[0], "cd") == 0
		&& ft_strcmp(tab[1], "~") == 0)
	{
		chdir(data->home_env);
		data->buffercwd = getcwd(data->buffercwd, PATH_MAX);
		return ;
	}
	else if (i == 2 && ft_strcmp(tab[0], "cd") == 0
		&& access(tab[1], F_OK) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", tab[1]);
		return ;
	}
	return ;
}

void	get_home_env(t_data *data)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (data->copy_env[i])
	{
		if (strncmp(data->copy_env[i], "HOME=", 5) == 0)
			break ;
		i++;
	}
	while (data->copy_env[i][j])
		j++;
	data->home_env = malloc(sizeof(char) * j - 5);
	j = 5;
	while (data->copy_env[i][j])
	{
		data->home_env[k] = data->copy_env[i][j];
		k++;
		j++;
	}
}

void	ft_cd(t_data *data, char *s)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(s, ' ');
	data->buffercwd = getcwd(data->buffercwd, PATH_MAX);
	while (tab[i])
		i++;
	if (i == 2 && ft_strcmp(tab[0], "cd") == 0
		&& ft_strcmp(tab[1], "..") == 0)
	{
		chdir("..");
		data->buffercwd = getcwd(data->buffercwd, PATH_MAX);
		return ;
	}
	else if (i == 2 && ft_strcmp(tab[0], "cd") == 0
		&& access(tab[1], F_OK) == 0)
	{
		chdir(tab[1]);
		data->buffercwd = getcwd(data->buffercwd, PATH_MAX);
		return ;
	}
	print_error_tild_cd(data, s);
}
