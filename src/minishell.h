/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:56:35 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/26 00:36:23 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
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
# define AMBIGUOUS 6
# define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:\
/usr/games:/usr/local/games:/snap/bin:/snap/bin"
# define CTRL_C_HD 300
# define IN_HD 400
# define NO_ERROR 0
# define ERROR 1
# define NO_FILE 0

typedef struct s_lexer
{
	char			*str;
	int				token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct s_exec
{
	int		fd_in;
	int		fd_out;
	int		*pipe_in;
	int		*pipe_out;
	char	**path;
	char	*test;
	char	**env_tab;
}				t_exec;

typedef struct s_env
{
	int				rank;
	int				equal;
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef struct s_cmds
{
	char			**tab;
	char			*builtin;
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
	char	*home_env;
	int		buffersize;
	int		pipes;
	t_lexer	**lex;
	t_cmds	**cmd;
	t_env	*copy_env;
	int		std_in;
	int		std_out;
	int		exit;
	int		**pipe_tab;
	pid_t	*pid_tab;
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

struct s_lexer	**lexer(t_data *data, char *str);
struct s_lexer	**split_quote_wspace(char *str);
char			**lexer_split_quote(char *str);
struct s_lexer	*ft_last_link(struct s_lexer **lexer);
char			*replace_env(t_data *data, char *str);
char			*special_env(char c);
int				is_envchar(char c);
char			*to_env(t_data *data, char *str, int i);
char			*copy_word(char *str);
int				add_word(struct s_lexer **lexer, char *str, int token);
void			is_in(char *in, char c);
int				is_token(char c);
int				has_token(char *str);
int				contain_token(t_lexer **lexer, char *str);
int				what_token(char *str);
char			remove_excess_quote(char *str);
void			move_back(char *str);
char			*find_env_patron(t_data *data, char *name);
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
t_lexer			*lexer_last_input(t_lexer *lex);
t_lexer			*lexer_last_output(t_lexer *lex);
int				get_input_fd(t_lexer *input, t_cmds *cmd);
int				get_output_fd(t_lexer *output);
int				check_acces_file(t_lexer *lex);
void			create_file(char *str);
void			cmd_execution(t_cmds *cmd, t_exec *exec);
int				which_cmd(t_cmds *cmd);
t_exec			*init_exec(t_data *data);
void			init_pipes(t_data *data);
int				input_fd(t_cmds *cmd);
int				output_fd(t_cmds *cmd);
void			simple_command(t_data *data, t_cmds *cmd);
int				is_direct_execution(char *str);
void			change_input_output(t_cmds *cmd, t_exec *exec);
void			multiple_commands(t_data *data);
int				loop_test(char **arg, t_exec *exec);
void			init_pid_tab(t_data *data);
void			close_all_pipes(t_cmds *cmd);
void			close_all_files(t_cmds *cmd);
void			prep_cmd_fds(t_data *data);

// signal part

int				is_digit(int c);
int				check_var(char *str);
void			ft_prompt(t_data *data);
void			ft_controlc(int signal);
char			*create_input(char *input);
void			ft_signal(void);
int				get_env(char **env, t_data *data);
void			len_env(char **env, int i, int j);
int				count(char *src);
int				ft_strcmp(char *s1, char *s2);

// builtin_part

int				ft_unset(t_cmds *cmd);
int				ft_cd(t_cmds *cmd);
int				ft_echo(t_cmds *cmd);
int				ft_exit(t_cmds *cmd);
int				ft_export(t_cmds *cmd);
int				ft_env(t_cmds *cmd);
int				ft_pwd(t_cmds *cmd);

// env part

void			get_home_env(t_cmds *cmd);
int				init_env(t_data *data, char **env);
char			*get_env_patron_3000(t_env *ptr, char *name);
t_env			*env_lst_new(char *env);
int				has_equal(char *str);
void			modify_export(t_data *data, char *arg);
void			env_lst_addback(t_data *data, t_env *new);
void			free_env(t_env *ptr);
void			rank_name(t_data *data);
char			**recup_tab(char *s);
// free part

void			free_exec(t_exec *exec);
void			free_after_execution(t_data *data);
int				multi_free(char *str, char *str2, char *str3);
void			free_env_list(t_data *data);
void			free_pid_tab(t_data *data);
void			free_pipe_tab(t_data *data);

// utils part

int				change_g_sig_to(int i);
long long		ft_atoill(char *str);
char			*ft_strjoin_free(char const *s1, char const *s2, int val);
int				str_is_digit(char *str);
int				len_tab(char **tab);
char			**copy_tab(char **tab);
int				putstr_fd_str(char *str, char *word, char *str2, int fd);
int				putstr_fd(char *str, int fd);
int				putstr_fd_char(char *str, char c, char *str2, int fd);
pid_t			do_fork(void);
void			do_dup2(int fd, int fd2);
int				do_dup(int fd);
void			do_pipe(int pipe_fd[2]);
void			do_close(int fd);
char			**env_to_tab(t_data	*data);
void			print_tab(char **tab);
int				cmd_lst_len(t_cmds *cmd);
int				len_lst(t_cmds *cmd);

extern int		g_sig;

#endif