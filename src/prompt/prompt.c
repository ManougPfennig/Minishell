/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:32:18 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/16 20:27:28 by mapfenni         ###   ########.fr       */
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

char	*ft_prompt(t_data *data)
{
	ft_signal();
	data->input = NULL;
	data->input = readline("minishell> ");
	if (data->input == NULL)
	{
		printf("quit\n");
		exit(0);
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
	return (NULL);
}

int	get_env(char **env, t_data *data)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	data->env_export = malloc(sizeof(char *) * (i + 1));
	data->copy_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		data->copy_env[i] = ft_strdup(env[i]);
		data->env_export[i] = ft_addstring("declare -x ", var_env_export(env[i]));
		i++;
	}
	data->copy_env[i] = NULL;
	data->env_export[i] = NULL;
	if (len_tab(data->copy_env) == 0)
		return (1);
	return (0);
}
