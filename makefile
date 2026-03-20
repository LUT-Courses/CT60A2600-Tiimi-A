# C-2025 project base IK
all:
	gcc -std=c99 -pedantic -Wall src/*.c -o bin/app

UNITY_DIR = Unity/src
.PHONY: test
test:
	gcc -std=c99 -pedantic -Wall -Isrc -IUnity/src test/test.c src/yleiset.c src/binaaripuu.c src/haut.c src/linkitettylista.c src/punamustapuu.c Unity/src/unity.c -o bin/test
	./bin/test

clean:
	rm -f bin/app bin/test
