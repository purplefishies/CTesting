
RM	:= rm	

FILES	:= validator.c obj_w_validation.c
OUTPUT	:= $(FILES:%.c=%_test)
HEADERS	:= $(wildcard *.h)

.PHONY:	$(HEADERS)

default:	$(OUTPUT)

%.h:

validator_test:validator.c validator.h
	g++ -DSELF_TEST -g $< -o $@ -L.  -lm -lpthread -lgtest

libvalidator.so:	validator.c
	g++ -fPIC -shared -g validator.c -o libvalidator.so -L.  -lm -lpthread


obj_w_validation_test: obj_w_validation.c libvalidator.so
	 g++ -DSELF_TEST -g -o $@ $< -L. -lvalidator -lm -lpthread -lgtest 

clean:
	$(RM) -f *~
	$(RM) -f *_test
	$(RM) *.so
