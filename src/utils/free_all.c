/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:00:32 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 21:41:30 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	multi_free(char *str, char *str2, char *str3)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	return (1);
}

void	free_exec(t_exec *exec)
{
		ft_free_tab(exec->path, exec->test);
		ft_free_tab(exec->env_tab, NULL);
		free(exec);
}

void	free_pipe_tab(t_data *data)
{
	int	i;

	i = 0;
	if (!data->pipe_tab)
		return ;
	while (data->pipe_tab[i] != NULL)
	{
		free(data->pipe_tab[i]);
		i++;
	}
	free(data->pipe_tab);
	data->pipe_tab = NULL;
}

void	free_pid_tab(t_data *data)
{
	if (data->pid_tab)
		free(data->pid_tab);
	data->pid_tab = NULL;
}

void	free_after_execution(t_data *data)
{
	t_cmds	*cmd;
	t_lexer	**redir_ptr;

	redir_ptr = NULL;
	cmd = data->cmd[0];
	free(data->cmd);
	free(data->builtins);
	free_pid_tab(data);
	free_pipe_tab(data);
	while (cmd)
	{
		redir_ptr = malloc(sizeof(t_lexer *));
		redir_ptr[0] = cmd->redir;
		free_lexer(redir_ptr);
		ft_free_tab(cmd->tab, cmd->builtin);
		if (cmd->exec)
			free_exec(cmd->exec);
		if (cmd->prev)
			free(cmd->prev);
		if (!cmd->next)
		{
			free(cmd);
			break ;
		}
		cmd = cmd->next;
	}
}

void	free_env_list(t_data *data)
{
	t_env	*ptr;
	t_env	*env;

	env = data->copy_env;
	while (env)
	{
		ptr = env;
		env = env->next;
		free_env(ptr);
	}
	free(data->home_env);
}
