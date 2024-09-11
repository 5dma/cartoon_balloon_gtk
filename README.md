Adds speech balloons to images.


# Library dependencies

As of Ubuntu 24.04, install the following packages

* libmagick++-6-headers
* libjson-glib-dev
* glib-2.0 


# Compiling

`make`

# Running

1. Configure settings in `annotation.json` and `configuration.json`.
2. `./balloon`

# Memory check

```
valgrind --leak-check=full  --show-leak-kinds=all  --track-origins=yes --verbose --gen-suppressions=yes --log-file=/tmp/valgrind-out.txt  ./balloon
```