/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_working.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:16:58 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/18 18:16:35 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_digit(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_cmds *cmd)
{
	int	i;

	i = 0;
	
	
}
