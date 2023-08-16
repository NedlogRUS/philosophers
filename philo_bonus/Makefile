NAME = philo_bonus
SRCDIR = src
OBJDIR = obj
SRCS = $(addprefix $(SRCDIR)/, main.c check_arg.c time_utils.c initializer.c philo.c \
	eat_sleep_think_repeat.c eat_die_checkers.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g
HEADER = $(SRCDIR)/philo.h

all: $(NAME) 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER) Makefile
	@ mkdir -p $(OBJDIR)
	@ $(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
