/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:38:47 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 13:18:46 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"
#include "../includes/minishell.h"

int	echo_heredc(t_execlst *el, int k, int c, int check__)
{
	int		j;
	t_red	*red;

	red = el->red;
	while (el->cmd[++k] && (el->cmd[k][0] == '-' && el->cmd[k][1]))
	{
		j = 1;
		while (el->cmd[k][j] == 'n')
			j++;
		if (!el->cmd[k][j])
		{
			c = 1;
			check__ = 1;
		}
		else
		{
			check__ = 0;
			break ;
		}
	}
	if (check__ == 0 && c == 0)
		print_echo(el);
	else if (check__ == 1 || (check__ == 0 && c == 1))
		print_echo_n(el, k);
	return (1);
}

int	red_out_echo(t_execlst *el, int k, int c, int check__)
{
	int		j;
	t_red	*red;

	red = el->red;
	while (el->cmd[++k] && (el->cmd[k][0] == '-' && el->cmd[k][1]))
	{
		j = 1;
		while (el->cmd[k][j] == 'n')
			j++;
		if (!el->cmd[k][j])
		{
			c = 1;
			check__ = 1;
		}
		else
		{
			check__ = 0;
			break ;
		}
	}
	if (check__ == 0 && c == 0)
		write_red_echo(el);
	else if (check__ == 1 || (check__ == 0 && c == 1))
		write_red_echo_n(el, k);
	return (0);
}

int	echo_cmd(t_execlst *el, int k, int c, int check__)
{
	int		j;
	t_red	*red;

	red = el->red;
	if (red && red->fd)
		return (red_echo(el));
	while (el->cmd[++k] && (el->cmd[k][0] == '-' \
		&& el->cmd[k][1]) && check__ != 0)
	{
		j = 1;
		while (el->cmd[k][j] == 'n')
			j++;
		if (!el->cmd[k][j])
		{
			c = 1;
			check__ = 1;
		}
		else
			check__ = 0;
	}
	if ((check__ == 0 || check__ == -1) && c == 0)
		print_echo(el);
	else if (check__ == 1 || ((check__ == 0 || check__ == -1) && c == 1))
		print_echo_n(el, k);
	return (1);
}
