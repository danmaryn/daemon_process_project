CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
TARGET = build/daemon_app
SRCS = src/main.c src/daemon_core.c src/logger.c
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))

all: build_dir $(TARGET)

build_dir:
	mkdir -p build

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build