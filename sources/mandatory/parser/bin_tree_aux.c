/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:38:20 by codespace         #+#    #+#             */
/*   Updated: 2024/09/01 20:18:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

t_token	*ft_search_pipe(t_token *token_list)
{
	t_token	*current;

	current = ft_token_lst_get_last(token_list);
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		current = current->prev;
	}
	return (NULL);
}

t_token	*ft_search_redirect(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type >= REDIR_APPEND && current->type <= REDIR_OUT)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_tree_node	*ft_get_redir_filename(t_token *redir)
{
	t_tree_node	*filename;

	filename = ft_dalloc(1, sizeof(t_tree_node));
	if (!filename)
	{
		perror("failed to build execution tree");
		return (NULL);
	}
	else
	{
		filename->token = redir;
		filename->token->prev = NULL;
		filename->left = NULL;
		filename->right = NULL;
	}
	return (filename);
}
