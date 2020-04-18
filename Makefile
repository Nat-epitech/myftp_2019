##
## EPITECH PROJECT, 2018
## Strace Makefile
## File description:
## Nathan DP Makefile (v1.0)
##

NAME	= myftp

CC = gcc

SRC	=	$(wildcard src/*.c)

OBJ	=	$(SRC:.c=.o)

OBJDIR	=	Objects

FINAL_OBJ = $(OBJDIR)/*o

CFLAGS += -Wall -Wextra -Iincludes

DEBUG := debug

$(DEBUG): CFLAGS	+= -g3 -ggdb

END         =   \033[0m
BOLD        =   \033[1m
RED         =   \033[31m
GREEN       =   \033[32m
YELLOW      =   \033[33m
PURPLE      =   \033[35m
CYAN        =   \033[36m
WHITE       =   \033[37m

all: $(NAME)

$(DEBUG):	fclean $(NAME)

$(NAME): $(OBJ) $(OBJDIR)
	@$(CC) $(FINAL_OBJ) -o $(NAME) -g3 --pedantic $(CFLAGS) && echo "\n$(CYAN)[$(GREEN)$(BOLD)Success$(END)$(CYAN)$(BOLD)] Moving Objects file(s) in folder : $(PURPLE)$(OBJDIR)$(END)" && \
echo "$(CYAN)[$(GREEN)$(BOLD)Success$(END)$(CYAN)$(BOLD)] Binary $(PURPLE)$(NAME)$(END)$(CYAN)$(BOLD) Successfully created with flags : $(PURPLE)$(CFLAGS)$(END)"

$(OBJDIR):
	@mkdir $(OBJDIR)
	@mv src/*.o $(OBJDIR)

clean:
	@$(RM) -rf $(OBJDIR)
	@$(RM) $(OBJ)
	@echo "$(CYAN)[$(GREEN)$(BOLD)Success$(END)$(CYAN)$(BOLD)] Objects file(s) removed$(END)"

fclean: clean
	@$(RM) $(NAME) && echo "$(CYAN)[$(GREEN)$(BOLD)Success$(END)$(CYAN)$(BOLD)] Workspace cleaned$(END)"

re: fclean all

%.o:    %.c
	@$(CC) $(LDFLAGS) -c $< -o $@ $(CFLAGS) $(LDLIBS) && echo "$(CYAN)[$(GREEN)$(BOLD)Success$(END)$(CYAN)$(BOLD)]$(CYAN) $<$(END)"\
|| echo "$(RED)[ERROR] $(BOLD)Failed to compile : $<$(END)" || clean

.PHONY: all clean fclean re

