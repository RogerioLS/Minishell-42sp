/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:34:20 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/23 19:04:40 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_access(char *path)
{
	if (access(path, F_OK))
		return (!!ft_fprintf(STDERR_FILENO, "cd: \
			%s: No such file or directory\n", path));
	else if (access(path, R_OK))
		return (!!ft_fprintf(STDERR_FILENO, "cd: %s: permission denied\n",
				path));
	return (SUCCESS);
}

int	change_to_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home)
	{
		if (chdir(home) == -1)
			return (ft_handle_error(home));
		return (SUCCESS);
	}
	else
		return (!!write(STDERR_FILENO, "cd: HOME not set\n", 17));
}

int	change_dir(char *path)
{
	if (check_access(path) == FAILURE)
		return (FAILURE);
	if (chdir(path) == -1)
		return (ft_handle_error(path));
	return (SUCCESS);
}

int	ft_cd(t_token *tokens)
{
	char	**args;

	if (ft_token_lst_get_size(tokens) > 2)
		return (!!write(STDERR_FILENO, "cd: too many arguments\n", 23));
	args = ft_get_cmd_and_args(tokens);
	if (!args[1] || !ft_strcmp(args[1], "~"))
		return (change_to_home());
	return (change_dir(args[1]));
}
