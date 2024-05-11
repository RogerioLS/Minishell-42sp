#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*expandVariables(const char *input)
{
	char		*buffer;
	const char	*cursor;
	size_t		varNameLen;
			char varName[varNameLen + 1];
	char		*varValue;
	size_t		currentLength;

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
			varNameLen = strcspn(cursor, " $/\t\n");
			strncpy(varName, cursor, varNameLen);
			varName[varNameLen] = '\0';
			varValue = getenv(varName);
			if (varValue)
			{
				strcat(buffer, varValue);
			}
			cursor += varNameLen;
		}
		else
		{
			currentLength = strlen(buffer);
			buffer = realloc(buffer, currentLength + 2);
			if (!buffer)
			{
				perror("realloc failed");
				return (NULL);
			}
			buffer[currentLength] = *cursor++;
			buffer[currentLength + 1] = '\0';
		}
	}
	return (buffer);
}

int	main(void)
{
	char	*input;
	char	*expanded;

	input = "$HOME";
	expanded = expandVariables(input);
	if (expanded)
	{
		printf("Original: %s\n", input);
		printf("Expanded: %s\n", expanded);
		free(expanded);
	}
	return (0);
}
