NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	   ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	   ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	   ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

PRINTF_SRCS = ft_printf/ft_printf.c \
	      		ft_printf/ft_printf_utils.c \
			ft_printf/ft_putptr.c

GNL_SRCS = get_next_line/get_next_line.c

SRCS += $(PRINTF_SRCS) $(GNL_SRCS)
	
BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			 ft_lstmap.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -Ift_printf -Iget_next_line

# Colors
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
NC = \033[0m

# Verbose mode control
ifdef VERBOSE
    QUIET =
else
    QUIET = @
endif

# Progress tracking
COMPILED = 0
TOTAL_FILES = $(words $(SRCS) $(BONUS_SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Creating libft.a...$(NC)"
	$(QUIET)ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)✓ libft.a ready$(NC)"

bonus: $(OBJS) $(BONUS_OBJS)
	@echo "$(BLUE)Creating libft.a with bonus...$(NC)"
	$(QUIET)ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(GREEN)✓ libft.a with bonus ready$(NC)"

%.o: %.c
	@printf "$(BLUE)Building libft... $(NC)$(notdir $<)\n"
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning libft...$(NC)"
	$(QUIET)rm -f $(OBJS) $(BONUS_OBJS)
	$(QUIET)rm -f get_next_line/get_next_line_bonus.o get_next_line/get_next_line_utils_bonus.o

fclean: clean
	@echo "$(RED)Removing libft.a...$(NC)"
	$(QUIET)rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re