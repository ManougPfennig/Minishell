/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:56:35 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/06 21:55:33 by mapfenni         ###   ########.fr       */
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

typedef struct s_lexer
{
	char			*str;
	int				token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct s_cmds
{
	char			**tab;
	char			*builtin;
	int				num_redir;
	char			*hd_file_name;
	t_lexer			*redir;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}				t_cmds;

typedef struct s_data
{
	char	*input;
	int		sigint;
	char	**builtins;
	char	*buffercwd;
	char	**copy_env;
	char	*home_env;
	int		buffersize;
	int		pipes;
	t_lexer	**lex;
	t_cmds	**cmd;
}				t_data;

typedef struct s_copy
{
	int	len;
	int	start;
	int	i;
	int	y;
}				t_copy;

typedef struct s_exec
{
	int	signal;
	int	old_pipe;
}				t_exec;

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
int				executor(t_data *data);
int				handle_heredocs(t_data *data);

// signal part

char			*ft_prompt(t_data *data);
void			ft_exitcmd(char *s);
void			ft_controlc(int signal);
char			*create_input(char *input);
void			ft_signal(void);
void			print_env(t_data *data);
char			**get_env(char	**env, t_data *data);
void			len_env(char **env, int i, int j);
void			print_env(t_data *data);
int				count(char *src);
void			ft_analyse(t_data *data, char *s);
void			ft_env(t_data *data, char *env);
void			ft_pwd(t_data *data, char *s);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strjoin_free(char const *s1, char const *s2, int val);
void			ft_cd(t_data *data, char *s);
void			get_home_env(t_data *data);
// print_lexer est à supprimer dans le produit fini.
void			print_lexer(t_lexer **lexed);
void			print_tab(char **tab);
void			print_cmd_list(t_data *data);

extern int		g_sig;

#endif