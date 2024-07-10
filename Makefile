CC = gcc
# CFLAGS += $(shell pkg-config --cflags json-c)
# LDFLAGS += $(shell pkg-config --libs json-c)
IMCFLAGS=$(shell /opt/homebrew/Cellar/imagemagick@6/6.9.13-12/bin/MagickWand-config --cflags)
IMLFLAGS=$(shell /opt/homebrew/Cellar/imagemagick@6/6.9.13-12/bin/MagickWand-config --ldflags --lib)
JSONGLIBCFLAGS=$(shell pkg-config --cflags json-glib-1.0)
JSONGLIBLFLAGS=$(shell pkg-config --libs json-glib-1.0) 
GLIB_HOME=/opt/homebrew/Cellar/glib/2.80.3/
hellomake: main.c read_json.c
	$(CC) -g -o balloon -I$(GLIB_HOME)include/glib-2.0/ \
	-I$(GLIB_HOME)lib/glib-2.0/include \
	$(IMCFLAGS) \
	$(IMLFLAGS) \
	$(JSONGLIBCFLAGS) \
	$(JSONGLIBLFLAGS) \
	read_json.c main.c 