/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:40 by roglopes          #+#    #+#             */
/*   Updated: 2024/05/11 11:55:52 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../../includes/mandatory/mini_shell.h"
#include <linux/limits.h>

// void	ft_pwd(int argc, char **argv)
// {
// 	char	wd[1024];

// 	if (argc > 1)
// 	{
// 		ft_printf("pwd: too many arguments\n");
// 	}
// 	else if (argc == 1)
// 	{
// 		if (argv[0][0] == '-' && argv[0][1] != '\0')
// 		{
// 			ft_printf("pwd: bad option: %s\n", argv[0]);
// 		}
// 		else
// 		{
// 			ft_printf("zsh: %s not found\n", argv[0]);
// 		}
// 	}
// 	else
// 	{
// 		getcwd(wd, sizeof(wd));
// 		ft_putendl_fd(wd, 1);
// 	}
// }

char *ft_realpath(const char *path, char *resolved_path) {
    char *tmp = realpath(path, resolved_path); // no argument for sizes
    if (tmp) {
        return tmp;
    } else {
        if (access(path, F_OK) == 0) {
            errno = ELOOP;
        }
        return NULL;
    }
}


void ft_pwd(int argc, char **argv) {
    char wd[PATH_MAX];
    int use_logical_path = 0;
    char *ptr_argv = *argv;
    int i = 0;

    while (i < argc) {
        if (ptr_argv[0] == '-') {
            if (ft_strcmp(ptr_argv, "-L") != 0) {
                ft_printf("pwd: bad option: %s\n", ptr_argv);
                return;
            }
            use_logical_path = 1;
        } else {
            ft_printf("pwd: too many arguments\n");
            return;
        }
        i++;
        ptr_argv++;
    }

    if (use_logical_path || getcwd(wd, sizeof(wd)) == NULL) {
        char resolved_path[PATH_MAX]; 
        if (ft_realpath(".", resolved_path) == NULL) { 
            perror("pwd");
        } else {
            ft_putendl_fd(resolved_path, 1);
        }
    } else {
        ft_putendl_fd(wd, 1);
    }
}



void ft_unset(char **args)
{
    if (!args[1]) 
    {
        ft_printf("unset: not enough arguments\n");
        return;
    }

    int i = 1;
    while (args[i]) 
    {
        if (unsetenv(args[i]) != 0) 
        {
            perror("unsetenv"); 
        }
        i++;
    }
}

void ft_echo(char **args)
{
    int i = 1;
    int newline = 1; // Flag para controlar a quebra de linha

    if (args[i] && ft_strcmp(args[i], "-n") == 0) 
    {
        newline = 0;
        i++;
    }

    while (args[i]) 
    {
        ft_printf("%s", args[i]);
        if (args[i + 1])
            ft_printf(" ");
        i++;
    }

    if (newline)
        ft_printf("\n");
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
