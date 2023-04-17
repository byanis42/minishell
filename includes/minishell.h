/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:49:14 by byanis            #+#    #+#             */
/*   Updated: 2023/04/17 23:19:48 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/libftprintf.h"
# include <errno.h>
# include <stdbool.h>

# define PATH_LEN 1024

# define SUCCESS 1
# define ERROR 0

# define INFILE 1
# define D_INFILE 2
# define OUTFILE 3
# define D_OUTFILE 4

extern int	g_code_erreur;

typedef struct s_redi
{
	int				type;
	char			*file;
	int				file_fd;
	struct s_redi	*next;
}t_redi;

typedef struct s_var
{
	char			*name;
	char			*value;
	int				is_export;
	int				is_print;
	struct s_var	*next;
}t_var;

typedef struct s_board
{
	char	*line_cmd;
	char	**tab;
	int		nb_words;
	char	*cmd_path;
	int		res_fork;
	int		pipe_fd[2];
	int		var_env_empty;
	t_redi	*redi;
}t_board;

typedef struct s_data
{
	char	*line;
	int		nb_cmd;
	char	**tab_cmd;
	t_var	*env;
	t_board	*cmd;
}t_data;

//				MAIN
//main.c
void	each_things_to_do(t_data *minis, char **envp);
void	minishell_loop(char **envp);
void	control_c(void);
int		check_all_spaces(char *str);
//init_struct.c
void	delete_first_node_redi(t_board *cmd);
void	free_redi(t_data *minis);
void	init_struct(t_data *minis);
void	free_struct(t_data *minis);
//signal.c
void	init_signals(void);
void	signal_handler(int sig);
void	line_empty(t_data *minis);
void	init_signals_child(void);
void	signal_handler_child(int sig);
//signal_hdoc.c
void	init_signals_h_doc(void);
void	signal_handler_h_doc(int sig);
void	line_empty_h_doc(void);
//				REDIRECTION
//redirect.c
char	*cpy_redi(char *new_str, int i);
void	redirection(t_data *minis);
void	clean_this_redi(char *str, int j, int res);
void	stock_redi(t_data *minis, t_board *cmd, char *str, int res);
char	*get_file_redi(t_data *minis, char *str);
//redirect_utils.c
int		is_redi_infile(t_redi *ptr);
int		is_redi_outfile(t_redi *ptr);
void	try_open_file(t_redi *ptr);
void	open_all_redi_files(t_board *cmd);
void	close_all_redi_files(t_board *cmd);
//redirect_utils_bis.c
void	ft_pipe_redi(t_data *minis, int redi_pipe[2][2]);
void	close_redi_pipe(int redi_pipe[2][2]);
int		ft_is_redi(char *str, size_t i);
t_redi	*lst_last_redi(t_redi *lst);
void	lst_add_redi(t_redi **lst, t_redi *new);
//redirect_infile.c
int		d_infile_to_pipe(t_redi *ptr, int redi_pipe[2]);
int		infile_to_pipe(t_redi *ptr, int redi_pipe[2]);
int		redirect_infile(t_board *cmd, int redi_pipe[2]);
int		read_input_h_doc(t_redi *ptr, int redi_pipe[2], int *res);
t_redi	*last_redi_out(t_redi *redi);
//redirect_outfile.c
int		redirect_outfile(t_board *cmd, int redi_pipe[2]);
void	redirect_error(t_data *minis, int redi_pipe[2][2]);
//				PARSING
//parse.c
int		parse(t_data *minis, char *str);
int		nothing_after_redi(t_data *minis, char *str, int i);
int		check_after_redi(char *str, char *new_str, int j, int i);
int		unknow_env_redi(t_data *minis, char *str, int i);
int		pipe_at_end(char *str, int i);
//is_directory.c
void	check_directory(t_data *minis);
//ft_split_cmd.c
void	ft_split_cmd(t_data *minis);
char	**ft_split_each_cmd(char *str, t_board *cmd, t_data *minis);
char	*str_cpy_words(char *line, int *i);
int		ft_count_split(char *line);
int		ft_len_words(char *line);
//ft_split_line.c
void	ft_write(char *new, char *str, int *i, int *j);
void	line_to_cmd(t_data *minis);
char	*str_cpy_cmd(char *line, int *i, t_data *minis);
int		ft_count_command(char *line);
//delete_quote.c
void	delete_quote(t_data *minis);
char	*get_new_str(char *str);
void	write_to_new_doublequote(char *str, char *new, int *i, int *j);
void	write_to_new_singlequote(char *str, char *new, int *i, int *j);
int		count_new_quote(char *str);
//				ENV
//create_env.c
void	ft_create_env(t_data *minis, char **envp);
void	create_var(t_data *minis, char **envp, int i);
void	create_var_interr(t_data *minis);
void	ft_get_value(t_data *minis, char *str, t_var *ptr);
void	ft_get_name(char *str, t_var *ptr);
//lst_env.c
void	put_res_pipe(t_data *minis, int res);
void	lst_add(t_var **lst, t_var *new);
t_var	*lst_last(t_var *lst);
t_var	*lst_name_finding(t_var *lst, char *name);
void	ft_malloc_empty(t_data *minis, t_var *ptr);
//get_envp_var.c
void	put_env_var(t_data *minis);
char	*get_envp_var(t_data *minis, char *cmd, int *empty);
int		is_an_other_var_env(char *var_env);
char	*search_env_var(char *str, int i, t_data *minis);
int		ft_strlen_var(char *str, int j);
//				BUILTINS
//export.c
void	ft_export(t_data *minis, t_board *cmd);
int		export_arg(t_data *minis, t_board *cmd, int i);
void	ft_create_variable(t_data *minis, char *str);
void	ft_assign_new_value(t_data *minis, char *str, char *name);
char	*get_name(char *str, t_data *minis);
//ft_cd.c
void	ft_cd(t_data *minis, t_board *cmd);
int		cd_without_arg(t_data *minis, t_board *cmd);
void	ft_change_pwd(t_var *env, t_data *minis);
void	ft_change_oldpwd(t_var *env, t_data *minis);
int		access_check(char *path);
//ft_check_builtins.c
void	butiltins_without_fork(t_data *minis, t_board *cmd, int i);
void	builtins_with_fork(t_data *minis, t_board *cmd);
void	ft_free_exit(t_data *minis);
void	ft_exit(t_data *minis, t_board *cmd);
int		ft_is_digital(char *str);
//buitlin_utils
void	ft_echo(t_board *cmd);
void	ft_echo_bis(t_board *cmd, int i, int option);
void	ft_envp(t_data *minis);
void	ft_pwd(void);
//unset.c
void	ft_unset(t_data *minis, t_board *cmd);
t_var	*ft_delete_node(char *str, t_var *env);
t_var	*ft_delete_first_node(t_var *env);
void	ft_delete_last_node(t_var *env);
void	ft_delete_middle_node(t_var *env);
//				TOOLS
//utils.c
int		len_env_var(char *str, int j);
int		ft_len_cmd(char *line);
char	*ft_cpy_new_line_bis(char *cmd, char *var_env, char *new, int i);
char	*ft_cpy_new_line(char *cmd, char *var_env, int i, t_data *minis);
int		is_redi_d_infile(t_redi *ptr);
//utils_bis.c
int		ft_is_not_fork(t_board *cmd);
int		ft_is_builtins(t_board *cmd);
void	print_list(t_var *exp, int i);
char	*list_chr(t_var *exp, char *str_name);
int		ft_strcmp(char *s1, char *s2);
//ft_free.c
void	free_struct_cmd(t_data *minis);
void	free_tab(char **tab, int i);
void	free_list(t_var *env);
//count_quote.c
int		count_to_new_quote(char *str, int *i, int quote);
int		is_no_open_single_quote(char *line, int i);
int		is_no_open_quote(char *line, int i);
//ft_error.c
void	ft_error(char *message, t_data *minis, int z, int is_perror);
void	ft_error_ptr(t_data *minis, t_var *ptr, int error);
void	ft_error_fork(t_data *minis, int redi_pipe[2][2], int y);
//ft_error_bis.c
void	ft_error_to_pipe(t_data *minis, int i);
//				PIPE
//pipe.c
int		ft_pipe(t_data *minis, char **envp);
void	create_pipe(t_data *minis);
void	find_path_struct(t_data *minis);
void	close_all_pipes(t_data *minis);
//path.c
char	*ft_try_path(t_data *minis, char *path, t_board *cmd);
int		ft_move_path(char *path, int *path_len);
char	*check_acces_path(t_data *minis, t_board *cmd);
char	*cpy_path(t_data *minis, t_board *cmd, char *path, int *path_len);
void	cpy_cmd(t_board *cmd, char *poss, int i);
//execute.c
int		ft_execute(t_data *minis, char **envp);
void	ft_execute_bis(t_data *minis, char **envp, int i);
//each_cmd.c
void	last_cmd(t_data *minis, char **envp, int i);
void	middle_cmd(t_data *minis, char **envp, int i);
void	first_cmd(t_data *minis, char **envp, int i);
int		just_one_cmd(t_data *minis, t_board *cmd, char **envp);
int		is_empty(char *str);
//fork.c
void	fork_one_cmd(t_data *minis, char **envp,
			int redi_pipe[2][2], t_board *cmd);
void	fork_first_cmd(t_data *minis, char **envp, int redi_pipe[2][2], int i);
void	fork_middle_cmd(t_data *minis, char **envp, int redi_pipe[2][2], int i);
void	fork_last_cmd(t_data *minis, char **envp, int redi_pipe[2][2], int i);
void	wait_all_pid(t_data *minis, int *res);
//pipe_utils.c
int		error_or_not_fork(t_data *minis, t_board *cmd, int z, int i);
void	close_for_cmd_pipe(t_data *minis, int z, int i);
int		infile_error_message(t_board *cmd, int print);
int		check_acces_read(t_redi *ptr, int print);
void	command_error_message(t_data *minis, int print);

#endif
