NAME = philo
NAMEB = philo_bonus
SRCDIR = src
OBJDIR = obj
SRCBDIR = srcb
OBJBDIR = objb
SRCS = $(addprefix $(SRCDIR)/, main.c check_arg.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
SRCB = $(addprefix $(SRCBDIR)/,)
OBJB = $(patsubst $(SRCBDIR)/%.c, $(OBJBDIR)/%.o, $(SRCB))
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
HEADER = $(SRCDIR)/philo.h
HEADERB = $(SRCBDIR)/philo_bonus.h

all: $(NAME) 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER) Makefile
	@ mkdir -p $(OBJDIR)
	@ $(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(NAMEB)

$(NAMEB): $(OBJB) 
	$(CC) $(CFLAGS) $(OBJB) -o $(NAMEB)

$(OBJBDIR)/%.o: $(SRCBDIR)/%.c $(HEADERB) Makefile
	mkdir -p $(OBJBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJB)
	$(RM) $(OBJDIR) $(OBJBDIR)

fclean: clean
	$(RM) $(NAME) $(NAMEB)

re: fclean all

.PHONY: all clean fclean re bonus
