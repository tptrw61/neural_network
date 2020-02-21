
CXXFLAGS:=-Wall -g

test: test.o nn.o linalg.o
	g++ $(CXXFLAGS) -o $@ $^

test.o: test.cpp nn.h linalg.h
	g++ -c $(CXXFLAGS) -o $@ $<

nn.o: nn.cpp nn.h
	g++ -c $(CXXFLAGS) -o $@ $<

linalg.o: linalg_slow.cpp linalg.h
	g++ -c $(CXXFLAGS) -o $@ $<

vector_asm.o: vector_asm.s
	as -o $@ $<

matrix_asm.o: matrix_asm.s
	as -o $@ $<

clean:
	rm -f *.o
