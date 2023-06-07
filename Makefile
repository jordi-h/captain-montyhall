### 
## Makefile skeleton
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
DOXYGEN=doxygen

# Files
EXEC=tresor
MODULES=main.c outils.c interface.c
OBJECTS=main.o outils.o interface.o

DOXFILE=DoxyFile

## Rules

all: $(EXEC)

tresor: $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS) $(GTKFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS) $(GTKFLAGS)

outils.o: outils.c
	$(CC) -c outils.c -o outils.o $(CFLAGS) $(GTKFLAGS)

interface.o: interface.c
	$(CC) -c interface.c -o interface.o $(CFLAGS) $(GTKFLAGS)

doc: 
	$(DOXYGEN) $(DOXFILE)

clean:
	rm -f *.o $(EXEC) *~
