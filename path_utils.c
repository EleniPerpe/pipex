/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:54:05 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/02 17:19:45 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_finder(char **env, char *command, char **command_args)
{
	int		i;
	char	**paths;
	char	*join_path;

	check_path(env);
	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0 && env[i] != 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		join_path = join_paths(paths[i], '/', command);
		if (access(join_path, F_OK | X_OK) == 0)
			return (free_array(paths), join_path);
		free(join_path);
		i++;
	}
	free_array(paths);
	free_array(command_args);
	handle_error("command not found", 127);
	return (NULL);
}

char	*join_paths(char *path, char slash, char *command)
{
	size_t	path_len;
	size_t	command_len;
	char	*ptr;
	size_t	i;

	i = 0;
	path_len = ft_strlen(path);
	command_len = ft_strlen(command);
	ptr = (char *)malloc((path_len + command_len + 2) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < path_len)
	{
		ptr[i] = path[i];
		i++;
	}
	ptr[i] = slash;
	i = 0;
	while (i < command_len)
	{
		ptr[path_len + 1 + i] = command[i];
		i++;
	}
	ptr[path_len + command_len + 1] = '\0';
	return (ptr);
}

char	**check_path(char **env)
{
	if (env[0] == NULL)
	{
		env = (char **)ft_calloc (2, sizeof(char *));
		if (env == NULL)
			handle_error("pipex", EXIT_FAILURE);
		env[0] = ft_strdup("PATH=usr/bin/:.");
		env[1] = NULL;
	}
	return (env);
}
