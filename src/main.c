/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:32:13 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/12 13:56:39 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

void	init_data(t_data *data)
{
	data->input = NULL;
	data->buffercwd = NULL;
	data->sigint = 0;
	data->init_env = 0;
	data->env_export = NULL;
	data->builtins = NULL;
	data->copy_env = NULL;
	data->new_copy_env = NULL;
	data->copy_env = NULL;
	data->home_env = NULL;
	data->buffersize = 0;
	data->pipes = 0;
	data->lex = NULL;
	data->cmd = NULL;
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	init_data(data);
	(void)argv;
	get_env(env, data);
	init_export_tab(data);
	if (argc != 1)
	{
		printf("Error\n");
		exit(0);
	}
	g_sig = 0;
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
