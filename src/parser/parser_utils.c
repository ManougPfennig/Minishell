/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:53:42 by nicolas           #+#    #+#             */
/*   Updated: 2024/01/11 20:59:09 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// La variable pipes permettra de savoir combien de maillons
// de la struct Parser on aura besoin.
// Ex : cd .. | echo "manouglebgdelastreet" data->pipes = 1
// Ex : cd .. ---> data->pipes = 0
// ALors on aura data->pipes + 1 maillon(s).
void	nb_pipes(t_data *data)
{
	t_lexer	*ptr;
	int		i;

	i = 0;
	ptr = data->lex[0];
	while (ptr)
	{
		if (ptr->token == 3)
			i++;
		ptr = ptr->next;
	}
	data->pipes = i;
}

int	check_error_lexer(t_data *data)
{
	t_lexer	*ptr;
	int		i;

	i = 0;
	ptr = data->lex[0];
	if (!ptr)
		return (1);
	if (ptr->token == 3)
	{
		printf("minishell: syntax error near `|'\n");
		return (1);
	}
	while (ptr)
	{
		if (ptr->token && !ptr->next && ++i)
			printf("minishell: syntax error near `%s'\n", ptr->str);
		else if (ptr->token != 0 && ptr->token != PIPE && \
		ptr->next->token != 0 && ++i)
			printf("minishell: syntax error near `%s'\n", ptr->next->str);
		else if (ptr->token == PIPE && ptr->next && \
		ptr->next->token == PIPE && ++i)
			printf("minishell: syntax error near `%s'\n", ptr->next->str);
		else if (ptr->token == PIPE && !ptr->next && ++i)
			printf("minishell: syntax error near `|'\n");
		if (i)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	add_back_cmds(t_data *data, t_cmds *new)
{
	t_cmds	*ptr;

	if (!data->cmd[0])
		data->cmd[0] = new;
	else
	{
		ptr = data->cmd[0];
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
}

void	init_cmd_list(t_data *data)
{
	t_cmds	*temp;
	int		i;

	data->cmd = malloc(sizeof(t_cmds *));
	data->cmd[0] = NULL;
	i = 0;
	nb_pipes(data);
	while (i <= data->pipes)
	{
		temp = malloc(sizeof(t_cmds));
		temp->tab = NULL;
		temp->builtin = NULL;
		temp->num_redir = 0;
		temp->hd_file_name = NULL;
		temp->redir = NULL;
		temp->exec = NULL;
		temp->next = NULL;
		temp->prev = NULL;
		temp->data = data;
		add_back_cmds(data, temp);
		temp = NULL;
		i++;
	}
}
