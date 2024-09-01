/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:15:53 by codespace         #+#    #+#             */
/*   Updated: 2024/08/31 20:54:28 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

char	***ft_get_my_env(void)
{
	static char	**env;

	return (&env);
}

int	*ft_get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

int	ft_set_exit_status(int status)
{
	int	*exit_status;

	exit_status = ft_get_exit_status();
	*exit_status = status;
	return (*exit_status);
}

void	ft_add_to_env(char *str)
{
	char	**new_env;
	int		i;
	char	**env;

	env = *get_my_env();
	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i++] = ft_strdup_calloc(str);
	new_env[i] = NULL;
	free(env);
	*get_my_env() = new_env;
	__environ = new_env;
}

void	ft_update_env(char *new_str, char *key)
{
	int		i;
	char	*env_key;
	char	*aux;
	char	**env;

	env = *get_my_env();
	i = -1;
	while (env[++i])
	{
		env_key = get_key(env[i]);
		if (!ft_strcmp(key, env_key))
		{
			aux = env[i];
			env[i] = ft_strdup_calloc(new_str);
			free(aux);
			break ;
		}
	}
	*get_my_env() = env;
	__environ = env;
}

void	ft_set_env(char *new_str, char *key, char *value)
{
	char	*env_var;

	env_var = getenv(key);
	if ((env_var || is_key_without_value(key)) && value != NULL)
		ft_update_env(new_str, key);
	else if (!is_env_key_present(key))
		ft_add_to_env(new_str);
}
