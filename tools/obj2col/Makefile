SRCDIR = src
OBJDIR = build
INC_DIR = include
BINDIR = $(N64_INST)/bin

CFLAGS += -I$(INC_DIR) -O3 -g

TARGET = $(BINDIR)/obj2col
SRC = $(SRCDIR)/main.c
OBJ = $(OBJDIR)/main.o

all: $(TARGET)
.PHONY: all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LINKFLAGS)

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
.PHONY: clean
