/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:56:35 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/03 20:02:28 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
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
	int				num_redir;
	char			*hd_file_name;
	t_lexer			*redir;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}				t_cmds;

typedef struct s_data
{
	char	*input;
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

typedef struct s_quote
{
	char	*str;
	int		type;
}				t_quote;

typedef struct s_redir
{
	t_lexer	*new;
	t_lexer	*tmp;
	t_lexer	*tmp2;
}				t_redir;

struct s_lexer	**lexer(char *str);
char			*replace_env(char *str);
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
struct s_lexer	**lexer(char *str);
int				add_word(struct s_lexer **lexer, char *str, int token);
struct s_lexer	*ft_last_link(struct s_lexer **lexer);
char			*copy_word(char *str);
int				what_token(char *str);
int				is_token(char c);
int				has_token(char *str);
int				ft_strcmp(char *s1, char *s2);
int				parser(t_data *data);
char			*ft_strjoin_free(char const *s1, char const *s2, int val);
void			free_lexer(t_lexer **lexed);
void			ft_cd(t_data *data, char *s);
void			get_home_env(t_data *data);
char			remove_excess_quote(char *str);
struct s_lexer	**split_quote_wspace(char *str);
char			**lexer_split_quote(char *str);
int				contain_token(t_lexer **lexer, char *str);
void			is_in(char *in, char c);
void			find_redir(t_data *data);
void			nb_pipes(t_data *data);
int				check_error_lexer(t_data *data);
void			init_cmd_list(t_data *data);
void			find_redir(t_data *data);
void			store_cmd(t_data *data);
// print_lexer est à supprimer dans le produit fini.
void			print_lexer(t_lexer **lexed);
void			print_tab(char **tab);

#endif