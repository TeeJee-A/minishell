/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:18:28 by ataji             #+#    #+#             */
/*   Updated: 2022/11/21 20:51:52 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"
#include "../includes/minishell.h"

int	exit_cmd(t_execlst *el)
{
	int	i;
	int	valid;

	printf("exit\n");
	i = -1;
	valid = 1;
	if (el->cmd && el->cmd[1] && !el->cmd[1][0])
		valid = 0;
	while (el->cmd && el->cmd[1] && el->cmd[1][++i])
		if (!ft_isdigit(el->cmd[1][i]))
			valid = 0;
	if (!valid)
	{
		printf("Minishell: exit: %s: \
			numeric argument required\n", el->cmd[1]);
		exit(255);
	}
	if (el->cmd && el->cmd[0] && el->cmd[1] && el->cmd[2])
		print_error_builtin("exit", "too many arguments", 1);
	else if (el->cmd[1])
		exit(ft_atoi(el->cmd[1]));
	else
		exit(0);
	return (1);
}
