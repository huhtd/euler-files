IS= 4096
PS=16 20 24
TS=0 1 2 3 4

.PHONY: all
all:
	bsub -n 24 -W 03:59 -R "rusage[mem=2048]" -R "span[ptile=24]" -o batch.txt "make run"

.PHONY: run
run: results4096/all.txt

results4096/all.txt: extract.py $(foreach i,$(IS), \
	$(foreach p,$(PS), \
		$(foreach t,$(TS), \
			results4096/$(i)-$(p)-$(t).txt \
		) \
	) \
)
	python $^ > $@

define RUNNER
results4096/$(i)-$(p)-$(t).txt: mandel_omp
	mkdir -p results4096
	export OMP_NUM_THREADS=$(p); ./mandel_omp $(i) > $$@
endef

$(foreach i,$(IS), \
	$(foreach p,$(PS), \
		$(foreach t,$(TS), \
			$(eval $(RUNNER)) \
		) \
	) \
)

mandel: mandel_seq mandel_omp

mandel_seq: mandel_seq.c pngwriter.c
	gcc -o $@ -I. -O3 $^ -lpng

mandel_omp: mandel_omp.c pngwriter.c
	gcc -o $@ -I. -O3 $^ -lpng

clean:
	rm -rf mandel_seq mandel_omp
	rm -rf results4096seq
	rm -rf batch.txt
