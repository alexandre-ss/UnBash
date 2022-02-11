unbash: 
	@gcc -o unbash -W main.c
	@./unbash
	@rm -rf unbash