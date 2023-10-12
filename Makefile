CFLAGS = -W -Wall -Wextra -I./include -g3

SRC = $(shell find . -name '*.c')
ASM_SRC = $(shell find . -name '*.asm')  # Ajoutez cette ligne pour les fichiers ASM

OBJ = $(SRC:.c=.o) $(ASM_SRC:.asm=.o)  # Mettez à jour la variable OBJ

TARGET = a.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.asm
	nasm -f elf64 $< -o $@ 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re:	fclean all
