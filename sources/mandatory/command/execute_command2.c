/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:40 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/02 18:00:19 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../../includes/mandatory/mini_shell.h"
#include <linux/limits.h>

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

// int open_file(char *filename, int append)
// {
//     int fd = open(filename, O_WRONLY | O_CREAT | (append * O_APPEND), 0644); // Multiplicação por 0 ou 1
//     if (fd == -1) 
//         ft_putstr_fd("ft_echo: error opening file\n", STDERR_FILENO);
//     return fd;
// }

// void print_args(char **args, int i, int fd)
// {
//     while (args[i])
//     {
//         ft_putstr_fd(args[i], fd);
//         if (args[i + 1])
//             ft_putchar_fd(' ', fd);
//         i++;
//     }
// }

// void ft_echo(char **args)
// {
//     int i = 1, newline = 1, fd = STDOUT_FILENO, append = 0;
//     char *filename = NULL;

//     while (args[i] && (args[i][0] == ' ' || args[i][0] == '\t' || !ft_strcmp(args[i], "-n"))) 
//         newline = ft_strcmp(args[i++], "-n") != 0; // Inverte a condição

//     while (args[i] && !filename) 
//     {
//         if (is_operator_or_end(args[i]))
//         {
//             append = ft_strncmp(args[i], ">>", 2) == 0;
//             i++;
//         }
//         else
//             filename = is_inside_quotes(args[i]) ? skip_quotes(args[i] + 1) - 1 : args[i++];
//     }

//     if (filename)
//         fd = open_file(filename, append);

//     print_args(args, i, fd);

//     if (newline)
//         ft_putchar_fd('\n', fd);

//     if (fd != STDOUT_FILENO)
//         close(fd);
// }

void ft_echo(char **args) {
    int i = 1;
    int newline = 1; // Flag para controlar a impressão da nova linha no final

    if (ft_strcmp(args[1], "-n") == 0) {
        newline = 0;
        i++;
    }
	
    while (args[i] != NULL) {
        ft_printf("%s", args[i]);
        i++;
        if (args[i] != NULL) {
            ft_printf(" ");
        }
    }

    if (newline) {
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
