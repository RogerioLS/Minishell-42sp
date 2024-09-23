/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:31:58 by codespace         #+#    #+#             */
/*   Updated: 2024/08/29 20:42:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

t_tree_node	*ft_build_execution_tree(t_token *token_list)
{
	t_tree_node	*root;

	root = ft_dalloc(1, sizeof(t_tree_node));
	if (!root)
	{
		perror("failed to build execution tree");
		return (NULL);
	}
	ft_split_tokens_into_tree(root, token_list);
	return (root);
}

void	ft_split_tokens_into_tree(t_tree_node *tree_node, t_token *token_list)
{
	t_token	*is_pipe;
	t_token	*is_redirect;

	is_pipe = ft_search_pipe(token_list);
	if (is_pipe)
		return (ft_split_list(tree_node, token_list, is_pipe));
	is_redirect = ft_search_redirect(token_list);
	if (is_redirect)
		return (ft_split_redirect(tree_node, token_list, is_redirect));
	else
		tree_node->token = token_list;
}

void	ft_split_list(t_tree_node *tree_node, t_token *token_list,
		t_token *token_to_cut)
{
	t_token	*right;

	if (!tree_node || !token_list || !token_to_cut)
		return ;
	tree_node->token = token_to_cut;
	right = ft_cut_token_list(token_list, token_to_cut);
	if (!right)
	{
		perror("failed to build execution tree");
		return ;
	}
	tree_node->left = ft_build_execution_tree(token_list);
	tree_node->right = ft_build_execution_tree(right);
}

t_token	*ft_cut_token_list(t_token *token_list, t_token *token_to_cut)
{
	t_token	*right;

	if (!token_list || !token_to_cut)
		return (NULL);
	right = token_to_cut->next;
	right->prev = NULL;
	if (token_to_cut->prev)
		token_to_cut->prev->next = NULL;
	token_to_cut->prev = NULL;
	token_to_cut->next = NULL;
	return (right);
}

void	ft_split_redirect(t_tree_node *tree_node, t_token *token_list,
		t_token *token_to_cut)
{
	if (!tree_node || !token_list || !token_to_cut)
		return ;
	tree_node->token = token_to_cut;
	tree_node->right = ft_get_redir_filename(token_to_cut->next);
	if (token_list == token_to_cut)
	{
		token_list = token_list->next->next;
		if (token_list)
			token_list->prev = NULL;
		token_to_cut->next->next = NULL;
		token_to_cut->prev = NULL;
	}
	else
	{
		token_to_cut->prev->next = token_to_cut->next->next;
		if (token_to_cut->next->next)
			token_to_cut->next->next->prev = token_to_cut->prev;
		token_to_cut->next->next = NULL;
		token_to_cut->prev = NULL;
	}
	tree_node->left = ft_build_execution_tree(token_list);
}
