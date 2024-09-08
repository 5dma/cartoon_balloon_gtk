Adds speech balloons to images.


# Library dependencies

* On Ubuntu, need to remove the standard GraphicsMagick and ImageMagick, and compile from source. See https://imagemagick.org/script/install-source.php
* glib-2.0
* json-glib-1.0


# Compiling

On Ubuntu 24.04, the following shell command is necessary:

export LD_LIBRARY_PATH=/snap/gnome-42-2204/current/usr/lib/x86_64-linux-gnu:/snap/core20/2264/usr/lib/x86_64-linux-gnu

export LD_LIBRARY_PATH=/snap/gnome-42-2204/current/usr/lib/x86_64-linux-gnu:/snap/core20/2318/usr/lib/x86_64-linux-gnu/

export LD_LIBRARY_PATH=/snap/gnome-42-2204/current/usr/lib/x86_64-linux-gnu:/snap/core22/1564/usr/share/doc/libstdc++6

export LD_LIBRARY_PATH=/snap/gnome-42-2204/current/usr/lib/x86_64-linux-gnu:/snap/core22/1586/usr/lib/x86_64-linux-gnu
export LD_LIBRARY_PATH=/snap/gnome-42-2204/current/usr/lib/x86_64-linux-gnu:/snap/core/17200/usr/lib/x86_64-linux-gnu/
export LD_LIBRARY_PATH=/snap/gnome-42-2204/current/usr/lib/x86_64-linux-gnu:/snap/core/16928/usr/lib/x86_64-linux-gnu
export LD_LIBRARY_PATH=/snap/gnome-42-2204/current/usr/lib/x86_64-linux-gnu:/snap/gnome-42-2204/176/usr/lib/x86_64-linux-gnu
export LD_LIBRARY_PATH=/snap/gnome-42-2204/current/usr/lib/x86_64-linux-gnu:
export LD_LIBRARY_PATH=/snap/gnome-42-2204/current/usr/lib/x86_64-linux-gnu:


`make`

# Running

1. Configure settings in `annotation.json` and `configuration.json`.
2. `./balloon`