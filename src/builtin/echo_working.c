/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_working.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:04:17 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/07 21:09:13 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmds *cmd)
{
	int		i;
	int		option;

	i = 1;
	option = 0;
	if (cmd->tab[i] && ft_strcmp(cmd->tab[1], "-n") == 0)
	{
		i++;
		option = 1;
	}
	if (cmd->tab[i] == NULL && option == 0)
	{
		write(1, "\n", 2);
		return ;
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
}