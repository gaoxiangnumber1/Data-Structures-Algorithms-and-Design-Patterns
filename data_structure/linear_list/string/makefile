CXX = g++
CXXFLAG =	-std=c++11 -Wall -Wconversion -Werror -Wextra -Wno-unused-parameter \
						-Wold-style-cast -Woverloaded-virtual -Wpointer-arith -Wshadow \
						-Wwrite-strings -march=native -rdynamic -I.

SOURCE	= $(shell find . -name '*.cc')
TEST = $(SOURCE:.cc=)

all: $(TEST)

.cc:
	$(CXX) $(CXXFLAG) -o $@ $<

clean:
	rm -f $(TEST) *~
