/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:32:18 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/26 00:55:37 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signal(void)
{
	signal(SIGINT, ft_controlc);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_controlc(int signal)
{
	if (g_sig == IN_HD)
	{
		write(STDERR_FILENO, "\n", 1);
		g_sig = CTRL_C_HD;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig = 130;
	(void)signal;
}

void	ft_prompt(t_data *data)
{
	data->home_env = get_env_patron_3000(data->copy_env, "HOME");
	data->input = NULL;
	data->input = readline("minishell> ");
	if (data->input == NULL)
	{
		data->exit = 1;
		return ;
	}
	add_history(data->input);
	data->lex = lexer(data, data->input);
	if (data->lex)
	{
		if (parser(data))
			executor(data);
		free_lexer(data->lex);
	}
	free(data->input);
	if (data->exit == 0)
		free(data->home_env);
	return ;
}
