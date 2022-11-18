/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:20:13 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 19:26:31 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"

void	msg_error(char *str)
{
	(void)str;
	write(1, " exit\n", 6);
	exit(0);
}

void	add_to_garbege(t_gc **data, t_gc *new)
{
	new->next = *data;
	*data = new;
	new = NULL;
}

void	add_to_garbege2(t_exp_env **data, t_exp_env *new)
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

t_exp_env	*ft_new_gc2(void *data)
{
	t_exp_env	*new;

	new = malloc(sizeof(t_exp_env));
	new->_free = data;
	new->next = NULL;
	return (new);
}
