# Set a variable LDFLAGS. Use the variable as $(LDFLAGS)
LDFLAGS := -L ./lib/lib -lsense -lm

clean:
		rm -f *.o final

all: final
final: main.o input.o output.o
		cc -o final main.o input.o output.o $(LDFLAGS)

main.o: main.c project.h
		cc -c main.c -I ./lib/include

input.o: input.c project.h
		cc -c input.c -I ./lib/include

output.o: output.c project.h
		cc -c output.c -I ./lib/include

run: final
		./final

