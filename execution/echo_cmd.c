/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:38:47 by ataji             #+#    #+#             */
/*   Updated: 2022/11/17 16:06:43 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"
#include "../includes/minishell.h"

int	echo_heredc(t_execlst *el)
{
	int		i;
	int		j;
	int		n;
	t_red	*red;

	red = el->red;
	n = 1;
	while (el->cmd[n] && !my_strcmp(el->cmd[n], "-n"))
		n++;
	i = n;
	while (el->cmd[i])
	{
		j = 0;
		while (el->cmd[i][j])
		{
			write(1, &el->cmd[i][j], 1);
			j++;
		}
		i++;
		if (el->cmd[i])
			write(1, " ", 1);
	}
	if (n == 1)
		write(1, "\n", 1);
	return (1);
}

int	red_in_echo(t_execlst *el)
{
	t_red	*red;

	red = el->red;
	if (red->type == HEREDC || red->type == REDIN)
	{
		echo_heredc(el);
		return (1);
	}
	return (0);
}

int	red_out_echo(t_execlst *el, int i)
{
	t_red	*red;
	int		j;

	red = el->red;
	while (el->cmd[++i])
	{
		j = 0;
		while (el->cmd[i][j])
			write(red->fd, &el->cmd[i][j++], 1);
		if (el->cmd[i])
			write(red->fd, " ", 1);
	}
	return (0);
}

int	red_echo(t_execlst *el)
{
	int		i;
	int		n;
	t_red	*red;

	n = 1;
	red = el->red;
	while (el->cmd[n] && !my_strcmp(el->cmd[n], "-n"))
		n++;
	i = n - 1;
	if (red->type == APPND || red->type == REDOUT)
		if (red_out_echo(el, i))
			return (1);
	if (red_in_echo(el))
		return (1);
	if (n == 1)
		write(red->fd, "\n", 1);
	return (1);
}

int	echo_cmd(t_execlst *el)
{
	int		k;
	t_red	*red;

	red = el->red;
	if (red && red->fd)
		return (red_echo(el));
	k = 1;
	if (!(my_strcmp(el->cmd[k], "-n")))
	{
		while (el->cmd[k] && !my_strcmp(el->cmd[k], "-n"))
			k++;
		if (el->cmd && el->cmd[2] == NULL)
			return (1);
		k = k - 1;
		while (el->cmd[++k])
		{
			if (!(el->cmd[k + 1]))
				return (printf("%s", el->cmd[k]), 1);
			if (el->cmd[k])
				printf("%s ", el->cmd[k]);
		}
	}
	else
		print_echo(el);
	return (1);
}
