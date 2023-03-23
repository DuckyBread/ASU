CC = g++
CFLAGS = -Werror -Wall -Wextra

all: LR_2

LR_2: lab_2.cc
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf LR_2 *.txt *.out
