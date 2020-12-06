CC		= gcc
CFLAGS = -O -Wall -Wstrict-prototypes -ansi -pedantic -g #-pg
TARGET = ./bin/csv2bin
INCLS = -I./inc
LIBS = -lm 
LFLAGS = 

SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o) #main.o stats.o utils.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLS) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS)
		
%.o: %.c
	$(CC) $(CFLAGS) $(INCLS) -o $@ -c $<
	
.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJS) a.out

.PHONY: test 
test:
	$(TARGET) ./test/ ts.csv ts.bin
