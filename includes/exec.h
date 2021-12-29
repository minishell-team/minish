#ifndef EXEC_H
# define EXEC_H

void	    free_char_array(char **array);
int			chk_line(char *line);
void		free_all_list(t_linked_order *order);

int	        exec(t_minishell *mini, char **av);
int	        redirect_fd(t_minishell *mini, int *pipe_fd);




#endif
