#ifndef PARSE_H
# define PARSE_H

typedef struct s_gss
{
	int	cnt;
	int	begin;
	int	close;
	int	redir;
	int	len;
}	t_gss;

typedef struct s_parse
{
	int	move;
	int	close;
	int	end;
	int	prev;
}	t_parse;

char	*get_content(char *key, t_minishell *mini);
void	parse(t_minishell *mini, char *line);
void	reset_add(t_gss *val);
void	gss_init(t_gss *val);
void	parse_init(t_parse *val, t_minishell *mini);
void	free_key_value(t_minishell *mini);
int		rebuild_cmd(char *src, char *dest, t_minishell *mini);
int		ft_strcmp(const char *a, const char *b);
int		get_split_size(const char *s, const char c);
int		unclosed(char *str, char quote);
int		get_key(char *src, char **key);
int		env_cnt(char *str, int *size, t_minishell *mini);
int		env_key_size(char *str);
int		single_quote(t_minishell *mini, char *src, char **dest, int *src_move);
int		double_quote(t_minishell *mini, char *src, char **dest, int *src_move);
int		single_cpy(char *src, char **dest);
int		double_cpy(char *src, char **dest, t_minishell *mini);
t_token	*cmd_split(const char *line, const char pivot, int move, int token_i);
t_token	*rebuild_token(t_minishell *mini, t_token *token);

#endif