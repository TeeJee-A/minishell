/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 19:45:32 by ibenmain          #+#    #+#             */
/*   Updated: 2022/11/10 19:02:33 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

char	*find_env(char *path)
{
	t_env	*env;

	env = g_data.g_envlst;
	if (!env)
		return (NULL);
	if (path)
	{
		while (env)
		{
			if (!ft_strcmp(path, env->var))
				return (env->val);
			env = env->next;
		}
	}
	return (NULL);
}
