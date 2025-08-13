NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDLIBS = -lreadline

# Colors for output
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m

# Verbose mode control
ifdef VERBOSE
    QUIET =
else
    QUIET = @
endif

# Directories
SRC_DIR = src
BUILTIN_DIR = $(SRC_DIR)/builtins
EXEC_DIR = $(SRC_DIR)/exec
MINISHELL_DIR = $(SRC_DIR)/minishell
PARSER_DIR = $(SRC_DIR)/parser
REDIRECT_DIR = $(SRC_DIR)/redirections
SIGNAL_DIR = $(SRC_DIR)/signal
TOKEN_DIR = $(SRC_DIR)/token
INCLUDE_DIR = include
LIBFT_DIR = libft

# Source files
BUILTIN_SRCS = $(BUILTIN_DIR)/builtins.c $(BUILTIN_DIR)/echo.c $(BUILTIN_DIR)/pwd.c $(BUILTIN_DIR)/cd.c $(BUILTIN_DIR)/cd_utils.c $(BUILTIN_DIR)/env.c $(BUILTIN_DIR)/exit.c $(BUILTIN_DIR)/export.c $(BUILTIN_DIR)/export_utils.c $(BUILTIN_DIR)/unset.c $(BUILTIN_DIR)/env_expansion.c $(BUILTIN_DIR)/env_var_utils.c $(BUILTIN_DIR)/error_utils.c
EXEC_SRCS = $(EXEC_DIR)/exec_cmd.c $(EXEC_DIR)/pipe_exec.c $(EXEC_DIR)/pipe_utils.c $(EXEC_DIR)/exec_utils.c
MINISHELL_SRCS = $(MINISHELL_DIR)/minishell.c $(MINISHELL_DIR)/env_utils.c $(MINISHELL_DIR)/input_utils.c $(MINISHELL_DIR)/path_utils.c
PARSER_SRCS = $(PARSER_DIR)/parser.c $(PARSER_DIR)/parser_utils.c $(PARSER_DIR)/parse_helpers.c $(PARSER_DIR)/redir.c
REDIRECT_SRCS = $(REDIRECT_DIR)/redirections.c $(REDIRECT_DIR)/redirections_utils.c
SIGNAL_SRCS = $(SIGNAL_DIR)/signals.c
TOKEN_SRCS = $(TOKEN_DIR)/token.c $(TOKEN_DIR)/token_utils.c
UTILS_SRCS = $(SRC_DIR)/utils/clean.c $(SRC_DIR)/utils/util.c

SRCS = $(BUILTIN_SRCS) $(EXEC_SRCS) $(MINISHELL_SRCS) $(PARSER_SRCS) $(REDIRECT_SRCS) $(SIGNAL_SRCS) $(TOKEN_SRCS) $(UTILS_SRCS)
OBJS = $(SRCS:.c=.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(LIBFT_DIR)/get_next_line

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(BLUE)Building libft...$(NC)"
	$(QUIET)$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BLUE)Linking $(NAME)...$(NC)"
	$(QUIET)$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) built successfully!$(NC)"

%.o: %.c
	@echo "$(YELLOW)Compiling:$(NC) $<"
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	$(QUIET)rm -f $(OBJS)
	$(QUIET)$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	$(QUIET)rm -f $(NAME)
	$(QUIET)$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re