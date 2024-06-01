#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char	*expandVariables(const char *input)
// {
// 	char		*buffer;
// 	const char	*cursor;
// 	size_t		name_length;
// 	char		*name;
// 	char		*valeu;
// 	size_t		current_length;

// 	buffer = malloc(strlen(input) + 1);
// 	if (!buffer)
// 	{
// 		perror("malloc failed");
// 		return (NULL);
// 	}
// 	buffer[0] = '\0';
// 	cursor = input;
// 	while (*cursor)
// 	{
// 		if (*cursor == '$')
// 		{
// 			cursor++;
// 			name_length = strcspn(cursor, " $/\t\n,.");
// 			name = malloc(name_length + 1);
// 			if (!name)
// 			{
// 				perror("malloc failed");
// 				free(buffer);
// 				return (NULL);
// 			}
// 			strncpy(name, cursor, name_length);
// 			name[name_length] = '\0';
// 			valeu = getenv(name);
// 			free(name);
// 			if (valeu)
// 			{
// 				buffer = realloc(buffer, strlen(buffer) + strlen(valeu) + 1);
// 				if (!buffer)
// 				{
// 					perror("realloc failed");
// 					return (NULL);
// 				}
// 				strcat(buffer, valeu);
// 			}
// 			cursor += name_length;
// 		}
// 		else
// 		{
// 			current_length = strlen(buffer);
// 			buffer = realloc(buffer, current_length + 2);
// 			if (!buffer)
// 			{
// 				perror("realloc failed");
// 				return (NULL);
// 			}
// 			buffer[current_length] = *cursor++;
// 			buffer[current_length + 1] = '\0';
// 		}
// 	}
// 	return (buffer);
// }

// int	main(void)
// {
// 	char	*input;
// 	char	*expanded;

// 	input = "Hello $USER, your home directory is $HOME.";
// 	expanded = expandVariables(input);
// 	if (expanded)
// 	{
// 		printf("Original: %s\n", input);
// 		printf("Expanded: %s\n", expanded);
// 		free(expanded);
// 	}
// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da lista ligada de tokens
typedef struct s_token
{
	char			*text;
	int				type;
	struct s_token	*next;
}					t_token;

// Função para criar um novo nó
t_token	*create_token(const char *text, int type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
	{
		perror("malloc failed");
		return (NULL);
	}
	node->text = strdup(text);
	if (!node->text)
	{
		perror("strdup failed");
		free(node);
		return (NULL);
	}
	node->type = type;
	node->next = NULL;
	return (node);
}

// Função para adicionar um novo nó ao final da lista
void	append_token(t_token **head, const char *text, int type)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = create_token(text, type);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

// Função para liberar a memória da lista
void	free_tokens(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->text);
		free(temp);
	}
}

// Função para expandir variáveis de ambiente
char	*expand_variable(const char *variable)
{
	char	*value;

	value = getenv(variable);
	return (value ? strdup(value) : NULL);
}

// Função auxiliar para processar texto não-variável
void	append_char_to_expanded(char **expanded, const char **cursor)
{
	size_t	current_length;

	current_length = strlen(*expanded);
	*expanded = realloc(*expanded, current_length + 2);
	if (!*expanded)
	{
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	(*expanded)[current_length] = **cursor;
	(*expanded)[current_length + 1] = '\0';
	(*cursor)++;
}

// Função auxiliar para expansão das variáveis
void	append_variable_to_expanded(char **expanded, const char **cursor)
{
	size_t	name_length;
	char	*name;
	char	*value;

	(*cursor)++;
	name_length = strcspn(*cursor, " $/\t\n,.");
	name = strndup(*cursor, name_length);
	if (!name)
	{
		perror("malloc failed");
		free(*expanded);
		exit(EXIT_FAILURE);
	}
	value = expand_variable(name);
	free(name);
	if (value)
	{
		*expanded = realloc(*expanded, strlen(*expanded) + strlen(value) + 1);
		if (!*expanded)
		{
			perror("realloc failed");
			exit(EXIT_FAILURE);
		}
		strcat(*expanded, value);
		free(value);
	}
	*cursor += name_length;
}

// Função principal para expandir tokens
void	expand_token(t_token *token)
{
	const char	*cursor;
	char		*expanded;

	cursor = token->text;
	expanded = malloc(strlen(token->text) + 1);
	if (!expanded)
	{
		perror("malloc failed");
		return ;
	}
	expanded[0] = '\0';
	while (*cursor)
	{
		if (*cursor == '$')
		{
			append_variable_to_expanded(&expanded, &cursor);
		}
		else
		{
			append_char_to_expanded(&expanded, &cursor);
		}
	}
	free(token->text);
	token->text = expanded;
}

void	expanda_variables_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		expand_token(current);
		current = current->next;
	}
}

int	main(void)
{
	t_token *tokens = NULL;
	append_token(&tokens, "$USER", 5);
		// Adiciona um token com o texto "$USER" e tipo 5
	append_token(&tokens, "Your home directory is $HOME.", 5);
		// Adiciona um token com o texto e tipo 5

	printf("Original Tokens:\n");
	for (t_token *temp = tokens; temp != NULL; temp = temp->next)
	{
		printf("Recebido: %s \nToken de tipo: %d\n", temp->text, temp->type);
	}

	expanda_variables_tokens(tokens);

	printf("\nExpanded Tokens:\n");
	for (t_token *temp = tokens; temp != NULL; temp = temp->next)
	{
		printf("Recebido: %s \nToken de tipo: %d\n", temp->text, temp->type);
	}

	free_tokens(tokens);
	return (0);
}