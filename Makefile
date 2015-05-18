# make print-VARNAME
print-%: ; @echo $*=$($*)

dist_path    = `pwd`/dist
driver_dist  = $(dist_path)/driver
driver_deps := $(foreach dir, driver/deps, $(wildcard $(dir)/*/*.c))
driver_src   = ./driver/main.c

CC = gcc

# FIXME: when the gui is added to the makefile, put it under dist task too
dist: driver


dist_dir: 
	@mkdir -p $(dist_path)

driver: dist_dir
	$(CC) -std=c99 -g -Wall $(driver_src) $(driver_deps) -o $(driver_dist)

clean:
	rm -rf $(dist_path)

money:
	ledger -f finances.dat balance

.PHONY: driver clean dist dist_dir
