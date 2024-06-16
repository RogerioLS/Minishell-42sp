/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:29:34 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/16 13:41:30 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

char	*ft_realpath(const char *path, char *resolved_path)
{
	char	*tmp;

	tmp = realpath(path, resolved_path);
	if (tmp)
	{
		return (tmp);
	}
	else
	{
		if (access(path, F_OK) == 0)
		{
			errno = ELOOP;
		}
		return (NULL);
	}
}

void	ft_pwd(int argc, char **argv)
{
	char	wd[PATH_MAX];
	char	resolved_path[PATH_MAX];
	int		use_logical_path;

	use_logical_path = 0;
	if (argc > 1)
	{
		if (ft_strcmp(argv[1], "-L") != 0)
		{
			ft_printf("pwd: bad option: %s\n", argv[1]);
			return ;
		}
		use_logical_path = 1;
	}
	if (use_logical_path || getcwd(wd, sizeof(wd)) == NULL)
	{
		if (ft_realpath(".", resolved_path) == NULL)
			perror("pwd");
		else
			ft_putendl_fd(resolved_path, 1);
	}
	else
		ft_putendl_fd(wd, 1);
}

void	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		i++;
		if (args[i] != NULL)
		{
			ft_printf(" ");
		}
	}
	if (newline)
	{
		ft_printf("\n");
	}
}

void	clear_screen(void)
{
	ft_printf("\e[2J\e[H");
}

void	ft_cd(char *path)
{
	char	*home;

	if (!path)
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			ft_printf("cd: HOME not set\n");
			return ;
		}
		path = home;
	}
	if (chdir(path) != 0)
	{
		perror("cd");
	}
}
