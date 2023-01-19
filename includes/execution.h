/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:24:20 by kfaouzi           #+#    #+#             */
/*   Updated: 2022/11/19 10:24:32 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H

# define EXECUTION_H
# include"libftpars.h"
# include"parsing.h"
# include <errno.h>

char		*creat_tmp_file(char *file);
char		*get_envval(char *s);
char		*find_env(char *path);
int			check_access(t_execlst *el);
char		*get_path(char *cmd);
int			handle_red(t_red *red);
int			check_access(t_execlst *el);
void		stay_in_shell(int _signal);
void		handel_sig_hr(int _signal);
#endif
