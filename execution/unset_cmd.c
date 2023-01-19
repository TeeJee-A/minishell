/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:26:25 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 14:46:36 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"
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
			if (!(my_strcmp(tmp->var, line[i])))
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

int	special_unset(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while ("-$,~^=}]/:\'\"%.0123456789"[j])
		{
			if (line[i] == "-$,~^=}]/:%.0123456789"[j])
				return (print_error_builtin(line, \
"Not a valid identifier", 1), 1);
			j++;
		}
		i++;
	}
	return (0);
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
		if (special_unset(line[i]))
			return (1);
		while (tmp)
		{
			if (!(my_strcmp(tmp->var, line[i])))
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
