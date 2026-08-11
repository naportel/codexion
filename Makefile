NAME = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f
SRCS = src/main.c \
       src/heap/heap.c \
       src/heap/init.c \
       src/parsing/parsing.c \
       src/threads/init.c \
       src/threads/join.c \
       src/threads/routines.c \
       src/utils/coder.c \
       src/utils/dongles.c \
       src/utils/error.c \
       src/utils/printlog.c \
       src/utils/time.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -Iincludes -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -g

all: $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
