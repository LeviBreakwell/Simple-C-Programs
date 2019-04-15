# Makefile for the ZDK
#
# $Revision:Wed Feb 14 21:24:00 EAST 2018$

TARGET=libzdk.a
FLAGS=-Wall -Werror -std=gnu99 -g

all: $(TARGET)

clean:
	if [ -f $(TARGET) ]; then rm $(TARGET); fi; \
	for f in *.o; do \
		if [ -f $${f} ]; then rm $${f}; fi; \
	done 

rebuild: clean all

$(TARGET): *.c *.h
	gcc -c *.c $(FLAGS)
	ar r $(TARGET) *.o
