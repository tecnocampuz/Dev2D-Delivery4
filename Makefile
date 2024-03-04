CFLAGS = -std=c99 -Wall -Werror -Wno-unused-variable -Wno-format
SOURCES = main.c

release:
	mkdir -p build
	clang $(SOURCES) -lraylib -o build/executable $(CFLAGS) -O3

debug:
	mkdir -p build
	clang $(SOURCES) -lraylib -o build/executable $(CFLAGS) -O0 -g -rdynamic -DDEBUG=1

clean:
	rm -rf build

test: debug
	build/executable