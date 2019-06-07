CXX = g++
CXXFLAGS += -Wall -std=c++14

module.so: module.cpp redismodule.h trie.o
	$(CXX) $(CXXFLAGS) -dynamic -fno-common -c -o module.o module.cpp
	ld -o module.so module.o trie.o -bundle -undefined dynamic_lookup -lc

trie.o: trie.h

.PHONY: tests clean

tests: test.cpp trie.o
	$(CXX) $(CXXFLAGS) test.cpp trie.o -o run_test && ./run_test && rm ./run_test

clean:
	rm trie.o module.o module.so
