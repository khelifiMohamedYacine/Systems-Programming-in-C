CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

all: anagram anaquery

# Rule to build anagram with math library
anagram: anagram.c
	$(CC) $(CFLAGS) anagram.c -o anagram $(LDFLAGS)

# Rule to build anaquery without math library
anaquery: anaquery.c
	$(CC) $(CFLAGS) anaquery.c -o anaquery

# Clean rule to remove executables
clean:
	rm -f anagram anaquery
