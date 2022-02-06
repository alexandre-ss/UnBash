unbash: 
	gcc -o unbash -W main.c
	./unbash

clean:
	rm -rf *.o*