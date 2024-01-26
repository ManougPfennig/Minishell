/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:41:37 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/26 01:10:14 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*input_fd() va ouvrir le dernier fichier d'input de la liste de
redirections de la commande puis return un file descriptor vers ce
fichier (heredoc compris).*/

int	input_fd(t_cmds *cmd)
{
	int		fd;
	t_lexer	*input;

	input = lexer_last_input(cmd->redir);
	if (input)
		fd = get_input_fd(input, cmd);
	else
		fd = NO_FILE;
	return (fd);
}

/*output_fd() va ouvrir le dernier fichier d'output de la liste de
redirections de la commande puis return un file descriptor vers ce
fichier.*/

int	output_fd(t_cmds *cmd)
{
	int		fd;
	t_lexer	*output;

	output = lexer_last_output(cmd->redir);
	if (output)
		fd = get_output_fd(output);
	else
		fd = NO_FILE;
	return (fd);
}

/*check_tab() permet d'exit avec un signal de 0, je l'ai mis dans un
if() purement parce-que la norme des 25 lignes.*/

int	check_tab(t_cmds *cmd)
{
	if (!cmd->tab)
		exit(EXIT_SUCCESS);
	return (1);
}

/*command_execution() va tourner en boucle sur tout les chemins existants de
la variable d'environnement PATH (si il s'agit d'un chemin réel, la commande
sera testée telle que dans execve()) afin de trouver un chemin correspondant
pour la commande. Si la fonction n'en trouve pas, elle affiche un message
d'erreur sur STDERR et exit avec le signal 127.*/

int	command_execution(t_cmds *cmd, t_exec *exec)
{
	pid_t	pid;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		if (check_tab(cmd) && is_direct_execution(cmd->tab[0]))
			execve(cmd->tab[0], cmd->tab, exec->env_tab);
		while (exec->path && exec->path[i])
		{
			exec->test = ft_strjoin_free(exec->path[i], "/", 0);
			exec->test = ft_strjoin_free(exec->test, cmd->tab[0], 1);
			if (execve(exec->test, cmd->tab, exec->env_tab) == -1)
				i++;
			ft_free_tab(NULL, exec->test);
		}
		putstr_fd_str(cmd->tab[0], ": command not found\n", NULL, 2);
		exit(127);
	}
	wait(&ret);
	return (ret % 255);
}

/*simple_command() va changer STDIN ou STDOUT en fonction des fichiers de
redirections donné à la commande (si il y en a), exécuter la commande
(avec command_execution() ou which_cmd() si il s'agit d'un builtin),
récupérer le signal de retour puis changer STDIN et STDOUT de nouveau pour
que Minishell continue de s'exécuter normalement.*/

void	simple_command(t_data *data, t_cmds *cmd)
{
	int		fd_in;
	int		fd_out;

	cmd->exec = init_exec(data);
	fd_in = input_fd(cmd);
	fd_out = output_fd(cmd);
	if (fd_in != NO_FILE)
		do_dup2(fd_in, STDIN_FILENO);
	if (fd_out != NO_FILE)
		do_dup2(fd_out, STDOUT_FILENO);
	if (cmd->builtin)
		g_sig = which_cmd(cmd);
	else
		g_sig = command_execution(cmd, cmd->exec);
	do_dup2(data->std_in, STDIN_FILENO);
	do_dup2(data->std_out, STDOUT_FILENO);
	if (fd_in != NO_FILE)
		close(fd_in);
	if (fd_out != NO_FILE)
		close(fd_out);
}
