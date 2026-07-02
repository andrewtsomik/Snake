# Set a variable LDFLAGS. Use the variable as $(LDFLAGS)
LDFLAGS := -L ~/lib -lsense -lm

clean:
		rm -f *.o final

all: final
final: main.o input.o output.o
		cc -o final main.o input.o output.o $(LDFLAGS)

main.o: main.c project.h
		cc -c main.c -I ~/include

input.o: input.c project.h
		cc -c input.c -I ~/include

output.o: output.c project.h
		cc -c output.c -I ~/include

run: final
		./final

