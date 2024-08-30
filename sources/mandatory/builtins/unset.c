/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:01:19 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/30 18:03:56 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_unset(t_token *tokens)
{
	int		i;
	char	**args;
	int		status;

	i = 0;
	status = 0;
	args = get_cmd_and_args(tokens);
	if (!args[1])
		return (set_exit_status(status));
	while (args[++i])
	{
		if (!is_valid_identifier(args[i], args[0]) && ++status)
			continue ;
		delete_env_key(get_key(args[i]));
	}
	return (set_exit_status(!!status));
}

void	delete_env_key(char *key_to_delete)
{
	int		i;
	int		j;
	char	*env_key;
	char	**new_env;
	char	**cur_env;

	cur_env = *get_my_env();
	i = 0;
	while (cur_env[i])
		i++;
	new_env = (char **)ft_calloc(i + 1, (sizeof(char *)));
	i = -1;
	j = -1;
	while (cur_env[++i])
	{
		env_key = get_key(cur_env[i]);
		if (ft_strcmp(key_to_delete, env_key))
			new_env[++j] = cur_env[i];
		else
			free(cur_env[i]);
	}
	free(cur_env);
	new_env[++j] = NULL;
	*get_my_env() = new_env;
	__environ = new_env;
}
