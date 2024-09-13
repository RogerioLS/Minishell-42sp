/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:01:19 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/13 18:34:29 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	delete_env_key(char *key_to_delete)
{
	int		i;
	int		j;
	char	*env_key;
	char	**new_env;
	char	**current_env;

	current_env = *ft_get_my_env();
	i = 0;
	while (current_env[i])
		i++;
	new_env = (char **)ft_calloc(i + 1, (sizeof(char *)));
	i = -1;
	j = -1;
	while (current_env[++i])
	{
		env_key = get_key(current_env[i]);
		if (ft_strcmp(key_to_delete, env_key))
			new_env[++j] = current_env[i];
		else
			free(current_env[i]);
	}
	free(current_env);
	new_env[++j] = NULL;
	*ft_get_my_env() = new_env;
	__environ = new_env;
}

int	ft_unset(t_token *tokens)
{
	int		i;
	char	**args;
	int		status;

	i = 0;
	status = 0;
	args = get_cmd_and_args(tokens);
	if (!args[1])
		return (ft_set_exit_status(status));
	while (args[++i])
	{
		if (!is_valid_identifier(args[i], args[0]) && ++status)
			continue ;
		delete_env_key(get_key(args[i]));
	}
	return (ft_set_exit_status(!!status));
}
