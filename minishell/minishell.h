/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:00:20 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/30 11:14:10 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <sys/param.h>

# define BUFFER_SIZE 1024

typedef struct s_flags
{
	int		pipe;
	int		redirect;
	int		quote;
	int		dollar_special;
}			t_flags;

typedef struct s_env
{
	char			**env;
	char			*name;
	char			*content;
	char			*path;
	int				num_env;
	struct s_env	*next;
}			t_env;

typedef struct s_pipe
{
	int		fd[2][2];
	int		in;
	int		out;
	int		last;
	int		out_error;
}		t_pipe;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			*cmd;
	char			**arg;
	int				num_arg;
	t_pipe			*pipe;
	t_flags			*flags;
	t_env			*env;
}			t_cmd;

typedef struct s_shell
{
	char			buffer[BUFFER_SIZE]; //
	char			**argv; // copia de los argumentos
	t_env			*env; // variables de entorno
	char			**env_copy;// copia variables de entorno
	char			**path;
	int				total_chars;
	int				bash_lvl;
	t_cmd			*cmd;
	t_flags			*flags;
}			t_shell;

//funciones
void		recive_args(t_shell *shell);
int			check_spaces(char *c);
void		exit_error(char *str, int n);
void		free_array(char **array);
int			start_line(t_shell **shell, char *input, char ***lines);
int			check_lines(t_shell *shell, t_cmd **cmd, char *input);
int			ft_check_quote(char *input, int simple, int doble, t_shell *shell);
int			ft_check_quote_pair(char *input, int *i, char quote);
char		**ft_split_pipes(char *str);
int			ft_count_pipes(char *str);
int			isdifoperator(char c);
int			get_next_quote(int i, char *str, char c);
int			ft_count_args(char *str);
int			check_null_args(char *s);
char		*change_null_args(char *s, t_cmd *cmd);
void		expand(t_cmd **cmd);
int			check_dolar(char *str);
int			check_dolar_and_digit(char *s);
int			special_digit(int i);
char		*change_dolar_x_var(t_cmd *cmd, char *s, char *var_reminder);
char		*quit_dollar_and_digit(char *s, int i, int j);
char		*ft_change_var(t_cmd *cmd, char *s, char **var_reminder);
char		*ft_replace_value(char *s);
char		*ft_replace_value2(char *s, int i, int j);
char		*ft_name_var(char *line);
int			check_special_char(char c);
int			search_next_char(char *s, char c, int j);
char		*ft_split_var(char *str, int i, t_cmd *cmd);
char		*cmd_name_var(t_cmd *cmd, char *line, char *name_var);
char		*ft_add_var_value(char *s1);
char		*change_line_value(char *line, char *var);
char		*ft_strjoin_special(char *s1, char *s2, size_t i, size_t c);
int			check_prime(char *s);
char		*replace_prime(char *s);
t_cmd		*ft_last(t_cmd **cmd);
int			var_strcmp(char *s1, char *s2);
int			ft_count_pipes(char *str);
char		**fill_memory(char *str, char **res);
int			check_pipe_arg(char *str);
void		put_error(char *bash, char *file, char *error);
int			check_redir(char **arg, int i);
int			redir_type(char *str);
char		operator_char(int n);
char		*remove_quotes(char *str, char c);
char		*ft_craft_result(char *line_final, char *line, char *var, int c);
int			check_nonpipas(t_cmd *cmd, char *command);
char		*noquotes(char *str);
void		execute_nopipas(t_cmd *cmd, char *temp_cmd);
void		setfds(t_pipe *pipe, int i);
void		setpipes(t_pipe *pipes, int i);
int			is_redir(char **arg);
void		redir(t_cmd *cmd);
int			get_next_diff(int i, char *str);
char		**remove_one(char **arg, int i);
void		put_in_file(int type, t_cmd *cmd, char *file);
int			get_from_file(t_cmd *cmd, char *file, int i);
void		get_input(t_cmd *cmd, char *stop);
void		clear_lst(t_cmd **cmd);
char		*str_tolower(char *str);
int			ft_try_to_exec(t_cmd *cmd, char *absolute_path,
				char *search_path, char	*temp);
char		*value_dolar_path(char *s);
int			check_access(char *path, t_cmd *cmd, t_env *env);
char		**arg_with_command(t_cmd *cmd);
t_pipe		*init_pipes(void);
void		execute_cmd(t_cmd **cmd, t_pipe *pipes, int i);
t_shell		*init(char **env);
t_cmd		*ft_last(t_cmd **cmd);
void		many_args(char **argv);
int			ft_count_env(char **arg, int len);
void		ft_exit(t_cmd *cmd, char *temp, int i);
int			check_only_num(char *s);
int			ft_atoi_error(int *atoi_error);
int			ft_unset(t_cmd **cmd);
int			ft_unset_strcmp(char *s, t_env *env);
int			ft_special_strcmp(char *s1, char *s2);
char		**convert_to_env(char **arg, int len);

//señales
void		wait_signal(int signal);

//biltings
int			ft_echo(t_cmd **cmd);
int			is_flag(char *s);
int			ft_pwd(int i);
int			ft_cd(t_cmd **cmd);
void		value_pwd(char *s, t_cmd *cmd, int control);
int			ft_env(t_cmd *cmd);
int			ft_export(t_cmd **cmd);
int			wrong_exp(char c);
int			new_vars1(t_cmd *cmd, char *binary);
void		new_vars2(t_cmd **cmd, char *binary, int i, char **aux);
char		*first_alph(char **temp);
char		*add_quotes(char *s);
int			count_env(char **arg, int len);
char		**check_ord(char **res, t_cmd *cmd);
void		export_var(t_cmd *cmd);
int			export_parse(t_cmd *cmd, char *array, int x, int flag);
char		*actual_path(int i);

#endif
