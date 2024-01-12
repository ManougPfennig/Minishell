/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:56:35 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/12 13:56:02 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define LESS_THAN 1
# define MORE_THAN 2
# define PIPE 3
# define LESS_LESS 4
# define MORE_MORE 5
# define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:\
/usr/games:/usr/local/games:/snap/bin:/snap/bin"
# define CTRL_D_HD 300
# define CTRL_C_HD 300
# define IN_HD 400
# define NO_ERROR 0
# define ERROR 1

typedef struct s_lexer
{
	char			*str;
	int				token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct s_exec
{
	int		signal;
	int		last_pipe;
	int		fd_in;
	int		fd_out;
	char	**path;
	char	*test;
	int		stdin_cpy;
	int		stdout_cpy;
}				t_exec;

typedef struct s_cmds
{
	char			**tab;
	char			*builtin;
	int				num_redir;
	char			*hd_file_name;
	t_lexer			*redir;
	t_exec			*exec;
	struct s_cmds	*next;
	struct s_cmds	*prev;
	struct s_data	*data;
}				t_cmds;

typedef struct s_data
{
	char	*input;
	int		sigint;
	int		init_env;
	char	**builtins;
	char	*buffercwd;
	char	**copy_env;
	char	**new_copy_env;
	char	**env_export;
	char	*home_env;
	int		buffersize;
	int		pipes;
	t_lexer	**lex;
	t_cmds	**cmd;
	int		std_in;
	int		std_out;
}				t_data;

typedef struct s_copy
{
	int	len;
	int	start;
	int	i;
	int	y;
}				t_copy;

typedef struct s_redir
{
	t_lexer	*new;
	t_lexer	*tmp;
	t_lexer	*tmp2;
}				t_redir;

// lexer part
struct s_lexer	**lexer(char *str);
struct s_lexer	**split_quote_wspace(char *str);
char			**lexer_split_quote(char *str);
struct s_lexer	*ft_last_link(struct s_lexer **lexer);
char			*replace_env(char *str);
int				is_envchar(char c);
char			*to_env(char *str, int i);
char			*copy_word(char *str);
int				add_word(struct s_lexer **lexer, char *str, int token);
void			is_in(char *in, char c);
int				is_token(char c);
int				has_token(char *str);
int				contain_token(t_lexer **lexer, char *str);
int				what_token(char *str);
char			remove_excess_quote(char *str);
void			free_lexer(t_lexer **lexed);

// parser part
int				parser(t_data *data);
int				check_error_lexer(t_data *data);
void			find_redir(t_data *data);
void			nb_pipes(t_data *data);
void			init_cmd_list(t_data *data);
void			find_redir(t_data *data);
void			store_cmd(t_data *data);
void			return_builtin(t_data *data);

// executor part
void			executor(t_data *data);
int				handle_heredocs(t_data *data);
int				check_input_list(t_cmds *cmd);
void			change_input_output(t_cmds *cmd, t_exec *exec, int pipe_fd[2]);
t_lexer			*lexer_last_input(t_lexer *lex);
t_lexer			*lexer_last_output(t_lexer *lex);
int				get_input_fd(t_lexer *input, t_cmds *cmd);
int				get_output_fd(t_lexer *output);
int				check_acces_file(t_lexer *lex);
void			create_file(char *str);
void			cmd_execution(t_cmds *cmd, t_exec *exec);
void			which_cmd(t_cmds *cmd);

// signal part

char			*find_variable(t_cmds *cmd, int j);
int				is_digit(int c);
int 			check_var(char *str);
void			init_export_tab(t_data *data);
char			*var_env_export(char *s);
char			*ft_prompt(t_data *data);
char			*ft_addstring(char *s, char *s2);
char			**copy_tab(char **tab);
int 			there_is_egual(char *str);
void			ft_echo(t_cmds *cmd);
void			ft_exit(t_cmds *cmd);
void			ft_export(t_cmds *cmd);
void			ft_controlc(int signal);
char			*create_input(char *input);
void			ft_signal(void);
void			print_env(t_data *data);
char			**get_env(char	**env, t_data *data);
void			len_env(char **env, int i, int j);
int				count(char *src);
void			ft_analyse(t_data *data, char *s);
void			ft_env(t_cmds *cmd);
void			ft_pwd(t_cmds *cmd);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strjoin_free(char const *s1, char const *s2, int val);
int				len_tab(char **tab);
void			ft_cd(t_cmds *cmd);
void			get_home_env(t_cmds *cmd);
int				str_is_digit(char *str);

// print_lexer est à supprimer dans le produit fini.
void			print_lexer(t_lexer **lexed);
void			print_tab(char **tab);
void			print_cmd_list(t_data *data);

extern int		g_sig;

#endif