NS=100000 1000000 10000000 100000000 1000000000
PS=1 2 4 6 8 12 16 20 24
TS=0 1 2 3 4

.PHONY: all
all:
	bsub -n 24 -W 00:10 -R "rusage[mem=2048]" -R "span[ptile=24]" -o batch.txt "make run"

.PHONY: run
run: results/all.txt

results/all.txt: extract.py $(foreach n,$(NS), \
	$(foreach p,$(PS), \
		$(foreach t,$(TS), \
			results/$(n)-$(p)-$(t).txt \
		) \
	) \
)
	python $^ > $@

define RUNNER
results/$(n)-$(p)-$(t).txt: dotProduct
	mkdir -p results
	export OMP_NUM_THREADS=$(p); ./dotProduct $(n) > $$@
endef

$(foreach n,$(NS), \
	$(foreach p,$(PS), \
		$(foreach t,$(TS), \
			$(eval $(RUNNER)) \
		) \
	) \
)

dotProduct: dotProduct.cpp walltime.h
	g++ -O3 -fopenmp $< -o $@

clean:
	rm -rf dotProduct
	rm -rf results
	rm -rf batch.txt