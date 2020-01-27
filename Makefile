
CXXFLAGS:=-Wall

linalg.o: linalg_slow.cpp linalg.h
	g++ -c $(CXXFLAGS) -o $@ $<

vector_asm.o: vector_asm.s
	as -o $@ $<

matrix_asm.o: matrix_asm.s
	as -o $@ $<

clean:
	rm -f *.o
