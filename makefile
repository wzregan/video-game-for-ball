GCC=gcc
INCLUDEDIR=./head/
GCCFLAG=-w -I $(INCLUDEDIR)
OBJ=enter.o
LIB=-lcurses
BIN=./bin/
vpath %.c src
vpath %.h head
vpath %.o bin

debug:$(OBJ)
	$(GCC) $(GCCFLAG)  -g $(addprefix $(BIN),$^)  -o  $(BIN)$@ $(LIB)
$(OBJ):%.o:%.c
	$(GCC) $(GCCFLAG) -c -g $^ -o $(BIN)$@ 
clean:
	rm ./bin/*
