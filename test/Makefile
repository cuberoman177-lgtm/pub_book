all: clean
	gcc -o test_search.out test_search.c ../src/book_utils.c -I. -I../include -lrt -lm
	./test_search.out

clean:
	$(RM) *.out
