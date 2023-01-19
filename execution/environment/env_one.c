/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_one.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:18:03 by ataji             #+#    #+#             */
/*   Updated: 2022/11/21 20:41:55 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

int	ft_check_plus_env(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '+' && line[i + 1] != '=')
			return (2);
		if (line[i] == '+' && line[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	find_equal_env(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	add_val_if_not_exist(t_env *dt, char *line, char **tab)
{
	if (tab[1])
	{
		dt->val = ft_strdup_env(tab[1]);
		dt->sz_val = ft_strlen_env(tab[1]);
		return (1);
	}
	else if (!tab[1])
	{
		if (find_equal_env(line))
		{
			dt->val = ft_strdup_env("");
			dt->sz_val = 1;
		}
		return (1);
	}
	return (2);
}

int	exist_or_not_env(char **tab, char *line)
{
	t_env	*dt;

	dt = g_data.g_envlst;
	while (dt)
	{
		if (ft_strcmp_env(tab[0], dt->var) == 0)
		{
			if (add_val_if_not_exist(dt, line, tab) == 1)
				return (1);
			return (2);
		}
		dt = dt->next;
	}
	return (0);
}

bool	find_equal_environment(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}
