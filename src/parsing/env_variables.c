/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:07:18 by paribeir          #+#    #+#             */
/*   Updated: 2024/08/19 14:09:21 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check mem management
void	expand_env_vars(t_token	*token, t_cmd *cmd_data)
{
	char *str;
	char *current;

	if (!ft_strchr(token->str, '\''))
		token->str = expand_heredoc(token->str, cmd_data);
	else
	{
		current = ft_strdup("");
		str = token->str;
		while (*str)
		{
			if (ft_strchr(str, '$') && !var_in_squote(str))
				add_expanded_var(&current, &str, cmd_data); //expand this var
			else
				add_literal(&current, &str); //copy everything inside single quotes
		}
		free(token->str);
		token->str = current; //overwrite token->str with new string. Do I need to alloc more memory?
	}
}

void	add_expanded_var(char **current, char **str, t_cmd *cmd_data)
{
	char	*var;
	char	*total;

	var = get_var(str, cmd_data); //TO DO: check if this advances the string past the var name
	if (var)
	{
		total = (char *)ft_calloc(strlen(*current) + strlen(var) + 1, sizeof(char));
		if (total)
		{
			ft_strlcpy(total, *current, ft_strlen(*current) + ft_strlen(var) + 1);
			ft_strlcat(total, var, ft_strlen(*current) + ft_strlen(var) + 1);
			free (*current);
			*current = total;
		}
		free (var);
	}
}

//make function usable for wildcard as well?
void	add_literal(char **current, char **str)
{
	char	*total;
	int		len;

	if (ft_strchr(*str, '\''))
		len = ft_strchr(*str, '\'') - *str;
	else
		len = ft_strlen(*str);
	total = ft_calloc(strlen(*current) + len + 1, sizeof(char));
	if (total)
	{
		ft_strlcpy(total, *current, len);
		ft_strlcat(total, *str, len);
		free(*current);
		*current = total;
		*str += len;
	}
	if (**str == '\'')
            (*str)++;
}

/*If '$' is followed by a '?', it will be expanded into the exit status of the last foreground process.
If there are more characters after the '?', they are kept as is, not affecting the expansion.
e.g. $?hello --> 0hello*/
char	*get_var(char **str, t_cmd *cmd_data)
{
	char	*var_name;
	char	*start;
	char	*var_content;

	(*str)++;
	start = *str;
	if (start && start[0] == '?')
		return (expand_error_code(*str, cmd_data));
	else if (!start || (!ft_isalnum(*start) && *start != '_'))
		return ("$");
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	var_name = ft_substr(start, 0, *str - start);
	if (!var_name)
		return (NULL);
	var_content = exe_env_get_var(var_name, cmd_data);
	free(var_name);
	if (!var_content)
		return (ft_strdup(""));
	return (ft_strdup(var_content)); 
}

//return (ft_strdup(ft_itoa(cmd_data->exit_status)));
char	*expand_error_code(char *str, t_cmd *cmd_data)
{
	char	*error_code;
	char	*complete_str;
	char	*other;


	error_code = ft_strdup(ft_itoa(cmd_data->exit_status));
	if (++str)
	{
		if (str[0] == '$')
			get_var(*str, cmd_data);
		complete_str = (char*)ft_calloc(ft_strlen(error_code) + ft_strlen(*str) + 1, 1);
		if (!complete_str)
			return (NULL);
		complete_str = ft_strjoin(error_code, *str)
	}

}