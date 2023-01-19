/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:36:11 by ataji             #+#    #+#             */
/*   Updated: 2022/11/21 23:10:41 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

int	ft_check_plus_exp(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '+' && (!line[i + 1] || line[i + 1] != '='))
			return (2);
		if (line[i] == '+' && line[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_replace_value_variable_exp(t_env *dt, char *var, char *val)
{
	t_env	*tmp;

	tmp = dt;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->next = init_explst();
		tmp = tmp->next;
	}
	tmp->var = ft_strdup_exp(var);
	tmp->val = ft_strdup_exp(val);
	tmp->sz_val = ft_strlen_exp(tmp->val);
	tmp->sz_var = ft_strlen_exp(tmp->var);
}

int	ft_replace_value_exp(t_env *dt, char *var, char *val)
{
	t_env	*tmp;

	tmp = dt;
	while (tmp)
	{
		if (!ft_strcmp_exp(tmp->var, var))
		{
			if (!tmp->val)
			{
				tmp->val = ft_strdup_exp(val);
				tmp->sz_val = ft_strlen_exp(val);
			}
			else
				tmp->val = ft_strjoin_exp(tmp->val, val);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	plus_cmp_exp(char *var)
{
	t_env	*dt;

	dt = g_data.g_explst;
	while (dt)
	{
		if (!ft_strcmp_exp(var, dt->var))
			return (1);
		dt = dt->next;
	}
	return (0);
}
