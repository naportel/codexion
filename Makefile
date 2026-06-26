NAME = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f
SCRS =
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -g

all: $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
