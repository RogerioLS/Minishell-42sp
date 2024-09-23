/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:12:49 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/23 19:12:51 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_wait_child_status(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (*status == 1)
		return ;
	else if (WIFSIGNALED(*status))
	{
		if (*status == SIGINT)
			write(STDIN_FILENO, "\n", 1);
		*status = WTERMSIG(*status) + 128;
	}
}

int	execute_child(int fd, int *pipe, t_tree_node *node)
{
	int	exit_status;

	dup2(pipe[fd], fd);
	ft_close_pipe(pipe);
	exit_status = ft_executor(node);
	ft_free_memory();
	ft_free_env();
	exit(exit_status);
}

int	ft_execute_pipe(t_tree_node *left, t_tree_node *right)
{
	int	child_pid[2];
	int	pipe_fd[2];
	int	exit_status[2];

	pipe(pipe_fd);
	child_pid[0] = fork();
	ft_setup_fork_signal_handlers(child_pid[0]);
	if (child_pid[0] == 0)
		execute_child(STDOUT_FILENO, pipe_fd, left);
	child_pid[1] = fork();
	ft_setup_fork_signal_handlers(child_pid[1]);
	if (child_pid[1] == 0)
		execute_child(STDIN_FILENO, pipe_fd, right);
	ft_close_pipe(pipe_fd);
	ft_wait_child_status(child_pid[0], &exit_status[0]);
	ft_wait_child_status(child_pid[1], &exit_status[1]);
	if (exit_status[0] == SIGINT + 128)
		return (exit_status[0]);
	return (exit_status[1]);
}
