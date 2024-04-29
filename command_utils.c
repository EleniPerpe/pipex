/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:07:02 by eperperi          #+#    #+#             */
/*   Updated: 2024/04/29 16:09:34 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**check_to_split_commands(char *argv)
{
	char	**temp;

	if (argv[0] == 'a' && argv[1] == 'w' && argv[2] == 'k')
		temp = split_command(argv);
	else
		temp = ft_split(argv, ' ');
	return (temp);
}

char	**split_command(char *arg)
{
	int		i;
	char	*command;
	char	**res;

	if (str_split(arg, ' ', &i) == NULL)
		res = make_res_split(arg);
	else
	{
		res = (char **)malloc(3 * sizeof(char *));
		if (res == NULL)
			return (NULL);
		i = 0;
		command = str_split(arg, ' ', &i);
		if (command == NULL)
			return (NULL);
		res[0] = ft_substr(arg, 0, i);
		if (res[0] == NULL)
			return (NULL);
		res[1] = ft_substr(arg, i + 1, ft_strlen(arg) - i);
		if (res[1] == NULL)
			return (NULL);
		res[2] = NULL;
	}
	return (res);
}

char	**make_res_split(char *arg)
{
	char	**res;

	res = (char **)malloc(2 * sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = arg;
	res[1] = NULL;
	return (res);
}

char	*str_split(const char *s, int c, int *i)

{
	*i = 0;
	while (s[*i] != '\0')
	{
		if (s[*i] == (char)c)
		{
			return ((char *)&s[*i]);
		}
		(*i)++;
	}
	if (s[*i] == (char)c)
	{
		return ((char *)&s[*i]);
	}
	return (NULL);
}

void	free_array(char **command_args)
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
}
