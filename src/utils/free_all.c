/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:00:32 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/18 21:33:33 by mapfenni         ###   ########.fr       */
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
	free(exec);
}

void	free_after_execution(t_data *data, t_exec *exec)
{
	t_cmds	*cmd;
	t_lexer	**redir_ptr;

	redir_ptr = NULL;
	cmd = data->cmd[0];
	free(data->cmd);
	free_exec(exec);
	free(data->builtins);
	while (cmd)
	{
		redir_ptr = malloc(sizeof(t_lexer *));
		redir_ptr[0] = cmd->redir;
		free_lexer(redir_ptr);
		ft_free_tab(cmd->tab, cmd->builtin);
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
