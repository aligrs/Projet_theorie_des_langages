NOM=PROJET_IN301

test1	:
	./eval "(2* ( (3 + 45)-8  )) +14/3" 
test2	:
	./eval "(2.   0+  12)-  ((4*2)+  3)" # expression avec . (float)
test3	:
	./eval "(2*   3+(3 -1)" # expression non correct
all:eval

eval:	main.o mes_fontion.o 
	gcc -o eval main.o mes_fontion.o 
mes_fontion.o:mes_fontion.c mes_fontion.h mestypes.h
	gcc  -c mes_fontion.c 
main.o:	main.c mes_fontion.h mestypes.h
	gcc -o main.o -c main.c 



clean:
       #clean all
	rm -f *.o
