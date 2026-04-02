# C-2025 project base IK
all:
	gcc -std=c99 -pedantic -Wall src/*.c -o bin/app

.PHONY: test
test:
	gcc -std=c99 -pedantic -Wall -Isrc -IUnity/src \
	test/test_main.c \
	test/test_binaaripuu.c \
	test/test_haut.c \
	test/test_linkitettylista.c \
	test/test_punamustapuu.c \
	src/yleiset.c \
	src/binaaripuu.c \
	src/haut.c \
	src/linkitettylista.c \
	src/punamustapuu.c \
	Unity/src/unity.c \
	-o bin/test 
	./bin/test

clean:
	rm -f bin/app bin/test
