build/set_brightness: build source/main.c
	gcc -o build/set_brightness source/main.c

run: build/set_brightness
	build/set_brightness

build:
	mkdir build

clean:
	rm -r build

install:
	cp build/set_brightness /bin/set_brightness
	chmod u+s /bin/set_brightness

uninstall:
	rm /bin/set_brightness