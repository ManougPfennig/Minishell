/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:32:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/12/08 12:18:31 by nicolas          ###   ########.fr       */
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

typedef struct s_data
{
	char	*input;
	char	*buffercwd;
	int		buffersize;
	char	**copy_env;

}	t_data;

typedef struct s_lexer {
	char			*str;
	int				token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct s_copy {
	int	len;
	int	start;
	int	i;
	int	y;
}				t_copy;

struct s_lexer	**lexer(char *str);
int				main(int argc, char **argv, char **env);
char			*ft_prompt(t_data *data);
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_exitcmd(char *s);
int				ft_strcmp(char *s1, char *s2);
void			ft_controlc(int signal);
size_t			ft_strlen(const char *s);
char			*create_input(char *input);
void			ft_signal(void);
void			print_env(t_data *data);
char			**get_env(char	**env, t_data *data);
void			len_env(char **env, int i, int j);
void			print_env(t_data *data);
char			*ft_strdup(char *src);
int				count(char *src);
void			ft_analyse(t_data *data, char *s);
void			ft_env(t_data *data, char *env);
char			**ft_split(char const *s, char c);
void			ft_pwd(t_data *data, char *s);
struct s_lexer	**lexer(char *str);
int				add_word(struct s_lexer **lexer, char *str, int token);
struct s_lexer *ft_last_link(struct s_lexer **lexer);
char			*copy_word(char *str);
int				what_token(char word[2]);
int				is_token(char c);
#endif