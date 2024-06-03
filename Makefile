CC = g++
CFLAGS = -std=c++20

NAME = database

EXEC = $(NAME)

OBJ = $(NAME).o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC) $(OBJ)
