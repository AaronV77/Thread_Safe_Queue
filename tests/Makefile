all:
	gcc queue_tests.c ../queue.o -L/usr/local/lib/libcheck.so.0 -lcheck -lpthread -DTHREADS -o c

run:
	./c
	
clean:
	rm c