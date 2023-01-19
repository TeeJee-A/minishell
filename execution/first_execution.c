/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:54:02 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 10:32:00 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"
#include "../includes/minishell.h"

int	check_access_file(t_execlst *el)
{
	while (el && el->red)
	{
		if (el->red->fd == -1)
		{
			printf("%s\n", strerror(el->red->__errno));
			return (-1);
		}
		if (!el->red->next)
			return (el->red->fd);
		el->red = el->red->next;
	}
	return (0);
}

void	dup_function(int fd_out, int fd_in)
{
	if (fd_out != -1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
	if (fd_in != -1)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
}

int	ft_red(t_execlst *el, int *dup1, int *dup0)
{
	int	fd_out;
	int	fd_in;

	*dup1 = dup(1);
	*dup0 = dup(0);
	fd_out = -1;
	fd_in = -1;
	while (el->red)
	{
		if (el->red->fd < 0)
			return (-1);
		if (el->red->type == 6 || el->red->type == 8)
			fd_out = el->red->fd;
		if (el->red->type == 5 || el->red->type == 7)
			fd_in = el->red->fd;
		el->red = el->red->next;
	}
	dup_function(fd_out, fd_in);
	return (0);
}

void	ft_pipe(t_execlst *el, int __pipe[2])
{
	if (el->next)
	{
		if (pipe(__pipe) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
}

void	execve_function(t_execlst *el)
{
	int	pid;
	int	__pipe[2];

	while (el)
	{
		ft_pipe(el, __pipe);
		pid = fork();
		if (pid < 0)
			return (perror("fork"));
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			cmd(el, __pipe);
		}
		postexec(el, __pipe);
		el = el->next;
	}
}
