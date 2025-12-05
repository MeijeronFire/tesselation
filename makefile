# all: compile
# 	./run 50 1 500 500
# 	mogrify -format png *.ppm

# compile:
# 	gcc tesselation.c -lpthread -lm -Wall -o run

all: 
	gcc fast_tesselation.c -O3 -lpthread -lm -Wall -Wpedantic -o run
	./run