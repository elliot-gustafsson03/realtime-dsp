# Compiler settings
CC = gcc
CFLAGS = -Wall -O3
LDFLAGS = -lportaudio -lm

# The name of the final executable
TARGET = dsp.app

# All source files that need to be compiled
SRCS = main.c \
       processing/processor.c \
	   util/operations.c \
       processing/tremolo.c \
       processing/delay.c

# Convert the .c filenames into .o (object) filenames
OBJS = $(SRCS:.c=.o)

# Default target runs when you just type 'make'
all: $(TARGET)

# Link all object files together into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile each .c file into a .o object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Mark these targets as commands, not files
.PHONY: all clean
