
out = api

build: main.c deps/serial/serial.c
	$(CC) -std=c99 -Wall $^ -o $(out)

clean:
	rm -rf $(out)

.PHONY: build clean
