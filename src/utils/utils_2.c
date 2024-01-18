/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:30:38 by npatron           #+#    #+#             */
/*   Updated: 2024/01/18 17:34:34 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_env(char *str)
{
	write(1, "bash: export: '", 15);
	write(1, str, ft_strlen(str));
	write(1, "': not a valid identifier\n", 27);
}

int	check_var(char *str)
{
	int	i;

	i = 1;
	if ((str[0] >= '!' && str[0] <= '/')
		|| (str[0] >= ':' && str[0] <= '?')
		|| (str[0] >= '0' && str[0] <= '9')
		|| str[0] == '=')
	{
		print_error_env(str);
		return (1);
	}
	while (str[i])
	{
		if ((str[i] >= '!' && str[i] <= '/')
			|| (str[i] >= ':' && str[i] <= '<')
			|| (str[i] >= '>' && str[i] <= '?'))
		{
			print_error_env(str);
			return (1);
		}
		i++;
	}
	return (0);
}
