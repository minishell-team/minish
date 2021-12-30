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
	int move;
	int close;
	int end;
	int prev;
}	t_parse;

void	parse(t_minishell *mini, char *line);
void	reset_add(t_gss *val);
void	gss_init(t_gss *val);
void	parse_init(t_parse *val);
void	rebuild_cmd(char *src, char *dest, t_minishell *mini);
int		unclosed(char *str, char quote);
int		env_cnt(char *str, int *size, t_minishell *mini);
t_token *cmd_split(const char *line, const char pivot, int move);
t_token *rebuild_token(t_minishell *mini, t_token *token);
#endif