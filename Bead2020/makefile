CC=gcc
all: elso masodik

elso: elso.c
	${CC} -o elso elso.c
masodik: masodik.c
	${CC} -o masodik -lm masodik.c

rm: elso masodik
	rm elso; rm masodik;