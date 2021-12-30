#ifndef EXEC_H
# define EXEC_H

# define SUCCESS 	    1
# define FAIL           0
# define STDIN_BACKUP 	420
# define STDOUT_BACKUP  421

void        free_char_array(char **array);
int         chk_line(char *line);
void        free_all_list(t_linked_order *order);
void        free_linked_order(t_minishell *mini);

int         exec(t_minishell *mini);
int         redirect_handler(t_minishell *mini, int **pipe_fd);
int         do_redirect(t_linked_order *order, int **pipe_fd);
int         check_flag(t_minishell *mini);

int         mini_echo(t_minishell *mini, int fd_out);
int         mini_cd(t_minishell *mini);
int         mini_pwd(int fd_out);
int         mini_export(t_minishell *mini, int fd_out);
int         mini_unset(t_minishell *mini);
int         mini_env(t_minishell *mini, int fd_out);
int         mini_exit(t_minishell *mini);
int         extern_func_exec(t_minishell *mini, int *pipe_fd);


#endif
