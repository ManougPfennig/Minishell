/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_working.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:04:09 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/16 21:58:17 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(t_cmds *cmd)
{
	int		i;

	i = 0;
	while (cmd->tab[i])
		i++;
	if (i > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (0);
}

void	ft_cd(t_cmds *cmd)
{
	if (print_error(cmd) == 1)
		return ;
	if (ft_strcmp(cmd->tab[1], "~") == 0)
	{
		chdir(cmd->data->home_env);
		cmd->data->buffercwd = getcwd(cmd->data->buffercwd, PATH_MAX);
		return ;
	}
	if (ft_strcmp(cmd->tab[1], "..") == 0)
	{
		chdir("..");
		cmd->data->buffercwd = getcwd(cmd->data->buffercwd, PATH_MAX);
		return ;
	}
	if (access(cmd->tab[1], F_OK) == 0)
	{
		chdir(cmd->tab[1]);
		cmd->data->buffercwd = getcwd(cmd->data->buffercwd, PATH_MAX);
		return ;
	}
	else if (access(cmd->tab[1], F_OK) == -1)
		printf("minishell: cd: %s: No such file or directory\n", cmd->tab[1]);
	return ;
}
