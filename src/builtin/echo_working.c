/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_working.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:04:17 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/18 17:59:40 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_condition(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (1);
	if (str[0] == '-' && str[1] != 'n')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(t_cmds *cmd)
{
	int		i;
	int		option;

	i = 1;
	option = 0;
	if (cmd->tab[i] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (cmd->tab[i] && check_condition(cmd->tab[i]) == 0)
	{
		i++;
		option = 1;
	}
	while (cmd->tab[i])
	{
		write(1, cmd->tab[i], ft_strlen(cmd->tab[i]));
		if (cmd->tab[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (option == 0)
		write(1, "\n", 2);
	return (0);
}
