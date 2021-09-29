.PHONY:clean test

target= lexana
CXXFLAGS= -g -Iinclude

$(target): log.o node.o keyword.o ./src/main.cpp
	$(CXX) $(CXXFLAGS) ./src/main.cpp node.o log.o keyword.o -o $(target)

log.o: ./src/log.cpp
	$(CXX) $(CXXFLAGS) ./src/log.cpp -c -o log.o

node.o: ./src/node.cpp
	$(CXX) $(CXXFLAGS) ./src/node.cpp -c -o node.o

keyword.o: ./src/keyword.cpp
	$(CXX) $(CXXFLAGS) ./src/keyword.cpp -c -o keyword.o

clean:
	rm *.o

test: $(target)
	$(target) test.c

debug: $(target)
	gdb $(target)