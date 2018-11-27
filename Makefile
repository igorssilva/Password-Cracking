
enc:
	gcc -Wall key.c encrypt.c -o encrypt -g
	
dec:
	gcc -Wall key.c decrypt.c -o decrypt -g

brute:
	gcc -Wall key.c brute.c -o brute -g

clean:
	rm -f *.o a.out encrypt gmon.out prof
