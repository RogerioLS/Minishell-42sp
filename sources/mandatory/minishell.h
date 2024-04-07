/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 06:37:07 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/07 06:39:57 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINISHELL_H
#	define MINISHELL_H

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
