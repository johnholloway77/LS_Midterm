#Compiler
CC = clang

#Compiler flags
CFLAGS = -Wall -Wextra

# Source files
SOURCES = main.c \
    flags/setFlags.c \
    flags/checkFlags.c \
    file/checkFileType.c \
    get/getDir.c \
    get/getFile.c \
    str/strFileMode.c \
    str/strFileTime.c \
    str/strFileSize.c \
    str/strFileName.c \
    sort/sortArray.c \
    print/printListing.c \
    queue/dirQueue.c \
    get/recurDir.c

OBJECTS = $(SOURCES:.c=.o)

# Libraries to link
LIBS = -lm

#output binary
BINARY=ls_midterm

all: $(BINARY)

#rule to link the binary
$(BINARY): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBS)

#rule to compile source files into object files
%.o:  %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY:  clean
clean: 
	rm -rf $(BINARY) $(OBJECTS)

#clean only the object files
.PHONY: clean-obj
clean-obj:
	rm -rf $(OBJECTS)