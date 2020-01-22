
linalg.o: linalg_slow.cpp linalg.h
	g++ -c -o $@ $<

vector_asm.o: vector_asm.s
	as -o $@ $<

matrix_asm.o: matrix_asm.s
	as -o $@ $<

clean:
	rm -f *.o
