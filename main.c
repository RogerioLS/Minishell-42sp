#include <stdio.h>
#include <stdlib.h>

// retorna o comprimento do segmento inicial de (s) que não contém nenhum caractere que está presente na string reject. Ele vai buscar o primeiro caractere de s que está em reject e retorna o índice onde ele está.
size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

// retorna o comprimento do segmento inicial de (s) que contém apenas caracteres que estão presentes na string accept. Ele vai buscar o primeiro caractere de s que não está em accept e retorna o índice onde ele está.
size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				break ;
			j++;
		}
		if (!accept[j])
			return (i);
		i++;
	}
	return (i);
}

char *ft_strtok(char *str, const char *delim) {
    static char *last;
    char *ret;

    if (str != NULL) {
        last = str;
    }
	else if (last == NULL || *last == '\0')
	{
		return (NULL);
	}
    last += ft_strspn(last, delim);  // Pula delimitadores
    if (*last == '\0') {
        return NULL;  // Não há mais tokens
    }
    ret = last;  // Início do token
    last += ft_strcspn(last, delim);  // Vai até o próximo delimitador
    if (*last != '\0') {
        *last = '\0';  // Termina o token atual
        last++;  // Pula o delimitador
    } else {
        last = NULL;  // Não há mais tokens
    }
    return ret;
}



int main() {
    char input[] = "ro ge > ls ol";
    char *token;

    token = ft_strtok(input, "");
    while (token != NULL) {
        printf("Token: '%s'\n", token);
        token = ft_strtok(NULL, " ");
    }

    return 0;
}