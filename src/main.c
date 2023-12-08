/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:32:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/12/01 22:40:42 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	(void)argv;
	get_env(env, data);
	if (argc != 1)
	{
		printf("Error\n");
		exit(0);
	}
	while (1)
	{
		ft_prompt(data);
		ft_exitcmd(data->input);
	}
	return (0);
}
