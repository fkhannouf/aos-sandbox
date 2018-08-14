# Makefile setup
#
# Put headers in "include" directory and update the _DEPS variable
# Put C/C++ sources in the roor directory and update the _OBJ variable
#
# Make the project using : make
# Clean the project using : make clean
 

INCDIR = ./include
CC=ppc-amigaos-g++
CFLAGS=-I$(INCDIR)

OBJDIR = obj

LIBS = -lauto

_DEPS =
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

_OBJ = main.o 
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))


$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o
