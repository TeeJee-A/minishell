/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:25:09 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 12:19:12 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

void	add_to_garbege(t_gc **data, t_gc *new)
{
	new->next = *data;
	*data = new;
	new = NULL;
}

t_gc	*ft_new_gc(void *data)
{
	t_gc	*new;

	new = malloc(sizeof(t_gc));
	new->_free = data;
	new->next = NULL;
	return (new);
}

void	*ft_malloc(size_t size)
{
	void	*data;

	data = malloc(size);
	if (!data)
		ft_exit(1);
	add_to_garbege(&g_data.garbege, ft_new_gc(data));
	return (data);
}

void	ft_free_inside(void)
{
	t_gc	*tmp;

	while (g_data.garbege)
	{
		tmp = g_data.garbege->next;
		free(g_data.garbege->_free);
		free(g_data.garbege);
		g_data.garbege = tmp;
	}
}

void	ft_free_env_exp(void)
{
	t_env	*tmp;

	while (g_data.g_envlst)
	{
		tmp = g_data.g_envlst->next;
		free(g_data.g_envlst->var);
		free(g_data.g_envlst->val);
		free(g_data.g_envlst);
		g_data.g_envlst = tmp;
	}
	while (g_data.g_explst)
	{
		tmp = g_data.g_explst->next;
		free(g_data.g_explst->var);
		free(g_data.g_explst->val);
		free(g_data.g_explst);
		g_data.g_explst = tmp;
	}
}

void	ft_exit(int ex)
{
	ft_free_inside();
	ft_free_env_exp();
	exit(ex);
}
