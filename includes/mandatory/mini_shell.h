/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:11 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/13 16:30:35 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../../libft/include/ft_printf.h"
# include "../../libft/include/get_next_line.h"
# include "../../libft/include/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

# define ARG_MAX 4096 // Máximo do próprio shell//

typedef struct s_mini
{
	char			*name;
	char			*cmd_line;
	int				exported;
	int				aftercmd;
	struct s_mini	*next;
}					t_mini;

// Utils
char	*ft_strtok(char *str, const char *delim);
char	*ft_antispace(char *buff);
char	*ft_firstword(char *buff);

// Variables
int		ft_exit(char *buff);
bool	commandline_var(char *cmd);
bool	validate_name(char *var_name);

#endif
