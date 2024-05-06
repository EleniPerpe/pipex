/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:05:23 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/02 18:38:30 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "Libft/libft.h"

void	child1(char **argv, int *pfd, char **env);
void	child2(char **argv, int *pfd, char **env);
char	**ft_split(char const *s, char c);
char	*path_finder(char **env, char *command, char **command_args);
void	free_arrays(char **command_args, char *command_path);
char	**split_command(char *arg);
char	*str_split(const char *s, int c, int *i);
char	*join_paths(char *path, char slash, char *command);
char	**make_res_split(char *arg);
void	handle_error(char *str, int exit_code);
int		handle_exit(int status);
char	**check_to_split_commands(char *argv);
char	**check_path(char **env);
void	free_array(char **array);
char	*check_quotes(char *arg);

#endif