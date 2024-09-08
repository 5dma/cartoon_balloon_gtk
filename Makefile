CC := gcc

all: main.c

	$(CC) -g -Wall -o balloon \
	`pkg-config --cflags glib-2.0` \
	`pkg-config --cflags json-glib-1.0` \
	`pkg-config --cflags gtk4` \
	`pkg-config --cflags ImageMagick` \
	-D NO_AT_BRIDGE=1 \
	$(wildcard *.c) \
	`pkg-config --libs glib-2.0` \
	`pkg-config --libs json-glib-1.0` \
	`pkg-config --libs gtk4` \
	`pkg-config --libs ImageMagick` \

