/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:34:20 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/12 21:19:11 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_get_into_home(char *path)
{
	if (path == NULL)
	{
		printf("cd: HOME not set");
		return (1);
	}
	return (0);
}

int	ft_cd(t_token *tokens)
{
	char	**args;
	int		token_list_size;
	char	*path;

	token_list_size = ft_token_lst_get_size(tokens);
	if (token_list_size > 2)
		return (!!write(STDERR_FILENO, "cd: too many arguments\n", 23));
	args = get_cmd_and_args(tokens);
	if (args[1] == NULL)
	{
		path = getenv("HOME");
		ft_get_into_home(path);
	}
	else
		path = ft_strdup(args[1]);
	if (chdir(path) != 0)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}
