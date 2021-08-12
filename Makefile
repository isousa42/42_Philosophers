CC	= gcc
FLAGS = -Wall -Wextra -Werror -lpthread -std=c11 -ggdb3
RM	= rm -f

NAME = philo

SRCS = philo.c utils.c set_settings.c do_something.c lib_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : 
	gcc $(SRCS) $(FLAGS) -o $(NAME) 

clean:
	$(RM) $(OBJS) 


fclean: clean
	 	$(RM) $(NAME)

re: fclean all

.PHONY:		all clean fclean re 