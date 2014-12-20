
OBJ = main.o analyse.o bst.o fgetline.o syllablecount.o
HEADER = text_analysis.h main.h
EXE = text-analyse

executable: $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

$(OBJ): $(HEADER)

debug: CFLAGS += -g -DDEBUG
debug: clean
debug: executable

test_bst: CFLAGS += -g -DTEST_BST -DDEBUG
test_bst: bst.o syllablecount.o
	$(CC) -o bst.test bst.o syllablecount.o

.PHONY: clean

clean: 
	-rm $(EXE) $(OBJ)

