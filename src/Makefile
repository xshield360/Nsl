TARGET=../bin/nsl
CPPFLAGS= gcc  -ggdb -Wall -std=c99
all:
	$(CPPFLAGS) -o $(TARGET) nsl.c scanner.c parser.c node.c inter.c symbol.c
clean:
	rm -f *.o $(TARGET)
