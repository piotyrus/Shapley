CFLAGS = -Wall
LDFLAGS	=
LDLIBS = -lOpenCL -lstdc++
EXECS = shapley 

CFLAGS += -DNDEBUG
CFLAGS += -g
#CFLAGS += -pg
#LDFLAGS += -pg

TARGET: $(EXECS)

all: $(TARGET)

main.o : main.c

shapley: main.o safe_stdlib.o io.o

%.o : %.c %.h

.PHONY: clean TARGET
clean:
	rm -f $(EXECS) *.o *~
