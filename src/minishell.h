/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:56:35 by mapfenni          #+#    #+#             */
/*   Updated: 2023/12/09 11:57:16 by mapfenni         ###   ########.fr       */
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

typedef struct s_lexer {
	char			*str;
	int				token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct	s_data
{
	char	*input;
	char	*buffercwd;
	int		buffersize;
	char	**copy_env;
	t_lexer	**lex;
}				t_data;

typedef struct	s_copy {
	int	len;
	int	start;
	int	i;
	int	y;
}				t_copy;

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
struct s_lexer *ft_last_link(struct s_lexer **lexer);
char			*copy_word(char *str);
int				what_token(char word[2]);
int				is_token(char c);
int				ft_strcmp(char *s1, char *s2);
void			parsing(t_data *data);
char			*ft_strjoin_free(char const *s1, char const *s2, int val);
void			free_lexer(t_lexer **lexed);

#endif