/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:24:40 by roglopes          #+#    #+#             */
/*   Updated: 2024/05/05 17:48:19 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*tmp;

	tmp = dest;
	while ((*dest++ = *src++) != '\0')
		;
	return (tmp);
}

void	process_arguments(char **args, char *path, int *long_format)
{
	int	i;

	i = 1;
	while (args[i] != NULL && i < 3)
	{
		if (args[i][0] == '-')
		{
			if (args[i][1] == 'l')
			{
				*long_format = 1;
			}
		}
		else
		{
			ft_strcpy(path, args[i]);
		}
		i++;
	}
}

void	print_file_info(struct dirent *entry, char *path)
{
	char		full_path[MAX_PATH_LEN];
	struct stat	file_info;
	int			path_len;
	int			entry_len;
	char		permissions[11];

	path_len = ft_strlen(path);
	entry_len = ft_strlen(entry->d_name);
	if (path_len + 1 + entry_len >= MAX_PATH_LEN)
	{
		ft_printf("Path is too long\n");
		return ;
	}
	ft_strcpy(full_path, path);
	full_path[path_len] = '/';
	ft_strcpy(full_path + path_len + 1, entry->d_name);
	if (stat(full_path, &file_info) == 0)
	{
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
		ft_printf("%s %3ld %-8d %-8d %8ld %.12s %s\n", permissions,
			file_info.st_nlink, file_info.st_uid, file_info.st_gid,
			file_info.st_size, ctime(&file_info.st_mtime) + 4, entry->d_name);
	}
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
