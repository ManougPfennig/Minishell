/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:10:03 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 23:33:14 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*init-exec() alloue de la mémoire pour une structure t_exec, la remplie des
valeurs nécessaires à l'execution d'une commandes et return un pointeur vers
cette nouvelle structure.*/

t_exec	*init_exec(t_data *data)
{
	t_exec	*exec;
	char	*temp;

	exec = malloc(sizeof(t_exec));
	exec->fd_in = NO_FILE;
	exec->fd_out = NO_FILE;
	exec->pipe_in = NULL;
	exec->pipe_out = NULL;
	exec->test = NULL;
	exec->env_tab = env_to_tab(data);
	temp = get_env_patron_3000(data->copy_env, "PATH");
	exec->path = ft_split(temp, ':');
	free(temp);
	return (exec);
}

/*open_empty_fd() renvoie un file descriptor de lecture, vide.*/

int	open_empty_fd(void)
{
	int	pipe_fd[2];

	do_pipe(pipe_fd);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

/* executor va prendre la liste de commandes généré par le parser afin
de finalement exécuter la ou les commandes dans de nouveaux processes.
Une liste contenant une commande seule ira dans simple_command() pour être
exécuté au plus proche du process principal (exemple : exit mettra fin au
terminal, ce qui n'est pas le cas lorsqu'il est exécuté dans une pipeline).
Si la liste contient plusieurs commandes, alors elle ira dans
multiples_commands() et autant de processes que de commandes seront créé en
simultané, toutes reliées entre elles par des pipes (pipeline).
Le signal de retour de la dernière commande sera gardé comme signal final.

Les tokens heredoc sont gérés avant l'exécution dans handle_heredoc()*/

void	executor(t_data *data)
{
	if (handle_heredocs(data))
		return ;
	if (!data->cmd[0]->next)
	{
		if (check_input_list(data->cmd[0]) == NO_ERROR)
			simple_command(data, data->cmd[0]);
	}
	else
	{
		multiple_commands(data);
	}
	free_after_execution(data);
	printf("signal : %i\n", (g_sig % 256));
	return ;
}
