/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:10:03 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/05 16:54:08 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_data *data)
{
	if (find_heredocs(data))
		return (1);
	printf("------------------\n");
	print_cmd_list(data);
	return (0);
}