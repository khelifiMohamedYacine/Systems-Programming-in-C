CC = gcc
CFLAGS = -Wall -g
all: patience pstatistics

# Rule to build patience
patience: patience.c patience.h
	$(CC) $(CFLAGS) -DPATIENCE_MAIN patience.c -o patience

# Rule to build pstatistics
pstatistics: pstatistics.c patience.c patience.h
	$(CC) $(CFLAGS) -DPSTATISTICS_MAIN pstatistics.c patience.c -o pstatistics

# Clean rule to remove executables and object files
clean:
	rm -f patience pstatistics patience.o
