/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:20:45 by ataji             #+#    #+#             */
/*   Updated: 2022/11/21 20:43:30 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

void	add_variable_env_two(t_env *dt, char **tab, char *line)
{
	t_env	*tmp;

	tmp = dt;
	tmp->var = ft_strdup_env(tab[0]);
	if (find_equal_env(line))
	{
		tmp->val = ft_strdup_env("");
		tmp->sz_val = 1;
	}
	tmp->sz_var = ft_strlen_env(tab[0]);
	tmp->next = NULL;
}

void	add_variable_env_three(t_env *dt, char **tab)
{
	t_env	*tmp;

	tmp = dt;
	tmp->var = ft_strdup_env(tab[0]);
	tmp->val = ft_strdup_env(tab[1]);
	tmp->sz_var = ft_strlen_env(tab[0]);
	tmp->sz_val = ft_strlen_env(tab[1]);
	tmp->next = NULL;
}

void	redin_env(t_env *tmp)
{
	if (tmp->sz_val)
	{
		write(1, tmp->var, tmp->sz_var);
		write(1, "=", 1);
		write(1, tmp->val, tmp->sz_val);
	}
	if (tmp->sz_val)
		write(1, "\n", 1);
}

int	redout_env(t_execlst *el, t_env *tmp)
{
	while (tmp)
	{
		if (el->red->type == REDOUT || el->red->type == APPND)
		{
			while (el->red->next)
				el->red = el->red->next;
			if (tmp->sz_val)
			{
				write(el->red->fd, tmp->var, tmp->sz_var);
				write(el->red->fd, "=", 1);
				write(el->red->fd, tmp->val, tmp->sz_val);
			}
			if (tmp->sz_val)
				write(el->red->fd, "\n", 1);
		}
		if (el->red->type == REDIN || el->red->type == HEREDC)
			redin_env(tmp);
		tmp = tmp->next;
	}
	return (1);
}

int	env_cmd(t_execlst *el)
{
	t_env	*tmp;

	tmp = g_data.g_envlst;
	if (el->red && el->red->fd)
	{
		redout_env(el, tmp);
		return (1);
	}
	while (tmp)
	{
		if (tmp->sz_val && tmp->sz_var)
			printf("%s=%s\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
	return (1);
}
