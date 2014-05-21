CFLAGS = -Wall
LDFLAGS	=
LDLIBS = -lstdc++
EXECS = shapley 

CFLAGS += -DNDEBUG
CFLAGS += -g
#CFLAGS += -pg
#LDFLAGS += -pg

TARGET: $(EXECS)

all: $(TARGET)

main.o : main.c

shapley: main.o safe_stdlib.o io.o function.o dijkstra.o graph.o queue.o

%.o : %.c %.h

%.o : %.cpp %.h

.PHONY: clean TARGET
clean:
	rm -f $(EXECS) *.o *~
