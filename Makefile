.PHONY: all test

run:
	gcc ./src/server.c ./src/linked_list.c -o run-server
	./run-server

test:
	gcc -g ./test/linked_list_test.c ./src/linked_list.c ./src/iterator.c -o run-test
	./run-test
