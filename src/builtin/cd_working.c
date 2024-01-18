/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_working.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:04:09 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/18 21:31:10 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(t_cmds *cmd)
{
	int		i;

	i = 0;
	if (!cmd->tab[1] && ft_strlen(cmd->data->home_env) == 0)
	{
		ft_putstr_fd("minishell: cd: HOME: is not set\n", 2);
		return (1);
	}
	while (cmd->tab[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	ft_cd(t_cmds *cmd)
{
	if (print_error(cmd) == 1)
		return (1);
	if ((!cmd->tab[1]))
	{
		chdir(cmd->data->home_env);
		return (0);
	}
	if (ft_strcmp(cmd->tab[1], "..") == 0)
	{
		chdir("..");
		return (0);
	}
	if (access(cmd->tab[1], F_OK) == 0)
	{
		chdir(cmd->tab[1]);
		return (0);
	}
	else if (access(cmd->tab[1], F_OK) == -1)
		putstr_fd_str("minishell: cd:", cmd->tab[1], ": No such file or \
		directory\n", 2);
	return (1);
}
