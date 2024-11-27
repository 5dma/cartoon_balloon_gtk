#Compiler and Linker
CC          := gcc

#The Target Binary Program
TARGET      := balloon

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := .
INCDIR      := headers
OBJDIR      := obj
TARGETDIR   := bin
#RESDIR      := res
SRCEXT      := c
DEPEXT      := d
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      := -g -Wall `pkg-config --cflags ImageMagick` `pkg-config --cflags json-glib-1.0` `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk4`
LFLAGS         := `pkg-config --libs glib-2.0` `pkg-config --libs json-glib-1.0` `pkg-config --libs gtk4` `pkg-config --libs ImageMagick` `pkg-config --libs MagickWand`
INC          := -I$(INCDIR)
#INC         := -I$(INCDIR) -I/usr/local/include
#INCDEP      := -I$(INCDIR)

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
#Find all source files
SOURCES     := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
#Create object file names from the source file names
OBJECTS     := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

all: directories $(TARGET)

# Make directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(OBJDIR)

#Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LFLAGS)


#Compile
$(OBJDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

#Clean objects
clean:
	@$(RM) -rf $(OBJDIR)

.PHONY: clean

