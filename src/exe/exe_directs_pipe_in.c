/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs_pipe_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:05:09 by jdach             #+#    #+#             */
/*   Updated: 2024/07/17 22:05:51 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs_pipe_in(t_cmd *cmd_env)
{
	dup2(cmd_env->pipe[0], STDIN_FILENO);
	close(cmd_env->pipe[0]);
}