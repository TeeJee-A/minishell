/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:38:05 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 11:01:09 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

int	exist_or_not_exp(char **tab, char *line)
{
	t_env	*dt;

	dt = g_data.g_explst;
	while (dt)
	{
		if (ft_strcmp_exp(tab[0], dt->var) == 0)
		{
			if (tab[1])
				return (dt->val = ft_strdup_exp(tab[1]), \
				dt->sz_val = ft_strlen_exp(tab[1]), 1);
			else if (!tab[1])
			{
				if (find_equal_exp(line))
				{
					dt->val = ft_strdup_exp("");
					dt->sz_val = 1;
				}
				return (1);
			}
			return (2);
		}
		dt = dt->next;
	}
	return (0);
}

int	find_equal_exp(char *line)
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

int	check_if_in_export(char *variable)
{
	t_env	*dt;

	dt = g_data.g_explst;
	while (dt)
	{
		if (!my_strcmp(variable, dt->var))
			return (0);
		dt = dt->next;
	}
	return (1);
}

int	check_if_dollar(char *dollar)
{
	int		i;
	char	*next_dollar;
	int		size_dollar;
	t_env	*dt;

	i = 0;
	dt = g_data.g_explst;
	next_dollar = ft_substr_exp(dollar, 1, ft_strlen_exp(dollar));
	size_dollar = ft_strlen_exp(next_dollar);
	if (size_dollar)
	{
		if (!check_if_in_export(next_dollar))
			return (printf("Minishell: `%s': Not a valid identifier\n", \
			next_dollar), 1);
		else
		{
			if (dt->sz_val)
				printf("declare -x %s=\"%s\"\n", dt->var, dt->val);
			else
				printf("declare -x %s\n", dt->var);
			return (1);
		}
	}
	return (0);
}

int	special_char(char *line, char **tab)
{
	int		i;
	int		j;
	char	*special;

	special = "$+,~^=}]/:\'\"%.0123456789";
	i = 1;
	if (line)
	{
		while (tab[i])
		{
			j = 0;
			while (special[j])
			{
				if (line[0] == special[j])
				{
					printf("Minishell: `%s': Not a valid identifier\n", tab[i]);
					return (1);
				}
				j++;
			}
			i++;
		}
	}
	return (0);
}
