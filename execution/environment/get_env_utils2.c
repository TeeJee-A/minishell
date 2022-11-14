/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 08:59:33 by ataji             #+#    #+#             */
/*   Updated: 2022/11/12 08:57:02 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr_env(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start < ft_strlen_env(s))
	{
		if (ft_strlen_env(s) < len)
			len = ft_strlen_env(s);
		str = (char *)malloc((len + 1) * sizeof(char));
		if (!str)
			return (NULL);
		while (i < len)
			str[i++] = s[start++];
	}
	else
		str = malloc(1);
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen_env(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_env(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(ft_strlen_env(s1) + 1 * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// t_env	*init_envlst_env(void)
// {
// 	t_env	*e;

// 	e = malloc(sizeof(t_env));
// 	e->var = NULL;
// 	e->val = NULL;
//     e->sz_var = 0;
//     e->sz_val = 0;
// 	e->next = NULL;
// 	return (e);
// }
