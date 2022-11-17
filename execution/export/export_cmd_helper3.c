/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_helper3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:45:47 by ataji             #+#    #+#             */
/*   Updated: 2022/11/17 21:51:43 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_it_exp(char **tab)
{
	int		i;
	int		j;
	int		count;
	char	*special;
	char	*line;

	i = 0;
	count = 0;
	special = "-$+,~^=}]/:\'\"%.0123456789";
	while (tab[i])
	{
		line = ft_strdup_exp(tab[i]);
		j = 0;
		while (special[j])
		{
			if (line[0] == special[j])
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	handle_special_char_exp(char **line)
{
	int	i;
	int	j;
	int	count;
	int	check;

	i = 0;
	j = 1;
	check = 0;
	count = find_it_exp(line);
	while (i < count)
	{
		printf("Minishell: `%s': Not a valid identifier\n", line[j]);
		g_data.exit_status = 1;
		i++;
		j++;
		check = 1;
	}
	if (check == 1)
		return (1);
	return (0);
}
