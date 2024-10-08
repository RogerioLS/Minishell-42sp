/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:39:48 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/31 21:25:38 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	tmp = ft_dalloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && quote == str[i])
			quote = '\0';
		else if ((str[i] == '\"' || str[i] == '\'') && quote == '\0')
			quote = str[i];
		else
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	retokenize(t_token **token)
{
	t_token	*next;
	t_token	*current;
	char	**tokens;
	int		i;

	current = *token;
	next = (*token)->next;
	tokens = ft_split((*token)->value, ' ');
	if (*tokens)
	{
		(*token)->value = *tokens;
		i = 1;
		while (tokens[i])
		{
			(*token)->next = ft_token_lst_new(tokens[i], WORD);
			(*token) = (*token)->next;
			i++;
		}
		(*token)->next = next;
		(*token) = current;
	}
	else
		(*token)->value = "\0";
}

void	handle_empty_value(t_token **current, t_tree_node **cmd_node)
{
	if ((*current)->prev)
		(*current)->prev->next = (*current)->next;
	if ((*current)->next)
		(*current)->next->prev = (*current)->prev;
	if (*((*cmd_node)->token->value) == '\0')
	{
		(*cmd_node)->token = (*cmd_node)->token->next;
		if ((*cmd_node)->token)
			(*cmd_node)->token->prev = NULL;
	}
}
