
OBJ = main.o analyse.o bst.o
HEADER = text_analysis.h
EXE = text-analyse

executable: $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS) -std=c99

$(OBJ): $(HEADER)

debug: CFLAGS += -g -DDEBUG
debug: clean
debug: executable

.PHONY: clean

clean: 
	-rm $(EXE) $(OBJ)

