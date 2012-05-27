
# This Makefile builds or cleans all the demos together.
DEMOS = ${sort ${dir ${wildcard */}}}
DEMOCLEAN = $(addsuffix .clean,$(DEMOS))

all: $(DEMOS)

clean: $(DEMOCLEAN)

$(DEMOS):
	$(MAKE) -C $@

$(DEMOCLEAN): %.clean:
	$(MAKE) -C $*  clean

.PHONY: all $(DEMOS) $(DEMOCLEAN)
