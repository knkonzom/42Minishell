NAME	=	minishell

SOURCE	=	$(wildcard src/*.c)

OBJECTS	=	$(SOURCE:.c=.o)

HEADER	=	includes/minishell.h

LIBS	=	-lreadline

CFLAGS	=	-Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(OBJECTS)
		gcc $(SOURCE) $(LIBS) -o minishell

clean:
		/bin/rm -f $(OBJECTS)

fclean:	clean
		/bin/rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re