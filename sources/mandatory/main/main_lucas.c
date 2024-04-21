/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:27:05 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/21 03:10:00 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#define MAX_PATH_LEN 1024
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

char *ft_strcpy(char *dest, const char *src){
	char *tmp = dest;
	while ((*dest++ = *src++) != '\0');
	return tmp;

}

void print_file_info(struct dirent *entry, char *path) {
    char full_path[MAX_PATH_LEN];
    struct stat file_info;

    int path_len = ft_strlen(path);
    int entry_len = ft_strlen(entry->d_name);

    if (path_len + 1 + entry_len >= MAX_PATH_LEN) {
        ft_printf("Path is too long\n");
        return;
    }

    ft_strcpy(full_path, path);
    full_path[path_len] = '/';
    ft_strcpy(full_path + path_len + 1, entry->d_name);

    if (stat(full_path, &file_info) == 0) {
        char permissions[11];
        permissions[0] = (S_ISDIR(file_info.st_mode)) ? 'd' : '-';
        permissions[1] = (file_info.st_mode & S_IRUSR) ? 'r' : '-';
        permissions[2] = (file_info.st_mode & S_IWUSR) ? 'w' : '-';
        permissions[3] = (file_info.st_mode & S_IXUSR) ? 'x' : '-';
        permissions[4] = (file_info.st_mode & S_IRGRP) ? 'r' : '-';
        permissions[5] = (file_info.st_mode & S_IWGRP) ? 'w' : '-';
        permissions[6] = (file_info.st_mode & S_IXGRP) ? 'x' : '-';
        permissions[7] = (file_info.st_mode & S_IROTH) ? 'r' : '-';
        permissions[8] = (file_info.st_mode & S_IWOTH) ? 'w' : '-';
        permissions[9] = (file_info.st_mode & S_IXOTH) ? 'x' : '-';
        permissions[10] = '\0';

        ft_printf("%s %3ld %-8d %-8d %8ld %.12s %s\n",
            permissions,
            file_info.st_nlink,
            file_info.st_uid,
            file_info.st_gid,
            file_info.st_size,
            ctime(&file_info.st_mtime) + 4,
            entry->d_name);
    }
}



void process_arguments(char **args, char *path, int *long_format) {
    int i = 1;
    while (args[i] != NULL && i < 3) {
        if (args[i][0] == '-') {
            if (args[i][1] == 'l') {
                *long_format = 1;
            }
        } else {
            ft_strcpy(path, args[i]);
        }
        i++;
    }
}

void list_directory(char **args) {
    int long_format = 0;
    char path[MAX_PATH_LEN] = "";

    process_arguments(args, path, &long_format);

    if (path[0] == '\0') {
        getcwd(path, sizeof(path));
    }

    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir() error");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            if (long_format) {
                print_file_info(entry, path);
            } else {
                ft_printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
}

int	ft_lstsize(t_token *head)
{
	int	count;

	count = 1;
	if (head == NULL)
		return (0);
	while (head->next != NULL)
	{
		head = head->next;
		count++;
	}
	return (count);
}

void print_environment() {
    extern char **environ;
    for (char **env = environ; *env != NULL; env++) {
        ft_printf("%s\n", *env);
    }
}

void	ft_pwd(void)
{
	char	wd[1024];
	
	getcwd(wd, sizeof(wd));
	ft_putendl_fd(wd, 1);
}

void export_variable(char **args) {
    if (args[1] != NULL) {
        char *name = ft_strtok(args[1], "=");
        char *value = ft_strtok(NULL, "=");
        
        if (name != NULL) {
            if (value != NULL) {
                setenv(name, value, 1);
            } else {
                setenv(name, "", 1);
            }
        }
    } else {
        print_environment();
    }
}

void clear_screen() {
    ft_printf("\e[2J\e[H");
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}


void execute_command(char **args) {
    if (args == NULL || args[0] == NULL) {
        return;
    }

    if (ft_strcmp(args[0], "pwd") == 0) {
        ft_pwd();
    } else if (ft_strcmp(args[0], "ls") == 0) {
        list_directory(args);
    } else if (ft_strcmp(args[0], "clear") == 0) {
        clear_screen();
    } else if (ft_strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (ft_strcmp(args[0], "export") == 0) {
        export_variable(args);
    } else if (ft_strcmp(args[0], "env") == 0) {
        print_environment();
    } else {
        ft_printf("command not found: %s\n", args[0]);
    }
}


char **tokens_to_argv(t_token *tokens) {
    int count = ft_lstsize(tokens);
    char **args = malloc((count + 1) * sizeof(char *));
    if (!args) {
        perror("malloc() error");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (tokens) {
        args[i] = ft_strdup(tokens->text);
        tokens = tokens->next;
        i++;
    }
    args[i] = NULL;

    return args;
}


int main(void)
{
    t_mini  mini;
    t_token *tokens;

    ft_printf("\033[1;33mMINISHELL started!\033[0m\n");
    signal(SIGINT, handle_signal);
    while (1)
    {
        mini.cmd_line = prompt();
        if (!mini.cmd_line)
        {
            ft_printf("\n");
            exit(EXIT_SUCCESS);
        }
        if (mini.cmd_line && *mini.cmd_line)
        {
            tokens = input_tokenizer(mini.cmd_line);
            char **args = tokens_to_argv(tokens);

            execute_command(args);

            free(args);
            ft_free_tokens(tokens);
        }
        free(mini.cmd_line);
    }
    return (0);
}

// void	print_tokens(t_token *head)
// {
// 	while (head != NULL)
// 	{
// 		ft_printf("Recebido: %s \nToken de tipo: %d\n\n", head->text, head->type);
// 		head = head->next;
// 	}
// }

// // funcao para enfeitar o a palavra MINIHELL started!
// // sai em degrader.
// void	print_gradient(void)
// {
// 	char	*text;
// 	int		text_length;
// 	int		i;
// 	int		ansi_green;
// 	int		ansi_red;
// 	int		length;
// 	int		step;
// 	int		ansi_code;

// 	int green, red;
// 	length = 30;
// 	text = "MINIHELL started!";
// 	text_length = ft_strlen(text);
// 	step = length / text_length;
// 	i = 0;
// 	ft_printf("\033[1;");
// 	while (i <= length)
// 	{
// 		green = (255 * i) / length;
// 		red = 255 - green;
// 		ansi_green = (green * 5) / 255;
// 		ansi_red = (red * 5) / 255;
// 		ansi_code = 16 + ansi_green * 6 + ansi_red;
// 		ft_printf("\033[38;5;%dm", ansi_code);
// 		if (i / step < text_length)
// 		{
// 			ft_printf("%c", text[i / step]);
// 		}
// 		i++;
// 	}
// 	ft_printf("\033[0m\n");
// }
