/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:54:32 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 19:54:38 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

//pino.c
void	init_stack(t_info *status);
void	put_to_list(char *line, t_stack *stack);
char	*put_space(char *line);
void	check_line(char *line, t_info *status);

void	ex_cd(t_info *status, t_stack *data);
void	ex_echo(t_info *status, t_stack *data);
void	ex_env(t_info *status, t_stack *data);
void	ex_exit(t_info *status, t_stack *data);
void	ex_export(t_info *status, t_stack *data);
void	ex_pwd(t_info *status, t_stack *data);
void	ex_unset(t_info *status, t_stack *data);

//export_utils
void	print_with_doublequotes(char *str);
int		valid_left(char *str, int flag);
int		plus_equal_or_not(char *str);
char	*no_left_but_plus(char *str);
void	print_export_env(t_list *env);
void	overwrite_envlist(t_list *env, char *str);

//exec_error
void	erro_msg_no_such_file(t_info *status, char *content);
void	erro_msg_is_a_directory(t_info *status, char *content);
void	erro_msg_permission_denied(t_info *status, char *content);
void	erro_msg_not_command_found(t_info *status, char *content);

void	is_non_xok(t_info *status);
void	is_directory_error(t_info *status, char *path);
void	is_no_file_error(t_info *status);
#endif