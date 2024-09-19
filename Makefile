CC = gcc

all: balloon

balloon: add_balloon.o add_text.o build_gui.o build_box_annotation.o logging.o main.o process_image.o read_annotation.o read_json.o read_themes.o resize.o
	$(CC) -g -Wall -o $@ $^ `pkg-config --libs glib-2.0` `pkg-config --libs json-glib-1.0` `pkg-config --libs gtk4` `pkg-config --libs ImageMagick` `pkg-config --libs MagickWand`

add_balloon.o: add_balloon.c
	$(CC) -Wall  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

add_text.o: add_text.c
	$(CC) -Wall `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4`  -c $^

build_gui.o: build_gui.c
	$(CC) -Wall  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

logging.o: logging.c
	$(CC) -Wall  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

main.o: main.c
	$(CC) -Wall  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^
process_image.o: process_image.c
	$(CC) -Wall  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

read_annotation.o: read_annotation.c
	$(CC) -Wall  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` `pkg-config --cflags json-glib-1.0` $^

read_json.o: read_json.c
	$(CC) -Wall  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` `pkg-config --cflags json-glib-1.0` $^

read_themes.o: read_themes.c
	$(CC) -Wall  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` `pkg-config --cflags json-glib-1.0` $^

resize.o: resize.c
	$(CC) -Wall  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

build_box_annotation.o: build_gui/build_box_annotation.c
	$(CC) -Wall  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^


