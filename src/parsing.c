/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:08:24 by nicolas           #+#    #+#             */
/*   Updated: 2023/12/08 12:15:06 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exitcmd(char *s)
{
	if (ft_strcmp(s, "exit") == 0)
		exit(EXIT_FAILURE);
	else
		return ;
}

void	ft_pwd(t_data *data, char *s)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(s, ' ');
	while (tab[i])
		i++;
	if (i == 1 && ft_strcmp(tab[0], "pwd") == 0)
	{
		data->input = getcwd(data->input, PATH_MAX);
		s = data->input;
		printf("%s\n", data->input);
		return ;
	}
	else
		return ;
}

void	ft_analyse(t_data *data, char *s)
{
	(void)s;
	ft_exitcmd(data->input);
	//ft_env(data, s);
	ft_pwd(data, data->input);

}