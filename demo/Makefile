
# This Makefile builds or cleans all the demos together.
DEMOS = leds_c leds_cpp buttons_cpp serial_c analogin_c
DEMOCLEAN = $(addsuffix .clean,$(DEMOS))

all: $(DEMOS)

clean: $(DEMOCLEAN)

$(DEMOS):
	$(MAKE) -C $@

$(DEMOCLEAN): %.clean:
	$(MAKE) -C $*  clean

.PHONY: all $(DEMOS) $(DEMOCLEAN)
