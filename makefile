build: joc.c
	gcc joc.c -o joc

run:
	./joc
clean:
	rm joc

test:
	make build
	valgrind --leak-check=full ./checker.sh
	make clean
