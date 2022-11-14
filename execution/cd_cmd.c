/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:29:20 by ataji             #+#    #+#             */
/*   Updated: 2022/11/12 09:47:41 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_cmd(char **line)
{
	if (line[1] == NULL)
	{
		if (!getenv("HOME"))
		{
			printf("Minishell: cd: HOME not set\n");
			return (1);
		}
		chdir(getenv("HOME"));
		return (1);
	}
	if (access(line[1], X_OK) == -1)
		printf("Minishell: cd: %s: Permission denied\n", line[1]);
	else if (chdir(line[1]) == -1)
		printf("Minishell: cd: %s: No such file or directory\n", line[1]);
	return (1);
}
