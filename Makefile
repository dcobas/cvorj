DIRS=driver support support_test userlib

all:
	$(MAKE) -C driver 
	$(MAKE) -C support
	$(MAKE) -C support_test
	$(MAKE) -C userlib

clean:
	$(MAKE) -C driver clean
	$(MAKE) -C support clean
	$(MAKE) -C support_test clean
	$(MAKE) -C userlib clean
