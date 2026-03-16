# C-2025 project base IK
all:
	gcc -std=c99 -pedantic -Wall src/*.c -o bin/app

UNITY_DIR = Unity/src

test:
	gcc -std=c99 -pedantic -Wall -Isrc -IUnity/src tests/yleiset.c src/yleiset.c Unity/src/unity.c -o bin/tests
	./bin/test

clean:
	rm -f bin/app bin/test
