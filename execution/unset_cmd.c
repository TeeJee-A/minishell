/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:26:25 by ataji             #+#    #+#             */
/*   Updated: 2022/11/11 21:23:44 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mini_unset_env(t_env *tmp, t_env *tmp2)
{
	if (tmp == g_data.g_envlst)
	{
		g_data.g_envlst = tmp->next;
		tmp->next = NULL;
		tmp = NULL;
		tmp2 = NULL;
	}
	else
	{
		tmp2->next = tmp->next;
		tmp->next = NULL;
		tmp = NULL;
		tmp2 = NULL;
	}
}

void	mini_unset_exp(t_env *tmp, t_env *tmp2)
{
	if (tmp == g_data.g_explst)
	{
		g_data.g_explst = tmp->next;
		tmp->next = NULL;
		tmp = NULL;
		tmp2 = NULL;
	}
	else
	{
		tmp2->next = tmp->next;
		tmp->next = NULL;
		tmp = NULL;
		tmp2 = NULL;
	}
}

int	unset_env(char **line)
{
	t_env	*tmp;
	t_env	*tmp2;
	int		i;

	i = 0;
	while (line && line[++i])
	{
		tmp = g_data.g_envlst;
		tmp2 = g_data.g_envlst;
		while (tmp)
		{
			if (!(ft_strcmp(tmp->var, line[i])))
			{
				mini_unset_env(tmp, tmp2);
				break ;
			}
			if (tmp != g_data.g_envlst)
				tmp2 = tmp2->next;
			tmp = tmp->next;
		}
	}
	return (1);
}

int	unset_exp(char **line)
{
	t_env	*tmp;
	t_env	*tmp2;
	int		i;

	i = 0;
	while (line && line[++i])
	{
		tmp = g_data.g_explst;
		tmp2 = g_data.g_explst;
		while (tmp)
		{
			if (!(ft_strcmp(tmp->var, line[i])))
			{
				mini_unset_exp(tmp, tmp2);
				break ;
			}
			if (tmp != g_data.g_explst)
				tmp2 = tmp2->next;
			tmp = tmp->next;
		}
	}
	return (1);
}
