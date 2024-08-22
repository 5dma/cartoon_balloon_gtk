CC := gcc

all: main.c

	$(CC) -g -Wall -o balloon \
	`pkg-config --cflags glib-2.0` \
	`pkg-config --cflags json-glib-1.0` \
	`pkg-config --cflags MagickWand` \
	$(wildcard *.c) \
	`pkg-config --libs MagickWand` \
	`pkg-config --libs glib-2.0` \
	`pkg-config --libs json-glib-1.0` 