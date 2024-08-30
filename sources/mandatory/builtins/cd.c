/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:34:20 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/30 15:11:15 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_cd(t_token *tokens)
{
	char	**args;
	int		token_list_size;

	token_list_size = ft_token_lst_get_size(tokens);
	if (token_list_size > 2)
		return (!!write(STDERR_FILENO, "cd: too many arguments\n", 23));
	args = get_cmd_and_args(tokens);
	if (!args[1] || !ft_strcmp(args[1], "~"))
		return (back_to_home());
	return (change_dir(args[1]));
}

int	handle_set_env(char *env, char *current_dir)
{
	if (env)
	{
		if (chdir(env) == -1)
			return (ft_handle_error(env));
		ft_set_env(ft_strjoin("OLDPWD=", current_dir), "OLDPWD", current_dir);
		ft_set_env(ft_strjoin("PWD=", getcwd(NULL, 0)), "PWD", getcwd(NULL, 0));
		return (SUCCESS);
	}
}

int	back_to_home(void)
{
	char	*home;
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	ft_collect_mem(current_dir);
	home = getenv("HOME");
	handle_set_env(home, current_dir);
	if (!home)
		return (!!write(STDERR_FILENO, "cd: HOME not set\n", 17));
}

int	entry_dir(char *path)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 4096);
	if (!current_dir)
		return (ft_handle_error("cd"));
	ft_collect_mem(current_dir);
	if (check_access(path) == FAILURE)
		return (FAILURE);
	if (chdir(path) == -1)
		return (ft_handle_error(path));
	handle_set_env(path, current_dir);
}

int	check_access(char *path)
{
	if (access(path, F_OK))
		return (!!ft_printf("cd: %s: no such file or directory\n", path));
	else if (access(path, R_OK))
		return (!!ft_printf("cd: %s: permission denied \n", path));
	return (SUCCESS);
}