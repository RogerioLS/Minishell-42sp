/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:34:20 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/13 18:46:16 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"



char *get_cwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
        ft_handle_error("cd");
    ft_collect_mem(cwd);
    return (cwd);
}

int check_access(char *path)
{
    if (access(path, F_OK))
        return (!!ft_fprintf(STDERR_FILENO, "cd: %s: no such file or directory\n", path));
    else if (access(path, R_OK))
        return (!!ft_fprintf(STDERR_FILENO, "cd: %s: permission denied\n", path));
    return (SUCCESS);
}

int change_to_home(void)
{
    char *home;
    char *cur_dir;

	cur_dir = getcwd(NULL, 0);
	ft_collect_mem(cur_dir);
    home = getenv("HOME");
    if (home)
    {
        if (chdir(home) == -1)
            return (ft_handle_error(home));
		ft_set_env(ft_strjoin("OLDPWD=", cur_dir), "OLDPWD", cur_dir);
		ft_set_env(ft_strjoin("PWD=", getcwd(NULL, 0)), "PWD", getcwd(NULL, 0));
        return (SUCCESS);
    }
    else
        return (!!write(STDERR_FILENO, "cd: HOME not set\n", 17));
}

int	change_dir(char *path)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 4096);
	if (!cur_dir)
		return (ft_handle_error("cd"));
	ft_collect_mem(cur_dir);
	if (check_access(path) == FAILURE)
		return (FAILURE);
	if (chdir(path) == -1)
		return (ft_handle_error(path));
	ft_set_env(ft_strjoin("OLDPWD=", cur_dir), "OLDPWD", cur_dir);
	ft_set_env(ft_strjoin("PWD=", getcwd(NULL, 0)), "PWD", getcwd(NULL, 0));
	return (SUCCESS);
}

int ft_cd(t_token *tokens)
{
    char **args;

    if (ft_token_lst_get_size(tokens) > 2)
        return (!!write(STDERR_FILENO, "cd: too many arguments\n", 23));
    args = get_cmd_and_args(tokens);
    if (!args[1] || !ft_strcmp(args[1], "~"))
        return (change_to_home());
    return (change_dir(args[1]));
}
