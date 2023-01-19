/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_four.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:47:09 by ataji             #+#    #+#             */
/*   Updated: 2022/11/21 22:54:08 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

void	add_variable_env(char *line, t_env **dt)
{
	t_env	*tmp;
	t_norm	norm;

	norm.i = 0;
	norm.c = 0;
	if (!*dt)
		*dt = init_envlst();
	tmp = *dt;
	norm.tab = add_variable_env_one(line, &tmp, norm.tab);
	norm.k = exist_or_not_env(norm.tab, line);
	if (ft_check_plus_env(line) == 1 && ++norm.c)
		ft_concat_plus_env(*dt, line);
	while (norm.c == 0 && norm.k == 0 && tmp && tmp->next)
		tmp = tmp->next;
	if (norm.c == 0 && norm.k == 0)
	{
		tmp->next = init_envlst();
		tmp = tmp->next;
	}
	if (norm.c == 0 && norm.k == 0 && norm.tab[1])
		add_variable_env_three(tmp, norm.tab);
	if (norm.c == 0 && norm.k == 0 && !norm.tab[1])
		add_variable_env_two(tmp, norm.tab, line);
}
