/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:13:15 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/23 19:13:18 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	open_redir_file(t_tree_node *right, int redir_type, int *fd)
{
	if (redir_type == REDIR_APPEND)
		*fd = open(right->token->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (redir_type == REDIR_HEREDOC || redir_type == REDIR_IN)
		*fd = open(right->token->value, O_RDONLY, 0644);
	else if (redir_type == REDIR_OUT)
		*fd = open(right->token->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*fd == -1)
		return (ft_handle_error(right->token->value));
	return (SUCCESS);
}

int	dup2_redir_file(int redir_type, int *fd)
{
	int	exit_status;

	exit_status = -1;
	if (redir_type == REDIR_APPEND || redir_type == REDIR_OUT)
		exit_status = dup2(*fd, STDOUT_FILENO);
	else if (redir_type == REDIR_HEREDOC || redir_type == REDIR_IN)
		exit_status = dup2(*fd, STDIN_FILENO);
	if (exit_status == -1)
		return (ft_handle_error("dup2"));
	close(*fd);
	return (SUCCESS);
}

int	ft_execute_redirect(t_tree_node *left, t_tree_node *right, int redir_type)
{
	int		fd;
	int		std_fd[2];
	int		exit_status;
	char	*before_expansion;

	exit_status = SUCCESS;
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	fd = -1;
	before_expansion = right->token->value;
	expand_tokens(right);
	if ((*before_expansion != '\0' && !right->token) || right->token->next)
		return (!!ft_fprintf(STDERR_FILENO, "%s: ambiguous redirect\n",
				before_expansion));
	if (open_redir_file(right, redir_type, &fd) != SUCCESS)
		return (FAILURE);
	if (dup2_redir_file(redir_type, &fd) != SUCCESS)
		return (FAILURE);
	if (left->token)
		exit_status = ft_executor(left);
	dup2(std_fd[0], STDIN_FILENO);
	dup2(std_fd[1], STDOUT_FILENO);
	return (exit_status);
}
