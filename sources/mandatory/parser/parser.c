/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:18:15 by codespace         #+#    #+#             */
/*   Updated: 2024/08/29 22:22:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	ft_parser(t_token *tokens, t_tree_node **root)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (ft_check_syntax(current) != SUCCESS)
			return (ft_set_exit_status(SYNTAX_ERROR));
		/*if (current->type == REDIR_HEREDOC && current->next->type == WORD \
			&& create_heredoc_file(current->next) != SUCCESS)
			return (*ft_get_exit_status());*/
		current = current->next;
	}
	*root = ft_build_execution_tree(tokens);
	return (SUCCESS);
}

int	ft_check_syntax(t_token *current)
{
	if (current->type == PIPE)
		return (ft_check_control_operator_rule(current));
	else if (current->type >= REDIR_APPEND && current->type <= REDIR_OUT)
		return (ft_check_redirect_rule(current));
	return (SUCCESS);
}

int	ft_check_control_operator_rule(t_token *token)
{
	if (token->prev == NULL || token->prev->type <= PIPE)
		return (ft_syntax_error(token->value));
	if (token->next == NULL || token->next->type <= PIPE)
		return (ft_syntax_error(token->value));
	return (SUCCESS);
}

int	ft_check_redirect_rule(t_token *token)
{
	if (token->next == NULL || token->next->type != WORD)
		return (ft_syntax_error(token->value));
	return (SUCCESS);
}
