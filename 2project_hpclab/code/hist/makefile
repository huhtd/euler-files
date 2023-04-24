PS=1 2 4 6 8 12 16 20 24
TS=0 1 2 3 4 5 6 7 8 9

.PHONY: all
all:
	bsub -n 24 -W 03:59 -R "rusage[mem=2048]" -R "span[ptile=24]" -o batch.txt "make run"

.PHONY: run
run: results/all.txt

results/all.txt: extract.py $(foreach p,$(PS), \
	$(foreach t,$(TS) \
		,results/$(i)-$(p)-$(t).txt \
	) \
)
	python $^ > $@

define RUNNER
results/$(p)-$(t).txt: hist_omp
	mkdir -p results
	export OMP_NUM_THREADS=$(p); ./hist_omp > $$@
endef

$(foreach p,$(PS), \
	$(foreach t,$(TS), \
		$(eval $(RUNNER)) \
	) \
)

all: hist_seq hist_omp

hist_seq: hist_seq.cpp
	g++ -O3 $^ -o $@

hist_omp: hist_omp.cpp
	g++ -O3 -fopenmp $^ -o $@

clean:
	rm -rf hist_seq hist_omp
	rm -rf results
	rm -rf batch.txt
