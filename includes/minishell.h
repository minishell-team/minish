#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

extern int g_exit; // exit함수에 사용할 종료 상태

typedef struct	s_err
{
	int				errcode;
	int				errindex;
	char			*errtoken;
}				t_err;

typedef struct	s_token
{
	char		*cmd; // 토큰 문자열
	char		redir_flag; // 리다이렉트여부
}				t_token;

typedef struct	s_linked_order
{// 다음 파이프 직전 까지 정보
	t_token			*cmdline;
	int				pipe_flag;
	int				exit_flag;
	int				right_flag;
	char			quote;
	char			*(redirect_filename[4]);
	//index 0 : left redirect char (<, <<);
	//index 1 : left redirect filename;
	//index 2 : righ redirect char (>, >>);
	//index 3 : righ redirect filename;
	struct s_err	err_manage;
	struct s_linked_order	*next;
	
}				t_linked_order;

typedef struct s_minishell
{
	char					**argv; //main에서 받아온 argv
	char					**env; //동적할당X 기본환경변수
	int						len; //환경변수 갯수
	char					**key; //환경변수 키
	char					**content; // 환경변수 값
	struct s_linked_order	*lo; //파이프 기준으로 나눈 링크드 리스트 
}				t_minishell;

# include "parse.h"
# include "exec.h"

#endif
