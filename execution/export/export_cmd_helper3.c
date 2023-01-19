/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_helper3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:45:47 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 14:31:26 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

int	find_it_exp(char *line)
{
	int		j;
	char	**special;
	int		k;
	int		check__;

	k = -1;
	check__ = 0;
	special = ft_split_exp(line, '=');
	if (!special[0][0])
		check__ = 1;
	while (special[0][++k])
	{
		j = 0;
		while ("-$,~^=}]/:\'\"%.0123456789"[j])
		{
			if (special[0][k] == "-$,~^=}]/:%.0123456789"[j])
				check__ = 1;
			j++;
		}
	}
	return (check__);
}

int	handle_special_char_exp(char *line)
{
	int	k;
	int	check;

	k = 0;
	check = 0;
	check = find_it_exp(line);
	if (check == 1)
	{
		print_error_builtin(line, "Not a valid identifier", 1);
		return (1);
	}
	return (0);
}

int	add_var_helper3(char *line)
{
	if (ft_check_plus_exp(line) == 2)
	{
		print_error_builtin(line, "Not a valid identifier", 1);
		return (0);
	}
	return (1);
}
