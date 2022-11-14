/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:18:59 by kfaouzi           #+#    #+#             */
/*   Updated: 2022/11/10 19:08:28 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

void	stay_in_shell(int _signal)
{
	if (SIGINT == _signal && g_data.id_cat == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		g_data.id_cat = 0;
}

void	handel_sig_hr(int _signal)
{
	(void)_signal;
	g_data.exec = -1;
	rl_done = 1;
}
