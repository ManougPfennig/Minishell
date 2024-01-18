/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:30:38 by npatron           #+#    #+#             */
/*   Updated: 2024/01/18 22:11:25 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error_env(char *str)
{
	write(2, "bash: export: `", 15);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}

int	check_var(char *str)
{
	int	i;

	i = 1;
	if (ft_strlen(str) == 0)
		return (print_error_env(""));
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
