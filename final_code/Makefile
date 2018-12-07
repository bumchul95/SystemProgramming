final: dht11temp.o gravity.o led.o main.o
	gcc -pthread -o final dht11temp.o gravity.o led.o main.o -lwiringPi

dht11temp.o: dht11temp.c
	gcc -c -o dht11temp.o dht11temp.c

gravity.o: gravity.c
	gcc -c -o gravity.o gravity.c

led.o: led.c
	gcc -c -o led.o led.c

main.o: main.c
	gcc -c -o main.o main.c

clean :
	rm -rf *.o
