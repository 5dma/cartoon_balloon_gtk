CC = gcc
OBJFILES = add_balloon.o add_text.o build_gui.o build_box_annotation.o build_box_theme.o build_box_configuration.o logging.o main.o process_image.o read_annotation.o read_json.o read_themes.o resize.o
CFLAGS = -g -Wall

all: balloon

balloon: $(OBJFILES)
	$(CC) -o $@ $^ `pkg-config --libs glib-2.0` `pkg-config --libs json-glib-1.0` `pkg-config --libs gtk4` `pkg-config --libs ImageMagick` `pkg-config --libs MagickWand`

add_balloon.o: add_balloon.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

add_text.o: add_text.c
	$(CC) $(CFLAGS) `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4`  -c $^

build_gui.o: build_gui.c
	$(CC) $(CFLAGS)  -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

logging.o: logging.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

main.o: main.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^
process_image.o: process_image.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

read_annotation.o: read_annotation.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` `pkg-config --cflags json-glib-1.0` $^

read_json.o: read_json.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` `pkg-config --cflags json-glib-1.0` $^

read_themes.o: read_themes.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` `pkg-config --cflags json-glib-1.0` $^

resize.o: resize.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

build_box_annotation.o: build_gui/build_box_annotation.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

build_box_theme.o: build_gui/build_box_theme.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

build_box_configuration.o: build_gui/build_box_configuration.c
	$(CC) $(CFLAGS) -c `pkg-config --cflags ImageMagick` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4` $^

.PHONY: clean
clean:
	rm -f $(OBJFILES)