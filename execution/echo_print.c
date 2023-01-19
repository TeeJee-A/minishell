/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 00:07:27 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 13:09:46 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"

void	print_echo_n(t_execlst *el, int j)
{
	int	i;

	i = j;
	while (el->cmd[i])
	{
		printf("%s", el->cmd[i]);
		if (el->cmd[i])
			printf(" ");
		i++;
	}
}

int	red_in_echo(t_execlst *el)
{
	t_red	*red;

	red = el->red;
	if (red->type == HEREDC || red->type == REDIN)
	{
		echo_heredc(el, 0, 0, 0);
		return (1);
	}
	return (0);
}

void	write_red_echo(t_execlst *el)
{
	int		i;
	int		j;
	t_red	*red;

	i = 0;
	red = el->red;
	while (el->cmd && el->cmd[++i])
	{
		j = 0;
		while (el->cmd[i][j])
			write(red->fd, &el->cmd[i][j++], 1);
		if (el->cmd[i])
			write(red->fd, " ", 1);
	}
	write(red->fd, "\n", 2);
}

void	write_red_echo_n(t_execlst *el, int k)
{
	int		i;
	int		j;
	t_red	*red;

	red = el->red;
	i = k;
	while (el->cmd && el->cmd[i])
	{
		j = 0;
		while (el->cmd[i][j])
			write(red->fd, &el->cmd[i][j++], 1);
		if (el->cmd[i])
			write(red->fd, " ", 1);
		i++;
	}
}

int	red_echo(t_execlst *el)
{
	t_red	*red;

	red = el->red;
	if (red->type == APPND || red->type == REDOUT)
		if (red_out_echo(el, 0, 0, 0))
			return (1);
	if (red_in_echo(el))
		return (1);
	return (1);
}
