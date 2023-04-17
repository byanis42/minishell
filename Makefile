SHELL	=	/bin/bash

# Variables

NAME		=	minishell
LIBFT		=	libft
INC			=	includes
HEADER		=	-I $(INC)
SRC_DIR		=	sources/
OBJ_DIR		=	obj/
CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra -I$(HOME)/.brew/opt/readline/include 
RM			=	rm -f
ECHO		=	echo -e

# Colors

DEF_COLOR	=	\033[0;39m
ORANGE		=	\033[0;33m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

# Sources

BIN_DIR		=	builtins/
BIN_FILES	=	ft_check_builtins ft_cd export unset builtin_utils

ENV_DIR		=	env/
ENV_FILES	=	get_envp_var create_env lst_env

MAIN_DIR	=	main/
MAIN_FILES	=	init_struct main signal signal_hdoc

PARS_DIR	=	parsing/
PARS_FILES	=	parse split_cmd split_line delete_quote is_directory

TOOLS_DIR	=	tools/
TOOLS_FILES	=	ft_error ft_error_bis ft_free utils utils_bis count_quote

PIPE_DIR	=	pipe/
PIPE_FILES	=	pipe path execute fork pipe_utils each_cmd

REDI_DIR	=	redirection/
REDI_FILES	=	redirect redi_utils redirect_infile redirect_outfile redi_utils_bis

SRC_FILES+=$(addprefix $(BIN_DIR),$(BIN_FILES))
SRC_FILES+=$(addprefix $(ENV_DIR),$(ENV_FILES))
SRC_FILES+=$(addprefix $(MAIN_DIR),$(MAIN_FILES))
SRC_FILES+=$(addprefix $(PARS_DIR),$(PARS_FILES))
SRC_FILES+=$(addprefix $(TOOLS_DIR),$(TOOLS_FILES))
SRC_FILES+=$(addprefix $(PIPE_DIR),$(PIPE_FILES))
SRC_FILES+=$(addprefix $(REDI_DIR),$(REDI_FILES))


SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

start:
			@make -C $(LIBFT)
			@cp $(LIBFT)/libft.a .
			@$(ECHO) -n "$(YELLOW)[Minishell]:\t$(DEF_COLOR)"
			@$(ECHO) -n "$(RED)[$(DEF_COLOR)"
			@make all
			@$(ECHO) -n "$(RED)]$(DEF_COLOR)"
			@$(ECHO) "$(GREEN) => 100%$(DEF_COLOR)"

all:		$(NAME)

$(NAME):	$(OBJ) $(OBJF)
			@$(CC) $(FLAGS) $(OBJ) $(HEADER) -lreadline libft.a -L$(HOME)/.brew/opt/readline/lib -o $(NAME)		

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJF)
			@$(ECHO) -n "$(ORANGE)=$(DEF_COLOR)"
			@$(CC) $(FLAGS) $(HEADER) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(BIN_DIR)
			@mkdir -p $(OBJ_DIR)$(ENV_DIR)
			@mkdir -p $(OBJ_DIR)$(MAIN_DIR)
			@mkdir -p $(OBJ_DIR)$(PARS_DIR)
			@mkdir -p $(OBJ_DIR)$(TOOLS_DIR)
			@mkdir -p $(OBJ_DIR)$(PIPE_DIR)
			@mkdir -p $(OBJ_DIR)$(REDI_DIR)


			@touch $(OBJF)

clean:
			@$(RM) -r $(OBJ_DIR)
			@$(RM) $(OBJF)
			@make clean -C $(LIBFT)
			@$(ECHO) -n "$(BLUE)[Minishell]:\tobject files$(DEF_COLOR)$(GREEN)  => Cleaned!$(DEF_COLOR)\n"

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) $(LIBFT)/libft.a
			@$(RM) libft.a
			@$(ECHO) -n "$(CYAN)[LIBFT]:\texec. files$(DEF_COLOR)$(GREEN)  => Cleaned!$(DEF_COLOR)\n"
			@$(ECHO) -n "$(CYAN)[Minishell]:\texec. files$(DEF_COLOR)$(GREEN)  => Cleaned!$(DEF_COLOR)\n"

re:			fclean start
			@$(ECHO) -n "$(GREEN)Cleaned and rebuilt everything for [Minishell]!$(DEF_COLOR)\n"

.PHONY:		start all clean fclean re
