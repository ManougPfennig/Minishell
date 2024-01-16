/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_get_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:11:26 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/16 12:35:02 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_to_fd(char *str)
{
	pid_t	pid;
	int		pipefd[2];
	int		fd;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		write(pipefd[1], str, ft_strlen(str));
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		wait(NULL);
		close(pipefd[1]);
		fd = dup(pipefd[0]);
		close(pipefd[0]);
	}
	return (fd);
}

int	is_output_in_other_cmd(t_lexer *input, t_cmds *cmd)
{
	t_lexer	*other;

	cmd = cmd->next;
	while (cmd)
	{
		other = lexer_last_output(cmd->redir);
		if (other && ft_strcmp(other->str, input->str) && other->token == 2)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	get_input_fd(t_lexer *input, t_cmds *cmd)
{
	int	fd;

	if (input->token == LESS_THAN)
	{
		if (is_output_in_other_cmd(input, cmd))
			fd = open(input->str, O_RDONLY | O_TRUNC);
		else
			fd = open(input->str, O_RDONLY);
	}
	else if (input->token == LESS_LESS)
		fd = str_to_fd(input->str);
	return (fd);
}

int	get_output_fd(t_lexer *output)
{
	int	fd;

	if (output->token == MORE_THAN)
		fd = open(output->str, O_WRONLY | O_TRUNC);
	else if (output->token == MORE_MORE)
		fd = open(output->str, O_WRONLY | O_APPEND);
	return (fd);
}