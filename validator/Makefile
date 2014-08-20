
RM	:= rm	

FILES	:= validator.c
OUTPUT	:= $(FILES:%.c=%_test)


default:	$(OUTPUT)

%_test:%.c
	g++ -DSELF_TEST -g $< -o $@ -L.  -lm -lpthread -lgtest

clean:
	$(RM) -f *~
	$(RM) -f *_test
