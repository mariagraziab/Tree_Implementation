CXX=g++
SRC1=test/test.cpp
SRC2=test/benchmark.cpp
FLAGS = -std=c++14 -Wall -Wextra 

all: test.x benchmark.x doc

test.x : $(SRC1)
	$(CXX) $(FLAGS) -o $@ $< -Iinclude

benchmark.x: $(SRC2)
	$(CXX) $(FLAGS) -o $@ $< -Iinclude

doc:
	@cd documentation; doxygen Doxyfile

clean:
	@rm -rf *.x documentation/html documentation/latex result/*.txt

.PHONY: clean all format document
