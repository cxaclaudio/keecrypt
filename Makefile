# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -lcrypto
SRC = src/main.c
TARGET = keecrypt

# Regra padrão
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Limpeza
clean:
	rm -f $(TARGET)
