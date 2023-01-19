/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:25:09 by ataji             #+#    #+#             */
/*   Updated: 2022/11/21 18:10:18 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"

void	*ft_malloc(size_t size)
{
	void	*data;

	data = malloc(size);
	if (!data)
		ft_exit(1);
	add_to_garbege(&g_data.garbege, ft_new_gc(data));
	return (data);
}

void	*ft_malloc2(size_t size)
{
	void	*data;

	data = malloc(size);
	if (!data)
		ft_exit(1);
	add_to_garbege2(&g_data.garbege_exp_env, ft_new_gc2(data));
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
	t_exp_env	*tmp;

	while (g_data.garbege_exp_env)
	{
		tmp = g_data.garbege_exp_env->next;
		free(g_data.garbege_exp_env->_free);
		free(g_data.garbege_exp_env);
		g_data.garbege_exp_env = tmp;
	}
}

void	ft_exit(int ex)
{
	ft_free_inside();
	ft_free_env_exp();
	exit(ex);
}
