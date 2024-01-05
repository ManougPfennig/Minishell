/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:32:18 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/05 16:38:54 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(void)
{
	signal(SIGINT, ft_controlc);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_controlc(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

char	*ft_prompt(t_data *data)
{
	ft_signal();
	data->input = readline("minishell> ");
	data->line_count++;
	if (data->input == NULL)
	{
		printf("quit\n");
		exit(0);
	}
	add_history(data->input);
	data->lex = lexer(data->input);
	if (data->lex)
	{
// 		print_lexer à enlever
		print_lexer(data->lex);
		if (parser(data))
			executor(data);
//		ft_analyse(data, data->input);
		free_lexer(data->lex);
	}
	return (data->input);
}

char	**get_env(char	**env, t_data *data)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	data->copy_env = malloc(sizeof(char *) * i);
	i = 0;
	while (env[i])
	{
		data->copy_env[i] = ft_strdup(env[i]);
		i++;
	}
	get_home_env(data);
	return (data->copy_env);
}
