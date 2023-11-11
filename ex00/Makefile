NAME := btc
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SOURCES = main.cpp
OBJECTS_DIR = objs
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)

fclean:
	rm -rf $(OBJECTS_DIR) $(NAME)

re: fclean all

git :
	git add -A
	git commit -m "auto commit"
	git push

.PHONY: all clean fclean re git

