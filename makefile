# C-2025 project base IK
all:
	gcc -std=c99 -pedantic -Wall src/main.c src/module.c -o bin/app

UNITY_DIR = Unity/src

test:
	gcc -std=c99 -pedantic -Wall -Isrc -IUnity/src tests/test_module.c src/module.c Unity/src/unity.c -o bin/tests
	./bin/tests

clean:
	rm -f bin/app bin/test
