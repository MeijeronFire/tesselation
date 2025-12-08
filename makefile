# all: compile
# 	./run 50 1 500 500
# 	mogrify -format png *.ppm

# compile:
# 	gcc tesselation.c -lpthread -lm -Wall -o run

all: fast_tesselation.o tpool.o
	gcc -o tes fast_tesselation.o tpool.o
fast_tesselation.o:
	gcc -c fast_tesselation.c
tpool.o:
	gcc -c tpool.c
clean:
	rm -f run tes
	rm -f *.ppm
	rm -f *.png
	rm -f *.gif
	rm -f *.txt
	rm -f *.o