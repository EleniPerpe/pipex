/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:06:16 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/02 18:06:58 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

void	free_arrays(char **command_args, char *command_path)
{
	int	i;

	i = 0;
	while (command_args[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(command_args[i]);
		i--;
	}
	free(command_args);
	free(command_path);
}
