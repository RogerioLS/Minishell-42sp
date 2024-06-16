/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:52:30 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/15 17:13:59 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	get_var_name(char **input, char *varname, int *len)
{
	int	i;

	i = 0;
	while ((*input)[i] && (isalnum((*input)[i]) || (*input)[i] == '_'))
	{
		varname[i] = (*input)[i];
		i++;
	}
	varname[i] = '\0';
	*len = i;
}

void	append_var_value(char **input, char *result, \
						size_t *res_len)
{
	char	varname[256];
	char	*value;
	int		len;

	get_var_name(input, varname, &len);
	value = getenv(varname);
	if (value)
	{
		strcpy(&result[*res_len], value);
		*res_len += strlen(value);
	}
	else
	{
		result[(*res_len)++] = '$';
		strcpy(&result[*res_len], varname);
		*res_len += strlen(varname);
	}
	*input += len;
}

void	handle_double_quotes(char **input, char *result, size_t *res_len)
{
	(*input)++;
	while (**input && **input != '"')
	{
		if (**input == '$')
		{
			(*input)++;
			append_var_value(input, result, res_len);
		}
		else if (**input == '\\')
		{
			(*input)++;
			if (**input)
				result[(*res_len)++] = *(*input)++;
		}
		else
			result[(*res_len)++] = *(*input)++;
	}
	if (**input == '"')
		(*input)++;
	result[*res_len] = '\0';
}
