/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:11 by roglopes          #+#    #+#             */
/*   Updated: 2024/03/31 18:41:35 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINI_SHELL_H
#	define MINI_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/errno.h>
#include <fcntl.h>

#	ifndef ARG_MAX
#	define ARG_MAX 4096  //Máximo do próprio shell//
#	endif

typedef struct			s_vars
{
	char				*name;
	char				*value;
	int					exported;
	int					aftercmd;
	struct s_vars		*next;
}						t_vars;

#	endif
