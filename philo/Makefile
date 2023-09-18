CC = cc

CFLAGS = -Wall -Wextra -Werror -I. -MMD -g3

SRC_PATH = sources/

OBJS_PATH = obj/

SRC = error.c \
	ft_atoi.c \
	init.c \
	main.c \
	print_state.c \
	thread.c \
	do_state.c \
	waccess.c \
	time.c

OBJS = $(SRC:.c=.o)

DEP = $(SRC:.c=.d)

PREFC = $(addprefix $(SRC_PATH),$(SRC))

PREFO = $(addprefix $(OBJS_PATH),$(OBJS))

PREFD = $(addprefix $(OBJS_PATH),$(DEP))

OBJ_DIR = obj

NAME = philo

all : $(NAME)

$(NAME) : $(PREFO)
	@echo "Compilation de Philosophers en cours..."
	@$(CC) $(PREFO) -o $(NAME)
	@echo "Terminé!"

bonus : all

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(OBJS_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR)

fclean :
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)

re : fclean all

-include $(PREFD)

.PHONY : all clean fclean re