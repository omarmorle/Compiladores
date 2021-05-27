Gram=y.tab.c y.tab.h

all: $(Gram) 
	@gcc -o calc y.tab.c vectores.c -lm 
	@echo Compiled

$(Gram): vectores.y
	@yacc -d vectores.y

clean:
	@rm -f *.out  *.tab.* calc
	@echo Clean
