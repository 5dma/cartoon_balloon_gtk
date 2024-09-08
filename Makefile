CC := gcc

all: main.c

	$(CC) -g -Wall -o balloon \
	`pkg-config --cflags glib-2.0` \
	`pkg-config --cflags json-glib-1.0` \
	`pkg-config --cflags gtk4` \
	`pkg-config --cflags ImageMagick` \
	$(wildcard *.c) \
	`pkg-config --libs glib-2.0` \
	`pkg-config --libs json-glib-1.0` \
	`pkg-config --libs gtk4` \
	`pkg-config --libs ImageMagick` \
	`pkg-config --libs MagickWand`

