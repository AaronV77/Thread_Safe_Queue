all:
	gcc -c queue.c
	gcc queue_main.c queue.o -o q

threads:
	gcc -c queue.c
	gcc threaded_main.c queue.o -DTHREADS -lpthread -o q

run:
	reset
	./q

clean:
	rm q queue.o