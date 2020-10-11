CC = gcc
CFLAGS = -g -Wall 
BINDIR = bin
SRCDIR = src
OBJDIR = $(BINDIR)/obj

LIBS := ncurses

EXEC := $(BINDIR)/test.out

# SRC := $(shell find $(SRCDIR) -name "*.c")
SRC := src/main.c
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ $(LDFLAGS) -l$(LIBS) -o $(EXEC)

$(OBJDIR)/%.o: %.c
	mkdir -p '$(@D)'
	$(CC) -l$(LIBS) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(BINDIR)
