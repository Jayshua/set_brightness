build/brightness: build source/main.c
	gcc -o build/brightness source/main.c

run: build/brightness
	build/brightness

build:
	mkdir build

clean:
	rm -r build

install:
	cp build/brightness /bin/brightness
	chmod u+s /bin/brightness

uninstall:
	rm /bin/brightness