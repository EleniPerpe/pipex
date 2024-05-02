/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:04:42 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/02 15:58:45 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pfd[2];
	pid_t	pid;
	int		status;

	if (argc != 5)
	{
		perror("Error: wrong count of arguments");
		exit(EXIT_FAILURE);
	}
	env = check_path(env);
	if (pipe(pfd) == -1)
		handle_error("pipe", EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		handle_error("fork", EXIT_FAILURE);
	if (pid == 0)
		child1(argv, pfd, env);
	child2(argv, pfd, env);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid, &status, 0);
	status = handle_exit(status);
	return (EXIT_SUCCESS);
}

void	child1(char **argv, int *pfd, char **env)
{
	int		fd_in;
	char	**command_args;
	char	*command_path;

	command_args = check_to_split_commands(argv[2]);
	if (command_args == NULL)
		handle_error("command not found", 127);
	command_path = path_finder(env, command_args[0], command_args);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		free(command_path);
		free_array(command_args);
		handle_error(argv[1], EXIT_FAILURE);
	}
	close(pfd[0]);
	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(pfd[1], STDOUT_FILENO) == -1)
		handle_error("dup2", EXIT_FAILURE);
	close(fd_in);
	if (execve(command_path, command_args, env) == -1)
	{
		free_array(command_args);
		free(command_path);
		close(pfd[1]);
		handle_error("execve", EXIT_FAILURE);
	}
}

void	child2(char **argv, int *pfd, char **env)
{
	int		fd_out;
	char	**command_args;
	char	*command_path;

	fd_out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd_out == -1)
		handle_error(argv[4], EXIT_FAILURE);
	command_args = check_to_split_commands(argv[3]);
	if (command_args == NULL)
		handle_error("command not found", 127);
	command_path = path_finder(env, command_args[0], command_args);
	close(pfd[1]);
	if (dup2(fd_out, STDOUT_FILENO) == -1 || dup2(pfd[0], STDIN_FILENO) == -1)
		handle_error("dup2", EXIT_FAILURE);
	if (execve(command_path, command_args, env) == -1)
	{
		free_array(command_args);
		free(command_path);
		close(pfd[0]);
		close(fd_out);
		handle_error("execve", EXIT_FAILURE);
	}
}

void	handle_error(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

int	handle_exit(int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = EXIT_FAILURE;
	return (status);
}
