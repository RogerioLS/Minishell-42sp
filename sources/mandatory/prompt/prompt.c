/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:05:13 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/02 13:06:19 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void initialize_shell(void) {
    ft_printf("\033[1;33mMINIHELL started!\033[0m\n");
}

int	afterprompt(int is_after)
{
	static int	after;

	if (is_after != -1)
		after = is_after;
	return (after);
}

void handle_single_quotes(char **input, char *result, size_t *res_len) {
    (*input)++;
    while (**input && **input != '\'') {
        result[(*res_len)++] = *(*input)++;
    }
    if (**input == '\'') (*input)++;
    result[*res_len] = '\0';
}

void handle_double_quotes(char **input, char *result, size_t *res_len) {
    (*input)++;
    while (**input && **input != '"') {
        if (**input == '$') {
            (*input)++;
            char varname[256];
            int i = 0;
            while ((*input)[i] && (ft_isalnum((*input)[i]) || (*input)[i] == '_')) {
                varname[i] = (*input)[i];
                i++;
            }
            varname[i] = '\0';
            char *value = getenv(varname);
            if (value) {
                ft_strcpy(&result[*res_len], value);
                *res_len += ft_strlen(value);
            }
            else {
                result[(*res_len)++] = '$';
                strcpy(&result[*res_len], varname);
                *res_len += ft_strlen(varname);
            }
            *input += i;
        } else if (**input == '\\') {
            (*input)++;
            if (**input) {
                result[(*res_len)++] = *(*input)++;
            }
        } else {
            result[(*res_len)++] = *(*input)++;
        }
    }
    if (**input == '"') (*input)++;
    result[*res_len] = '\0';
}


void parse_input(char *input, char *result) {
    size_t res_len = 0;
    while (*input) {
        if (*input == '\'') {
            handle_single_quotes(&input, result, &res_len);
        } else if (*input == '"') {
            handle_double_quotes(&input, result, &res_len);
        } else {
            result[res_len++] = *input++;
        }
    }
    result[res_len] = '\0';
}

char *prompt(void) {
    char *cmd_line = NULL;
    afterprompt(0);
    cmd_line = readline("\033[1;31mMINIHELL>$\033[0m ");
    if (!cmd_line) {
        ft_printf("Error reading input.\n");
        exit(EXIT_FAILURE);
    }
    afterprompt(1);
    if (cmd_line[0] != '\0') {
        add_history(cmd_line);
    }
    char *parsed_cmd = (char *)malloc(1024 * sizeof(char));
    if (parsed_cmd == NULL) {
        ft_printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    parse_input(cmd_line, parsed_cmd);
    free(cmd_line);
    return parsed_cmd;
}