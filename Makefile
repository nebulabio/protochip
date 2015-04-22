
out = protochip_driver

build: ./driver/main.c ./driver/deps/serial/serial.c
	$(CC) -std=c99 -Wall $^ -o $(out)

clean:
	rm -rf $(out)

money:
	ledger -f finances.dat balance

.PHONY: build clean
