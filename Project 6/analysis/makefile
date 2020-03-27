CC = g++
CPPFLAGS = -g -Wall -std=c++11 -O2
DELETE_FILES = bin analysis.o

analysis: FORCE ../bst/bst.h ../avl/avlbst.h ../splay/splay.h
	$(CC) $(CPPFLAGS) analysis.cpp -o analysis

FORCE: ;

.phony: clean test

clean:
	-@rm -rf $(DELETE_FILES)