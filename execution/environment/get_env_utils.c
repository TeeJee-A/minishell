/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 08:55:47 by ataji             #+#    #+#             */
/*   Updated: 2022/11/17 17:21:48 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_freeing_env(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	*get_var_name_env(const char *s, int index)
{
	char	*var_name;
	int		i;

	var_name = malloc(index + 1);
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < index)
	{
		var_name[i] = s[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*get_var_value_env(const char *s, int index)
{
	char	*var_value;
	int		j;

	if (s[index] == '\0')
		return (NULL);
	var_value = malloc(ft_strlen_env(s) - index + 1);
	if (!var_value)
		return (NULL);
	j = 0;
	while (s[index])
	{
		var_value[j] = s[index];
		index++;
		j++;
	}
	var_value[j] = '\0';
	return (var_value);
}

char	**set_words_env(char const *s, char c)
{
	char	**tab;
	int		i;

	tab = malloc(3 * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	tab[0] = get_var_name_env(s, i);
	tab[1] = get_var_value_env(s, i + 1);
	tab[2] = NULL;
	return (tab);
}

char	**ft_split_env(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = set_words_env((char *)s, c);
	return (tab);
}
