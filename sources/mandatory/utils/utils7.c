/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:33:56 by codespace         #+#    #+#             */
/*   Updated: 2024/08/16 22:47:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

static char	*get_key(char *envp, int *len_key)
{
	char	*key;

	*len_key = 0;
	while (envp[*len_key] != '=')
		(*len_key)++;
	key = ft_strndup(envp, *len_key);
	*len_key += 1;
	return (key);
}

void	get_envp(t_venv **envp, char **environ)
{
	char	*key;
	char	*value;
	int		index;
	int		len_key;

	index = 0;
	len_key = 0;
	while (environ[index])
	{
		key = get_key(environ[index], &len_key);
		value = ft_strdup(environ[index] + len_key);
		env_lstadd_back(envp, env_lstnew(key, value));
		index++;
		free (key);
		free (value);
	}
}
