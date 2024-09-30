#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := minishell
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -g3 #-lreadline 
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
GETNEXTLINE = get_next_line/*.c
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      errors.c \
                          execute.c \
                          expand.c \
                          expand_utils.c \
                          expand_var.c \
                          ft_execve.c \
                          ft_exit.c \
                          ft_unset.c \
                          init.c \
                          minishell.c \
                          null_args.c \
                          parse.c \
                          parse_utils.c \
                          pipes.c \
                          pipes_utils.c \
                          redir.c \
                          redir_file.c \
                          redir_utils.c \
                          signal.c \
                          utils.c \
                          utils2.c \
                          utils_env.c \
                          cd.c \
                          echo.c \
                          export.c \
                          export_utils2.c \
                          export_utils.c \
                          pwd.c \
                          env.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f


all:		${NAME}

${NAME}:	${OBJS}
			@$(MAKE) -C ./$(LIBFT_DIR) all
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} $(OBJS) $(LIBFT) $(GETNEXTLINE) -o ${NAME} -L/lib/x86_64-linux-gnu -lreadline -lncurses
			@echo "$(GREEN)$(NAME) created[0m ✔️"

			



gnl:		${GETNEXTLINE}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all
