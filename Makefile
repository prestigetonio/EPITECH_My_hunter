##
## EPITECH PROJECT, 2023
## makefile
## File description:
## emacs
##

NAME = my_hunter
SRC = src/my_hunter.c	\
		src/my_hunter2.c \

OBJ = $(SRC:.c=.o)
LIBS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -g

$(NAME): $(OBJ)
	gcc -o $(NAME) $(SRC) $(LIBS)

all: $(NAME)

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f \#*\#

fclean: clean
	rm -f $(NAME)

re: fclean all

install:
	cp $(NAME) /home/tonio/delivery/B-MUL-100-TLS-1-1-myhunter-tony.fournales/SFML-2.6.1/lib/

uninstall:
	rm -f /home/tonio/delivery/B-MUL-100-TLS-1-1-myhunter-tony.fournales/SFML-2.6.1/lib/$(NAME)
