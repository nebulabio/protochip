# make print-VARNAME
print-%: ; @echo $*=$($*)

dist_path = `pwd`/dist

driver_dist = $(dist_path)/driver

driver: ./driver/main.c ./driver/deps/serial/serial.c
	$(CC) -std=c99 -Wall $^ -o $(driver_dist)

clean:
	rm -rf $(dist_path)

money:
	ledger -f finances.dat balance

.PHONY: driver clean
