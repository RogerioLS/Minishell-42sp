/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:39:38 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/31 21:14:21 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	executor(t_tree_node *root)
{
	if (!root->token)
		return (SUCCESS);
	if (root->token->type == AND)
		return (execute_and(root->left, root->right));
	else if (root->token->type == OR)
		return (execute_or(root->left, root->right));
	else if (root->token->type == PIPE)
		return (execute_pipe(root->left, root->right));
	else if (root->token->type >= REDIR_APPEND
		&& root->token->type <= REDIR_OUT)
		return (execute_redirect(root->left, root->right, root->token->type));
	else if (root->token->type == OPEN_PAREN)
		return (execute_block(root));
	else
		return (execute_command(root));
}

int	execute_and(t_tree_node *left, t_tree_node *right)
{
	int	exit_status;

	exit_status = set_exit_status(executor(left));
	if (exit_status == SUCCESS)
		return (set_exit_status(executor(right)));
	return (exit_status);
}

int	execute_or(t_tree_node *left, t_tree_node *right)
{
	int	exit_status;

	exit_status = set_exit_status(executor(left));
	if (exit_status != SUCCESS && *get_exit_status() < 128)
		return (set_exit_status(executor(right)));
	return (exit_status);
}

int	execute_block(t_tree_node *root)
{
	t_tree_node	*block_root;
	t_token		*current;
	int			exit_status;
	int			pid;

	pid = fork();
	if (pid == -1)
		exit(ft_handle_error("fork"));
	if (pid == 0)
	{
		root->token = root->token->next;
		current = root->token;
		while (current->next)
			current = current->next;
		current->prev->next = NULL;
		if (ft_parser(root->token, &block_root) == SUCCESS)
			exit(executor(block_root));
	}
	wait_child_status(pid, &exit_status);
	return (exit_status);
}
