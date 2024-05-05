/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:40 by roglopes          #+#    #+#             */
/*   Updated: 2024/05/05 17:20:36 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	ft_pwd(int argc, char **argv)
{
	char	wd[1024];

	if (argc > 1)
	{
		ft_printf("pwd: too many arguments\n");
	}
	else if (argc == 1)
	{
		if (argv[0][0] == '-' && argv[0][1] != '\0')
		{
			ft_printf("pwd: bad option: %s\n", argv[0]);
		}
		else
		{
			ft_printf("zsh: %s not found\n", argv[0]);
		}
	}
	else
	{
		getcwd(wd, sizeof(wd));
		ft_putendl_fd(wd, 1);
	}
}

void	list_directory(char **args)
{
	int				long_format;
	char			path[MAX_PATH_LEN];
	DIR				*dir;
	struct dirent	*entry;

	long_format = 0;
	path[MAX_PATH_LEN] = "";
	process_arguments(args, path, &long_format);
	if (path[0] == '\0')
	{
		getcwd(path, sizeof(path));
	}
	dir = opendir(path);
	if (dir == NULL)
	{
		perror("opendir() error");
		return ;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			if (long_format)
			{
				print_file_info(entry, path);
			}
			else
			{
				ft_printf("%s\n", entry->d_name);
			}
		}
	}
	closedir(dir);
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

void	export_variable(char **args)
{
	char	*name;
	char	*value;

	if (args[1] != NULL)
	{
		name = ft_strtok(args[1], "=");
		value = ft_strtok(NULL, "=");
		if (name != NULL)
		{
			if (value != NULL)
			{
				setenv(name, value, 1);
			}
			else
			{
				setenv(name, "", 1);
			}
		}
	}
	else
	{
		print_environment();
	}
}
