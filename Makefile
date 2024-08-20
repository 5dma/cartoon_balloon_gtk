# On Ubuntu, need to remove the standard GraphicsMagick and ImageMagick, and compile from source. See https://imagemagick.org/script/install-source.php

CC = gcc
#ifeq ($(HOME),/Users/mlautman)
#	IMCFLAGS=$(shell /opt/homebrew/Cellar/imagemagick@6/6.9.13-14/bin/MagickWand-config --cflags)
#	IMLFLAGS=$(shell /opt/homebrew/Cellar/imagemagick@6/6.9.13-14/bin/MagickWand-config --ldflags --lib)
#	GLIB_HOME=/opt/homebrew/Cellar/glib/2.80.4/include/
#else
#	IMCFLAGS=$(/usr/bin/Magick-config --cflags)
#	IMLFLAGS=$(/usr/bin/Magick-config  --ldflags --libs)
#	GLIB_HOME=/usr/include/
#endif
#JSONGLIBCFLAGS=$(pkg-config --cflags json-glib-1.0)
#JSONGLIBLFLAGS=$(pkg-config --libs json-glib-1.0) 
# hellomake: main.c 
#	$(CC) -g -o balloon -I$(GLIB_HOME)glib-2.0/ \
#	$(IMCFLAGS) \
#	$(IMLFLAGS) \
#	$(JSONGLIBCFLAGS) \
#	$(JSONGLIBLFLAGS) \
#	read_json.c resize.c add_text.c logging.c read_annotation.c main.c 

#/usr/bin/gcc -g -Wall -o balloon `pkg-config --cflags glib-2.0` `pkg-config --cflags json-glib-1.0` `pkg-config --cflags GraphicsMagick` -I/usr/include/ImageMagick-6 main.c logging.c read_annotation.c read_json.c resize.c add_balloon.c add_text.c

/usr/bin/gcc -g -Wall -o balloon `pkg-config --cflags glib-2.0` `pkg-config --cflags json-glib-1.0` `pkg-config --cflags GraphicsMagick`  main.c logging.c read_annotation.c read_json.c resize.c add_balloon.c add_text.c

/usr/bin/gcc -g -Wall -o balloon `pkg-config --cflags glib-2.0` `pkg-config --cflags json-glib-1.0` `pkg-config --cflags MagickCore` main.c logging.c read_annotation.c read_json.c resize.c add_balloon.c add_text.c