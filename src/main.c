/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:32:13 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/07 23:12:15 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

void	init_data(t_data *data)
{
	data->input = NULL;
	data->buffercwd = NULL;
	data->sigint = 0;
	data->builtins = NULL;
	data->copy_env = NULL;
	data->home_env = NULL;
	data->buffersize = 0;
	data->pipes = 0;
	data->lex = NULL;
	data->cmd = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	init_data(data);
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
//		ft_exitcmd(data->input);
	}
	return (0);
}


//			 |||	
/*⠀⠀⠀⠀⠀⠀⠀⠀||||||⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀||||||||||⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⡆⠀⠀⠀⠀⠀⢢⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⢶⠆⠛⠁⠀⠸⢊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠨⠔⠀⠀⠔⢠⣏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣣⠙⠁⠀⢀⡆⢻⡶⡤⣄⣠⣤⣀⡀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⡠⠾⠙⣳⡶⠚⢹⠣⢀⢵⠾⢟⠉⠁⠓⠽⢷⡀⠀⠀
⠀⠀⠀⠀⢀⠤⠒⠓⠲⠶⡄⠈⠐⠒⠺⢶⣿⣗⠤⠀⢰⠀⠀⠀⠀⣧⠀⠀
⠀⠀⠀⢀⠃⠀⠀⠀⠀⠀⡃⠀⠀⠀⠐⠙⢻⡄⠀⠀⠘⣦⣄⠀⠐⠛⢆⠀
⠀⠀⢀⣌⠀⠀⠀⠀⠀⣼⠁⠀⠀⠀⠀⠒⠒⣿⠉⠀⠀⣿⢠⠀⠀⠀⠙⡆
⠀⡰⠋⠀⢀⠀⠈⠉⢻⣿⣦⡄⡀⠀⠀⠀⠴⣾⣏⣁⣠⣿⡈⣣⠀⢀⣇⢰
⠀⣇⡔⠀⠀⡇⣀⣀⣾⠃⠈⠛⠶⠶⣴⠶⠋⠁⢄⠈⠙⣿⡟⠁⠀⠀⠘⢈
⢰⡟⠀⠀⠐⢿⠻⣿⣯⡓⠂⠀⠀⠀⢸⠀⠀⠀⢘⣆⡠⠟⠓⠂⠀⢀⡠⠜
⢸⡟⣖⠀⠀⠀⠑⡘⢿⣿⡆⠀⢀⠤⠤⠤⣤⡤⠞⠉⠀⠀⣀⠠⡶⠋⠀⠀
⠀⠙⠮⣢⡤⣀⠀⠐⠠⣹⡇⢀⣋⡌⢀⡀⠀⠀⣀⣄⣀⠥⠐⠊⠀⠀⠀⠀
⠀⠀⠀⠈⠉⠓⠧⣤⣄⠀⠉⠁⠐⢌⡹⣿⡶⠾⡟⠁⣿⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣆⡀⠀⠤⢰⢿⡄⠀⠁⠀⡿⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢰⠟⠉⠉⠛⣶⣶⣷⠈⠺⠆⠀⢠⣧⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠘⠛⠛⠓⠀⠀⠀⠈⠙⠂⠀⠀⠀⠀⠀⠀*/
// Biblically accurate npatron
