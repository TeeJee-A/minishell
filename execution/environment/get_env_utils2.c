/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 08:59:33 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 10:49:36 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
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
		str = (char *)ft_malloc2((len + 1) * sizeof(char));
		if (!str)
			ft_exit(1);
		while (i < len)
			str[i++] = s[start++];
	}
	else
	{
		str = ft_malloc2(1);
		if (!str)
			ft_exit(1);
	}
	return (str[i] = '\0', str);
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
	str = (char *)ft_malloc2(ft_strlen_env(s1) + 1 * sizeof(char));
	if (!str)
		ft_exit(1);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
