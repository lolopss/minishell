CC = @gcc
RM = @rm -f
FLAG = -Wall -Wextra -Werror
NAME = minishell
SRC = main.c			\
		utils_1.c		\
		utils_2.c		
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAG) -o $(NAME) $(OBJ) -lreadline
	@echo made
clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : minishell
