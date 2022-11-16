/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:56:09 by ataji             #+#    #+#             */
/*   Updated: 2022/11/16 19:37:40 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error_builtin(char *s1, char *s2, int error)
{
	printf("Minishell: %s: %s\n", s1, s2);
	g_data.exit_status = error;
}

void	print_error(char *s1, char *s2, int error)
{
	printf("Minishell: %s: %s\n", s1, s2);
	g_data.exit_status = error;
	exit(error);
}
