/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env_get_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:53 by jdach             #+#    #+#             */
/*   Updated: 2024/08/18 14:41:59 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_env_get_var(char *var, t_cmd *cmd_data)
{
	char	*env_var_string;
	char	*return_str;
	char	**split_strings;

	env_var_string = exe_env_get_var_address(var, cmd_data);
	if (env_var_string)
	{
		split_strings = ft_split(env_var_string, '=');
		return_str = ft_strdup(split_strings[1]);
		exe_cleanup_strarray(split_strings);
		return (return_str);
	}
	return (NULL);
}
