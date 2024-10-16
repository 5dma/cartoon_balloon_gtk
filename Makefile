CC = gcc
OBJFILES = add_balloon.o add_text.o build_gui.o build_box_annotation.o build_box_theme.o build_box_configuration.o logging.o main.o process_image.o read_annotation.o read_configuration.o read_themes.o resize.o initialize_gui.o memory_management.o cleanup.o build_controllers_annotation.o build_controllers_window.o
CFLAGS = -g -Wall `pkg-config --cflags ImageMagick` `pkg-config --cflags json-glib-1.0` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4`

all: balloon

balloon: $(OBJFILES)
	$(CC) -o $@ $^ `pkg-config --libs glib-2.0` `pkg-config --libs json-glib-1.0` `pkg-config --libs gtk4` `pkg-config --libs ImageMagick` `pkg-config --libs MagickWand`

add_balloon.o: add_balloon.c headers.h
	$(CC) $(CFLAGS) -c $^

add_text.o: add_text.c headers.h
	$(CC) $(CFLAGS) -c $^

build_gui.o: build_gui.c headers.h
	$(CC) $(CFLAGS)  -c $^

logging.o: logging.c headers.h
	$(CC) $(CFLAGS) -c $^

main.o: main.c headers.h
	$(CC) $(CFLAGS) -c $^

process_image.o: process_image.c headers.h
	$(CC) $(CFLAGS) -c $^

read_annotation.o: read_annotation.c headers.h
	$(CC) $(CFLAGS) -c $^

read_configuration.o: read_configuration.c headers.h
	$(CC) $(CFLAGS) -c $^

read_themes.o: read_themes.c headers.h
	$(CC) $(CFLAGS) -c $^

resize.o: resize.c headers.h
	$(CC) $(CFLAGS) -c $^

build_box_annotation.o: build_gui/build_box_annotation.c
	$(CC) $(CFLAGS) -c $^

build_box_theme.o: build_gui/build_box_theme.c
	$(CC) $(CFLAGS) -c $^

build_box_configuration.o: build_gui/build_box_configuration.c
	$(CC) $(CFLAGS) -c $^


initialize_gui.o: build_gui/initialize_gui.c
	$(CC) $(CFLAGS) -c $^

memory_management.o: memory_management.c headers.h
	$(CC) $(CFLAGS) -c $^

cleanup.o: cleanup.c headers.h
	$(CC) $(CFLAGS) -c $^

build_controllers_annotation.o: build_controls/build_controllers_annotation.c headers.h
	$(CC) $(CFLAGS) -c $^

build_controllers_window.o: build_controls/build_controllers_window.c headers.h
	$(CC) $(CFLAGS) -c $^

.PHONY: clean
clean:
	rm -f $(OBJFILES) headers.h.gch