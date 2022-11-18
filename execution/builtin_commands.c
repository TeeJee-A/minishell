/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:58:48 by ataji             #+#    #+#             */
/*   Updated: 2022/11/17 23:01:03 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_echo(t_execlst *el)
{
	int	i;

	i = 1;
	while (el->cmd[i])
	{
		printf("%s ", el->cmd[i]);
		i++;
	}
	printf("\n");
}

int	mini_echo(t_execlst *el)
{
	int	ck;

	ck = 0;
	if (el->cmd[1] == NULL && !el->red)
	{
		write (1, "\n", 1);
		ck = 1;
	}
	else
		ck = echo_cmd(el);
	return (ck);
}

int	mini_builtin_commands(t_execlst *el)
{
	return (check_access_file(el));
}

int	environment_commands(t_execlst *el)
{
	int	ck;

	ck = 0;
	if (!(my_strcmp(el->cmd[0], "env")))
		ck = env_cmd(el);
	else if (!(my_strcmp(el->cmd[0], "export")))
		ck = export_cmd(el->cmd, el);
	else if (!(my_strcmp(el->cmd[0], "unset")))
	{
		ck = unset_env(el->cmd);
		ck = unset_exp(el->cmd);
	}
	return (ck);
}

int	builtin_commands(t_execlst *el)
{
	int	ck;

	ck = 0;
	if (mini_builtin_commands(el) == -1)
		return (-1);
	if (el && el->cmd && el->cmd[0])
	{
		if (!(my_strcmp(el->cmd[0], "echo")))
			ck = mini_echo(el);
		else if (!(my_strcmp(el->cmd[0], "exit")))
			exit_cmd();
		else if (!(my_strcmp(el->cmd[0], "pwd")))
			ck = pwd_cmd(el);
		else if (!(my_strcmp(el->cmd[0], "cd")))
			ck = cd_cmd(el->cmd);
		else
			ck = environment_commands(el);
	}
	return (ck);
}
