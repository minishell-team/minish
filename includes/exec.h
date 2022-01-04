#ifndef EXEC_H
# define EXEC_H

# define SUCCESS 	    1
# define FAIL           0
# define ERROR          -1
# define STDIN_BACKUP 	420
# define STDOUT_BACKUP  421
# define SKY            "\001\033[1;36m\002"
# define WHITE          "\001\033[0m\002"

void    free_char_array(char **array);
int     chk_line(char *line);
void    free_all_list(t_linked_order *order);
void    free_linked_order(t_minishell *mini);

void    init_signal(void);
void    exit_clean(t_minishell *mini, int error_code);
void    show_error(t_linked_order *order);
int     find_env(t_minishell *mini, char *key);
char	*readline_with_path(void);
void    show_exit_upline(void);

int     check_unique_key(t_minishell *mini, char *new_key, char *new_value);
void    alert_export_error(char *cmd, char *key);
void    show_declare_x(t_minishell *mini, int fd_out);
int     key_check_char(char c);
int     key_check_str(char *str, char eof);
void    free_trash(char **arr);

int     exec(t_minishell *mini);
int     redirect_handler(t_minishell *mini, int **pipe_fd);
int     do_redirect(t_linked_order *order, int **pipe_fd);
int     check_flag(t_minishell *mini);
void    alert_redirect_error(char *str, int exit_code);

int     mini_echo(t_minishell *mini, int fd_out);
int     mini_cd(t_minishell *mini);
int     mini_pwd(int fd_out);
int     mini_export(t_minishell *mini, int fd_out);
int     mini_unset(t_minishell *mini);
int     mini_env(t_minishell *mini, int fd_out);
int     mini_exit(t_minishell *mini);
int     extern_func_exec(t_minishell *mini, int *pipe_fd);
void    system_call_exec(t_minishell *mini, char *path, int *fds);

void    ascii_art(void);

#endif
