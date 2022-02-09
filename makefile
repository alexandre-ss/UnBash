unbash: 
	@gcc -o unbash -W main.c

execute:
	@./unbash
	@rm -rf unbash