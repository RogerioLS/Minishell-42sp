#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*expandVariables(const char *input)
{
	char		*buffer;
	const char	*cursor;
	size_t		name_length;
	char		*name;
	char		*valeu;
	size_t		current_length;

	buffer = malloc(strlen(input) + 1);
	if (!buffer)
	{
		perror("malloc failed");
		return (NULL);
	}
	buffer[0] = '\0';
	cursor = input;
	while (*cursor)
	{
		if (*cursor == '$')
		{
			cursor++;
			name_length = strcspn(cursor, " $/\t\n,.");
			name = malloc(name_length + 1);
			if (!name)
			{
				perror("malloc failed");
				free(buffer);
				return (NULL);
			}
			strncpy(name, cursor, name_length);
			name[name_length] = '\0';
			valeu = getenv(name);
			free(name);
			if (valeu)
			{
				buffer = realloc(buffer, strlen(buffer) + strlen(valeu) + 1);
				if (!buffer)
				{
					perror("realloc failed");
					return (NULL);
				}
				strcat(buffer, valeu);
			}
			cursor += name_length;
		}
		else
		{
			current_length = strlen(buffer);
			buffer = realloc(buffer, current_length + 2);
			if (!buffer)
			{
				perror("realloc failed");
				return (NULL);
			}
			buffer[current_length] = *cursor++;
			buffer[current_length + 1] = '\0';
		}
	}
	return (buffer);
}

int	main(void)
{
	char	*input;
	char	*expanded;

	input = "Hello $USER, your home directory is $HOME.";
	expanded = expandVariables(input);
	if (expanded)
	{
		printf("Original: %s\n", input);
		printf("Expanded: %s\n", expanded);
		free(expanded);
	}
	return (0);
}
