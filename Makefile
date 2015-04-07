CC = gcc
INCS = $(*.h)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
BIN = my_malloc

$(BIN) : $(OBJS) $(INCS)
	gcc $^ -o $@

%.o : $.c $(INCS)
	gcc $< -c
