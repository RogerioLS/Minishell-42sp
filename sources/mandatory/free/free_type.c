/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:34:57 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/06/29 16:00:13 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	ft_free_tokens(t_token *head)
{
	t_token	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->text);
		free(temp);
	}
}

void	ft_free_commands(t_command *head)
{
	t_command	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->text);
		free(temp);
	}
}

void	ft_free_string_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
	{
		return (NULL);
	}
	result = malloc(strlen(s1) + strlen(s2) + 1);
	if (!result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(result, s1);
	strcat(result, s2);
	free(s1);
	return (result);
}

void	free_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}
