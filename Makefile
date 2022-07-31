build: 
	g++ main.cpp -o not-snake -lstdc++ -lncurses
clean: 
	rm not-snake
install:
	cp not-snake /bin
uninstall:
	rm /bin/not-snake
