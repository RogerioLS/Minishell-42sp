/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:39:38 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/20 15:58:59 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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
			exit(ft_executor(block_root));
	}
	ft_wait_child_status(pid, &exit_status);
	return (exit_status);
}

int	ft_executor(t_tree_node *root)
{
	if (root->token->type == PIPE)
		return (ft_execute_pipe(root->left, root->right));
	else if (root->token->type >= REDIR_APPEND
		&& root->token->type <= REDIR_OUT)
		return (ft_execute_redirect(root->left, root->right, root->token->type));
	else if (root->token->type == OPEN_PAREN)
		return (execute_block(root));
	else
		return (ft_execute_command(root));
}
