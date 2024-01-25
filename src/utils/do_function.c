/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:11:06 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/25 13:28:20 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	do_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork");
	return (pid);
}

void	do_dup2(int fd, int fd2)
{
	int	ret;

	ret = dup2(fd, fd2);
	if (ret == -1)
		perror("dup2");
	return ;
}

int	do_dup(int fd)
{
	int	ret;

	ret = dup(fd);
	if (ret == -1)
		perror("dup");
	return (ret);
}

void	do_pipe(int pipe_fd[2])
{
	int	ret;

	ret = pipe(pipe_fd);
	if (ret == -1)
		perror("pipe");
	return ;
}

void	do_close(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
		perror("close");
	return ;
}
