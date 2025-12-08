# all: compile
# 	./run 50 1 500 500
# 	mogrify -format png *.ppm
buildopts = -Wall -Wextra -lpthread -pthread

all: tes

tes: main.o fast_tesselation.o tpool.o defs.o
	gcc $(buildopts) -o tes $^

%.o: %.c
	gcc $(buildopts) -c $<

clean:
	rm -f tes run *.o *.ppm *.png *.gif *.txt