TARGETS=hello hello_zdk banner CAB202_Topic_1_Notes.html Topic01-Notes.zip

all: $(TARGETS)

LIBS=-lzdk -lncurses -lm
DIRS=-I../ZDK -L../ZDK
FLAGS=-std=gnu99 -Wall -Werror -g

clean:
	for f in $(TARGETS); do \
		if [ -f $$f ]; then rm $$f; fi; \
		if [ -f $$f.exe ]; then rm $$f.exe; fi; \
		if [ -f $$f.html ]; then rm $$f.html; fi; \
	done

rebuild: clean all

banner: banner.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 

hello: hello.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 

hello_zdk: hello_zdk.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 

CAB202_Topic_1_Notes.html: CAB202_Topic_1_Notes.src ../packages/Common/html.pch
	m5 "CAB202_Topic_1_Notes.html" "CAB202_Topic_1_Notes.src"

Topic01-Images/Slide_16_cropped.png: ../Diagrams/Diagrams/Slide_16_cropped.png
	cp "$<" "$@"

Topic01-Notes.zip: CAB202_Topic_1_Notes.html Topic01-Images/Slide_16_cropped.png
	jar cfM $@ CAB202_Topic_1_Notes.html Topic01-Images/*
