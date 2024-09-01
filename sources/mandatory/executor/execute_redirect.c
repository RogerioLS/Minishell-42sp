/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:29:35 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/31 21:26:46 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	execute_redirect(t_tree_node *left, t_tree_node *right, int redir_type)
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
		return (!!printf("%s: ambiguous redirect\n", before_expansion));
	if (open_redir_file(right, redir_type, &fd) != SUCCESS)
		return (FAILURE);
	if (dup2_redir_file(redir_type, &fd) != SUCCESS)
		return (FAILURE);
	if (left->token)
		exit_status = executor(left);
	dup2(std_fd[0], STDIN_FILENO);
	dup2(std_fd[1], STDOUT_FILENO);
	return (exit_status);
}

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
