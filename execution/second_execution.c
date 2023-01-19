/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:49:44 by ataji             #+#    #+#             */
/*   Updated: 2022/11/20 20:08:23 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"

char	*change_app_to_low(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] >= 65 && cmd[i] <= 90)
			cmd[i] += 32;
		i++;
	}
	return (cmd);
}

void	preexec(t_execlst *el, int pipe[2])
{
	if (el->next)
	{
		dup2(pipe[W], STDOUT_FILENO);
		close(pipe[R]);
		close(pipe[W]);
	}
}

void	postexec(t_execlst *el, int pipe[2])
{
	if (el->next)
	{
		dup2(pipe[R], STDIN_FILENO);
		close(pipe[R]);
		close(pipe[W]);
	}
	else
		close(0);
}

int	check_if_builtin(t_execlst *el)
{
	char	*cmd;
	char	**tab;
	int		i;

	i = 0;
	if (!el->cmd || !*el->cmd)
		return (0);
	if (!el)
		return (0);
	el->cmd[0] = change_app_to_low(el->cmd[0]);
	cmd = "echo exit pwd cd env export unset";
	tab = my_split(cmd, ' ');
	while (tab[i])
	{
		if (my_strcmp(tab[i++], el->cmd[0]) == 0)
			return (0);
	}
	return (1);
}
