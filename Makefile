CC = gcc
OBJFILES = add_balloon.o add_text.o build_gui.o build_box_annotation.o build_box_theme.o build_box_configuration.o logging.o main.o process_image.o read_annotation.o read_configuration.o read_themes.o resize.o initialize_gui.o memory_management.o
CFLAGS = -g -Wall `pkg-config --cflags ImageMagick` `pkg-config --cflags json-glib-1.0` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4`

all: balloon

balloon: $(OBJFILES)
	$(CC) -o $@ $^ `pkg-config --libs glib-2.0` `pkg-config --libs json-glib-1.0` `pkg-config --libs gtk4` `pkg-config --libs ImageMagick` `pkg-config --libs MagickWand`

add_balloon.o: add_balloon.c
	$(CC) $(CFLAGS) -c $^

add_text.o: add_text.c
	$(CC) $(CFLAGS) -c $^

build_gui.o: build_gui.c
	$(CC) $(CFLAGS)  -c $^

logging.o: logging.c
	$(CC) $(CFLAGS) -c $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

process_image.o: process_image.c
	$(CC) $(CFLAGS) -c $^

read_annotation.o: read_annotation.c
	$(CC) $(CFLAGS) -c $^

read_configuration.o: read_configuration.c
	$(CC) $(CFLAGS) -c $^

read_themes.o: read_themes.c
	$(CC) $(CFLAGS) -c $^

resize.o: resize.c
	$(CC) $(CFLAGS) -c $^

build_box_annotation.o: build_gui/build_box_annotation.c
	$(CC) $(CFLAGS) -c $^

build_box_theme.o: build_gui/build_box_theme.c
	$(CC) $(CFLAGS) -c $^

build_box_configuration.o: build_gui/build_box_configuration.c
	$(CC) $(CFLAGS) -c $^


initialize_gui.o: build_gui/initialize_gui.c
	$(CC) $(CFLAGS) -c $^

memory_management.o: memory_management.c
	$(CC) $(CFLAGS) -c $^


.PHONY: clean
clean:
	rm -f $(OBJFILES)