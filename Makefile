#This is a rather "generic" Makefile in case it's needed and also a test for my first push. The Makefile will have to be modified if we intend to use it. 

CC=gcc
CFLAGS=-Wall 

DEBUG=no
ifeq ($(DEBUG),yes)
CFLAGS += -g
endif

Qwirkle: partie.o joueur.o tuile.o sac.o test.o
	$(CC) $^ -o Qwirkle

partie.o: partie.h joueur.h sac.h
joueur.o: joueur.h tuile.h
sac.o: sac.h tuile.h
tuile.o: tuile.h
test.o: test.h
%.o:%.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f *.o *~
	rm -f Qwirkle


